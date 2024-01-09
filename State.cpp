//
// Created by Seppe Degryse on 31/12/2023.
//

#include "State.hpp"
#include "Card.hpp"
#include "Manille.hpp"


bool State::is_terminal() const
{
    return player_cards.none() && remaining_cards.none();
}


float State::get_score() const
{
    return score/2;
}


StateVector State::get_children() const
{
    auto children = StateVector();
    if (player == 1) {
        children.reserve(player_cards.count());
        generate_children_player(children);
    } else {
        children.reserve(remaining_cards.count());
        generate_children_opponent(children);
    }

    return children;
}


int State::get_next_player() const
{
    auto value = player + 1;
    if (player == 4) {
        value = 1;
    }
    return value;
}


void State::generate_children_opponent(StateVector &children) const
{
    auto allowed_cards = Manille::get_allowed_cards(remaining_cards, trick_cards, player, trump);

    for (int i = 0; i < CARD_COUNT; ++i) {
        if (!allowed_cards[i]) {
            continue;
        }

        auto child = new State(*this);

        child->trick_cards.emplace_back(i);
        child->trick_cards.back().set_player(player);
        child->remaining_cards[i] = false;
        child->player = get_next_player();

        if (child->trick_cards.size() == 4) {
            complete_trick(child);
        }

        children.emplace_back(child);
    }
}


void State::generate_children_player(StateVector &children) const
{
    auto allowed_cards = Manille::get_allowed_cards(player_cards, trick_cards, player, trump);

    for (int i = 0; i < CARD_COUNT; ++i) {
        if (!allowed_cards[i]) {
            continue;
        }

        auto child = new State(*this);
        child->trick_cards.emplace_back(i);
        child->trick_cards.back().set_player(player);
        child->player_cards[i] = false;
        child->player = get_next_player();

        if (child->trick_cards.size() == 4) {
            complete_trick(child);
        }

        children.emplace_back(child);
    }
}


void State::complete_trick(State *child) const
{
    int winner = Manille::determine_winner(child->trick_cards, trump);
    if (winner == 1 || winner == 3)
        child->score += Manille::get_score(child->trick_cards);
    else
        child->score -= Manille::get_score(child->trick_cards);

    child->trick_cards.clear();
}


State::State(const CardVector& player_cards, const CardVector& remaining_cards, CardVector trick_cards, Suit trump, int player) :
        player_cards(),
        remaining_cards(),
        trick_cards(std::move(trick_cards)),
        trump(trump),
        player(player),
        score(0)
{
    for (auto &card: player_cards) {
        this->player_cards[static_cast<int>(card)] = true;
    }

    for (auto &card: remaining_cards) {
        this->remaining_cards[static_cast<int>(card)] = true;
    }
    trick_cards.reserve(4);
}
