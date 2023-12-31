//
// Created by Seppe Degryse on 27/12/2023.
//

#include <algorithm>
#include "Manille.hpp"
#include "Card.hpp"


CardVector Manille::get_allowed_cards(const CardVector &player, const CardVector &trick, const Suit trump)
{
    const Suit suit = trick[0].suit;
    if (suit == trump) {
        auto filtered = filter_cards(player, suit);

        // If the player has no cards from the trump suit, they can play any
        if (filtered.empty()) {
            return player;
        }

        // At this point, the player has cards from the trump suit
        auto higher = filter_cards_higher(filtered, suit, get_highest_card(trick, suit));

        // If the player has no cards higher from the played one (trump suit), they can provide any cards from the trump
        // suit
        if (higher.empty()) {
            return filtered;
        }

        // If the player has at least one card from the trump suit that is higher than the played one, they have to play
        // one of them
        return higher;
    } else {
        auto filtered = filter_cards(player, suit);

        // If the player has cards from the same suit, player has to provide (any of these cards)
        if (!filtered.empty())
            return filtered;

        // At this point, the player cannot follow suit
        // filter cards from the trump suit
        filtered = filter_cards(player, trump);

        // If the player does not have cards from the trump suit, they can play any card
        if (filtered.empty()) {
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
            if (!is_partner_leading(trick, static_cast<int>(player[0].player), trump)) {
                return filtered;
            } else {
                return player;
            }
        }

        // At this point, there are played cards from the trump suit
        // If the partner is leading, the player can play any card
        if (is_partner_leading(trick, static_cast<int>(player[0].player), trump)) {
            return player;
        }

        // At this point, the partner is not leading
        // The player has to use a card from the trump suit only if they can beat the opponent's card
        auto higher = filter_cards_higher(player, trump, get_highest_card(trick, trump));

        if (higher.empty()) {
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
        if (card.suit == suit) {
            filtered.emplace_back(card);
        }

    }
    return filtered;
}


CardVector Manille::filter_cards_higher(const CardVector &cards, Suit suit, Card a_card)
{
    CardVector filtered = CardVector();

    for (auto &card: cards) {
        if (card.suit == suit && card > a_card) {
            filtered.emplace_back(card);
        }

    }

    return filtered;
}


Card Manille::get_highest_card(const CardVector &cards, Suit suit)
{
    Card highest = Card();
    for (auto &card: cards) {
        if (card.suit == suit && card > highest) {
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

    return highest_card.player;
}


bool Manille::is_partner_leading(const CardVector &trick, int player_index, Suit suit)
{
    return get_leader(trick, suit) == (player_index + 2) % 4;
}


Suit Manille::choose_trump(const CardVector &player)
{
    int points[4] = {0, 0, 0, 0};
    Suit suits[4] = {Suit::HEARTS, Suit::SPADES, Suit::CLUBS, Suit::DIAMONDS};

    for (auto &card: player) {
        points[static_cast<int>(card.suit) - 1] += card.points();
    }

    return suits[std::distance(points, std::max_element(points, points + 4))];
}


int Manille::determine_winner(const CardVector &trick, Suit trump)
{
    const Suit suit = trick[0].suit;
    if (suit == trump || !filter_cards(trick, trump).empty()) {
        return get_leader(trick, trump);
    } else {
        return get_leader(trick, suit);
    }
}
