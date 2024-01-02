#include <gtest/gtest.h>
#include "../State.hpp"


TEST(State, is_terminal)
{
    CardVector player_cards;
    CardVector remaining_cards;
    CardVector trick_cards;

    State state(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 1);
    EXPECT_TRUE(state.is_terminal());

    player_cards = CardVector{Card(Suit::HEARTS, Value::JACK)};
    state = State(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 1);
    EXPECT_FALSE(state.is_terminal());


    remaining_cards = CardVector{Card(Suit::HEARTS, Value::JACK)};
    trick_cards = CardVector{Card(Suit::HEARTS, Value::JACK), Card(Suit::HEARTS, Value::JACK),
                             Card(Suit::HEARTS, Value::JACK), Card(Suit::HEARTS, Value::JACK)};
    state = State(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 1);
    EXPECT_FALSE(state.is_terminal());
}


TEST(State, get_next_player)
{
    CardVector player_cards;
    CardVector remaining_cards;
    CardVector trick_cards;

    State state(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 1);
    EXPECT_EQ(state.get_next_player(), 2);

    state = State(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 2);
    EXPECT_EQ(state.get_next_player(), 3);

    state = State(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 3);
    EXPECT_EQ(state.get_next_player(), 4);

    state = State(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 4);
    EXPECT_EQ(state.get_next_player(), 1);
}


TEST(State, get_children_player)
{
    CardVector player_cards = CardVector{Card(Suit::HEARTS, Value::JACK, 1)};
    CardVector remaining_cards;
    CardVector trick_cards = CardVector{Card(Suit::HEARTS, Value::SEVEN, 2), Card(Suit::HEARTS, Value::EIGHT, 3),
                                        Card(Suit::HEARTS, Value::NINE, 4)};

    State state(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 1);

    auto children = state.get_children();
    EXPECT_EQ(children.size(), 1);
    auto child = children[0];

    EXPECT_TRUE(child.is_terminal());
    EXPECT_EQ(child.get_score(), 0.5);
    EXPECT_EQ(child.get_player(), 2);
}


TEST(State, get_children_opp)
{
    CardVector player_cards;
    CardVector remaining_cards = CardVector{Card(Suit::HEARTS, Value::JACK)};
    CardVector trick_cards = CardVector{Card(Suit::HEARTS, Value::SEVEN, 1), Card(Suit::HEARTS, Value::EIGHT, 2),
                                        Card(Suit::HEARTS, Value::NINE, 3)};

    State state(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 4);

    auto children = state.get_children();
    EXPECT_EQ(children.size(), 1);

    auto child = children[0];
    EXPECT_TRUE(child.is_terminal());
    EXPECT_EQ(child.get_score(), -0.5);
    EXPECT_EQ(child.get_player(), 1);
}


TEST(State, get_children)
{
    CardVector player_cards = CardVector{Card(Suit::HEARTS, Value::TEN, 1),};
    CardVector remaining_cards = CardVector{Card(Suit::HEARTS, Value::JACK), Card(Suit::HEARTS, Value::NINE),
                                            Card(Suit::HEARTS, Value::ACE)};
    CardVector trick_cards = CardVector{};

    State state(player_cards, remaining_cards, trick_cards, Suit::HEARTS, 1);

    auto children = state.get_children();
    EXPECT_EQ(children.size(), 1);

    auto child = children[0];
    EXPECT_FALSE(child.is_terminal());
    EXPECT_EQ(child.get_score(), 0);
    EXPECT_EQ(child.get_player(), 2);

    children = child.get_children();
    EXPECT_EQ(children.size(), 3);

    child = children[0];
    EXPECT_FALSE(child.is_terminal());
    EXPECT_EQ(child.get_score(), 0);
    EXPECT_EQ(child.get_player(), 3);

    children = child.get_children();
    EXPECT_EQ(children.size(), 2);

    child = children[0];
    EXPECT_FALSE(child.is_terminal());
    EXPECT_EQ(child.get_score(), 0);
    EXPECT_EQ(child.get_player(), 4);

    children = child.get_children();
    EXPECT_EQ(children.size(), 1);

    child = children[0];
    EXPECT_TRUE(child.is_terminal());
    EXPECT_EQ(child.get_score(), 5);
    EXPECT_EQ(child.get_player(), 1);
}