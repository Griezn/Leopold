//
// Created by Seppe Degryse on 27/12/2023.
//

#include <algorithm>
#include "Manille.hpp"
#include "Card.hpp"
#include "iostream"


constexpr CardBitset MASK            = 0b1111'1111'1111'1111'1111'1111'1111'1111;
constexpr CardBitset HEARTS_FILTER   = 0b0001'0001'0001'0001'0001'0001'0001'0001;
constexpr CardBitset SPADES_FILTER   = 0b0010'0010'0010'0010'0010'0010'0010'0010;
constexpr CardBitset CLUBS_FILTER    = 0b0100'0100'0100'0100'0100'0100'0100'0100;
constexpr CardBitset DIAMONDS_FILTER = 0b1000'1000'1000'1000'1000'1000'1000'1000;


CardBitset Manille::get_allowed_cards(const CardBitset &player, const CardVector &trick, int playerI, const Suit trump)
{
    if (trick.empty())
        return player;

    const Suit suit = trick[0].suit();
    if (suit == trump) {
        auto filtered = filter_bitset(player, suit);

        // If the player has no cards from the trump suit, they can play any
        if (filtered.none()) {
            return player;
        }

        // At this point, the player has cards from the trump suit
        auto higher = filter_bitset_higher(filtered, suit, get_highest_card(trick, suit));

        // If the player has no cards higher from the played one (trump suit), they can provide any cards from the trump
        // suit
        if (higher.none()) {
            return filtered;
        }

        // If the player has at least one card from the trump suit that is higher than the played one, they have to play
        // one of them
        return higher;
    } else {
        auto filtered = filter_bitset(player, suit);

        // If the player has cards from the same suit, player has to provide (any of these cards)
        if (filtered.any())
            return filtered;

        // At this point, the player cannot follow suit
        // filter cards from the trump suit
        filtered = filter_bitset(player, trump);

        // If the player does not have cards from the trump suit, they can play any card
        if (filtered.none()) {
            return player;
        }

        // At this point, the player has some cards from the trump suit
        if (trick.size() == 1) {
            return filtered;
        }

        // We determine if using a card from the trump suit is an obligation, based on the partner
        auto played_filtered = filter_cards(trick, trump);

        // If there are no played cards from the trump suit, the player has to use a card from the trump suit only if
        // their partner is not leading
        if (played_filtered.empty()) {
            if (!is_partner_leading(trick, playerI, trump)) {
                return filtered;
            } else {
                return player;
            }
        }

        // At this point, there are played cards from the trump suit
        // If the partner is leading, the player can play any card
        if (is_partner_leading(trick, playerI, trump)) {
            return player;
        }

        // At this point, the partner is not leading
        // The player has to use a card from the trump suit only if they can beat the opponent's card
        auto higher = filter_bitset_higher(player, trump, get_highest_card(trick, trump));

        if (higher.none()) {
            return player;
        }

        return higher;
    }
}


int Manille::get_score(const CardVector &trick)
{
    int score = 0;
    for (auto &card: trick) {
        score += card.points();
    }
    return score;
}


CardVector Manille::filter_cards(const CardVector &cards, Suit suit)
{
    CardVector filtered = CardVector();

    for (auto &card: cards) {
        if (card.suit() == suit) {
            filtered.emplace_back(card);
        }

    }
    return filtered;
}


CardVector Manille::filter_cards_higher(const CardVector &cards, Suit suit, Card a_card)
{
    CardVector filtered = CardVector();

    for (auto &card: cards) {
        if (card.suit() == suit && card > a_card) {
            filtered.emplace_back(card);
        }

    }

    return filtered;
}


Card Manille::get_highest_card(const CardVector &cards, Suit suit)
{
    Card highest = Card(31);
    for (auto &card: cards) {
        if (card.suit() == suit && card >= highest) {
            highest = card;
        }
    }
    return highest;
}


int Manille::get_leader(const CardVector &trick, const Suit suit)
{
    const auto highest_card = get_highest_card(trick, suit);

    if (!highest_card.valid()) {
        return -1;
    }

    return highest_card.player();
}


bool Manille::is_partner_leading(const CardVector &trick, int player_index, Suit suit)
{
    return get_leader(trick, suit) == (player_index + 2) % 4;
}


Suit Manille::choose_trump(const CardBitset &player)
{
    int points[4] = {0, 0, 0, 0};
    Suit suits[4] = {(Suit) HEARTS_MASK, (Suit) SPADES_MASK, (Suit) CLUBS_MASK, (Suit) DIAMONDS_MASK};


    for (int i = 0; i < CARD_COUNT; ++i) {
        if (player[i]) {
            points[(int) Card(i).suit() >> 4] += Card(i).points();
        }
    }

    return suits[std::distance(points, std::max_element(points, points + 4))];
}


int Manille::determine_winner(const CardVector &trick, Suit trump)
{
    const Suit suit = trick[0].suit();
    if (suit == trump || !filter_cards(trick, trump).empty()) {
        return get_leader(trick, trump);
    } else {
        return get_leader(trick, suit);
    }
}


CardBitset suit_to_filter(Suit suit)
{
    switch (suit) {
        case HEARTS_MASK:
            return HEARTS_FILTER;
        case SPADES_MASK:
            return SPADES_FILTER;
        case CLUBS_MASK:
            return CLUBS_FILTER;
        case DIAMONDS_MASK:
            return DIAMONDS_FILTER;
        default:
            return 0;
    }
}


inline CardBitset Manille::filter_bitset(const CardBitset &cards, Suit suit)
{
    return cards & suit_to_filter(suit);
}


CardBitset Manille::filter_bitset_higher(const CardBitset &cards, Suit suit, Card card)
{
    auto temp = filter_bitset(cards, suit); // filter on suit
    auto value = card.value();
    return temp & (MASK >> (8 - value) * 4);
}
