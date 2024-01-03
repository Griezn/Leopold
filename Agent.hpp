//
// Created by Seppe Degryse on 29/12/2023.
//

#ifndef LEOPOLD_AGENT_HPP
#define LEOPOLD_AGENT_HPP

#include <vector>

struct State;
struct Card;
enum class Suit;
enum class Value;

typedef std::vector<Card> CardVector;

struct Agent {
    Card choose_card(const CardVector &player, const CardVector &trick, Suit trump);

    float alpha_beta(State *state, float alpha, float beta);

private:

    float maximize(State *state, float alpha, float beta);
    float minimize(State *state, float alpha, float beta);
};


#endif //LEOPOLD_AGENT_HPP
