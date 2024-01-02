//
// Created by Seppe Degryse on 01/01/2024.
//
#include <gtest/gtest.h>
#include "../Agent.hpp"
#include "../State.hpp"
#include "../Manille.hpp"


TEST(Agent, alpha_beta)
{
    auto agent = Agent();

    auto deck = Card::get_deck();

    CardVector player_cards = {
        deck[4],
        deck[5],
        deck[6],
        deck[7],
    };

    for (auto &card: player_cards) {
        deck.erase(std::find(deck.begin(), deck.end(), card));
        card.player = 1;
    }
    int size = player_cards.size() * 3;
    deck.erase(deck.begin(), deck.begin() + (deck.size() - size));
    EXPECT_EQ(deck.size(), size);

    auto state = State(player_cards, deck, {}, Manille::choose_trump(player_cards), 1);

    auto val = agent.alpha_beta(state, -60.f, 60.f);
    std::cout << val << std::endl;
    std::cout << agent.count << std::endl;
}
