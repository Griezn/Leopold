//
// Created by Seppe Degryse on 29/12/2023.
//

#include <iostream>
#include "Agent.hpp"
#include "State.hpp"


float Agent::alpha_beta(const State &state, float alpha, float beta)
{
    if (state.is_terminal()) {
        count++;
        return state.get_score();
    }

    if (state.get_player() == 1 || state.get_player() == 3) {
        return maximize(state, alpha, beta);
    } else {
        return minimize(state, alpha, beta);
    }
}


float Agent::maximize(const State &state, float alpha, float beta)
{
    float value = -60.f;
    for (const auto &child : state.get_children()) {
        value = std::max(value, alpha_beta(child, alpha, beta));
        alpha = std::max(alpha, value);
        if (value >= beta) {
            break;
        }
    }
    return value;
}


float Agent::minimize(const State &state, float alpha, float beta)
{
    float value = 60.f;
    for (auto &child : state.get_children()) {
        value = std::min(value, alpha_beta(child, alpha, beta));
        beta = std::min(beta, value);
        if (value >= beta) {
            break;
        }
    }
    return value;
}


Card Agent::choose_card(const CardVector &player, const CardVector &trick, Suit trump)
{
    auto deck = Card::get_deck();
    for (auto &card: player) {
        deck.erase(std::find(deck.begin(), deck.end(), card));
    }
    int size = player.size() * 3;
    deck.erase(deck.begin(), deck.begin() + (deck.size() - size));
    auto state = State(player, deck, trick, trump, 1);

    std::vector<float> scores;
    for (const auto &child : state.get_children()) {
        scores.push_back(alpha_beta(child, -60.f, 60.f));
    }

    return player[std::distance(scores.begin(), std::max_element(scores.begin(), scores.end()))];
}
