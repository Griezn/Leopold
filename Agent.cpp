//
// Created by Seppe Degryse on 29/12/2023.
//

#include <taskflow/taskflow.hpp>
#include "Agent.hpp"
#include "State.hpp"


float Agent::alpha_beta(State *state, float alpha, float beta)
{
    if (state->is_terminal()) {
        return state->get_score();
    }

    if (state->get_player() == 1 || state->get_player() == 3) {
        return maximize(state, alpha, beta);
    } else {
        return minimize(state, alpha, beta);
    }
}


float Agent::maximize(State *state, float alpha, float beta)
{
    float value = -60.f;
    for (auto child : state->get_children()) {
        value = std::max(value, alpha_beta(child, alpha, beta));
        delete child;
        if (value > beta) {
            break;
        }
        alpha = std::max(alpha, value);
    }

    return value;
}


float Agent::minimize(State *state, float alpha, float beta)
{
    float value = 60.f;
    for (auto child : state->get_children()) {
        value = std::min(value, alpha_beta(child, alpha, beta));
        delete child;
        if (value < beta) {
            break;
        }
        beta = std::min(beta, value);
    }

    return value;
}


Card Agent::choose_card(const CardVector &player, const CardVector &trick, Suit trump)
{
    // initialize state
    auto deck = Card::get_deck();
    for (auto &card: player) {
        deck.erase(std::find(deck.begin(), deck.end(), card));
    }
    int size = player.size() * 3;
    deck.erase(deck.begin(), deck.begin() + (deck.size() - size));
    auto state = State(player, deck, trick, trump, 1);

    //calculate
    tf::Executor executor;
    std::vector<std::future<float>> f;

    for (auto child : state.get_children()) {
        f.emplace_back(executor.async([child, this] { return Agent::alpha_beta(child, -60.f, 60.f); }));
    }
    // wait
    executor.wait_for_all();

    return {};
}
