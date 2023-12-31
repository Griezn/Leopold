//
// Created by Seppe Degryse on 31/12/2023.
//

#include "State.hpp"
#include "Card.hpp"
#include "Manille.hpp"


bool State::is_terminal() const
{
    return player_cards.empty() && remaining_cards.empty();
}


int State::get_score() const
{
    return score;
}


StateVector State::get_children() const
{
    auto children = StateVector();
    if (player == 1) {
        generate_children_player(children);
    } else {
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
    for (auto card: remaining_cards) {
        card.player = player;
        auto child = State(*this);
        child.trick_cards.push_back(card);
        child.remaining_cards.erase(std::find(child.remaining_cards.begin(), child.remaining_cards.end(), card));
        child.player = get_next_player();

        if (child.trick_cards.size() == 4) {
            complete_trick(child);
        }

        children.push_back(child);
    }
}


void State::generate_children_player(StateVector &children) const
{
    for (auto card: player_cards) {
        auto child = State(*this);
        child.trick_cards.push_back(card);
        child.player_cards.erase(std::find(child.player_cards.begin(), child.player_cards.end(), card));
        child.player = get_next_player();

        if (child.trick_cards.size() == 4) {
            complete_trick(child);
        }

        children.push_back(child);
    }
}


void State::complete_trick(State &child) const
{
    if (Manille::determine_winner(child.trick_cards, trump) == 1 ||
        Manille::determine_winner(child.trick_cards, trump) == 3)
        child.score += Manille::get_score(child.trick_cards);
    else
        child.score -= Manille::get_score(child.trick_cards);

    child.trick_cards.clear();
}


State::State(CardVector player_cards, CardVector remaining_cards, CardVector trick_cards, Suit trump, int player) :
        player_cards(std::move(player_cards)),
        remaining_cards(std::move(remaining_cards)),
        trick_cards(std::move(trick_cards)),
        trump(trump),
        player(player),
        score(0)
{
}
