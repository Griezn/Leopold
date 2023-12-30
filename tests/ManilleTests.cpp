#include <gtest/gtest.h>
#include "../Manille.hpp"
#include "../Card.hpp"


TEST(Manille, get_highest_card)
{
    CardVector trick = {
            Card(Suit::HEARTS, Value::SEVEN),
            Card(Suit::HEARTS, Value::EIGHT),
            Card(Suit::HEARTS, Value::NINE),
            Card(Suit::HEARTS, Value::JACK)
    };
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::HEARTS), Card(Suit::HEARTS, Value::JACK));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN),
            Card(Suit::DIAMONDS, Value::EIGHT),
            Card(Suit::CLUBS, Value::NINE),
            Card(Suit::SPADES, Value::JACK),
    };
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::HEARTS), Card(Suit::HEARTS, Value::SEVEN));
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::DIAMONDS), Card(Suit::DIAMONDS, Value::EIGHT));
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::CLUBS), Card(Suit::CLUBS, Value::NINE));
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::SPADES), Card(Suit::SPADES, Value::JACK));
}


TEST(Manille, filter_cards)
{
    CardVector deck = {
            Card(Suit::HEARTS, Value::SEVEN),
            Card(Suit::HEARTS, Value::EIGHT),
            Card(Suit::HEARTS, Value::NINE),
            Card(Suit::HEARTS, Value::JACK),
            Card(Suit::DIAMONDS, Value::SEVEN),
            Card(Suit::DIAMONDS, Value::EIGHT),
            Card(Suit::DIAMONDS, Value::NINE),
            Card(Suit::DIAMONDS, Value::JACK),
            Card(Suit::CLUBS, Value::SEVEN),
            Card(Suit::CLUBS, Value::EIGHT),
            Card(Suit::CLUBS, Value::NINE),
            Card(Suit::CLUBS, Value::JACK),
            Card(Suit::SPADES, Value::SEVEN),
            Card(Suit::SPADES, Value::EIGHT),
            Card(Suit::SPADES, Value::NINE),
            Card(Suit::SPADES, Value::JACK),
    };

    CardVector expected_hearts = {
            Card(Suit::HEARTS, Value::SEVEN),
            Card(Suit::HEARTS, Value::EIGHT),
            Card(Suit::HEARTS, Value::NINE),
            Card(Suit::HEARTS, Value::JACK),
    };

    CardVector expected_diamonds = {
            Card(Suit::DIAMONDS, Value::SEVEN),
            Card(Suit::DIAMONDS, Value::EIGHT),
            Card(Suit::DIAMONDS, Value::NINE),
            Card(Suit::DIAMONDS, Value::JACK),
    };

    CardVector expected_clubs = {
            Card(Suit::CLUBS, Value::SEVEN),
            Card(Suit::CLUBS, Value::EIGHT),
            Card(Suit::CLUBS, Value::NINE),
            Card(Suit::CLUBS, Value::JACK),
    };

    CardVector expected_spades = {
            Card(Suit::SPADES, Value::SEVEN),
            Card(Suit::SPADES, Value::EIGHT),
            Card(Suit::SPADES, Value::NINE),
            Card(Suit::SPADES, Value::JACK),
    };

    EXPECT_EQ(Manille::filter_cards(deck, Suit::HEARTS), expected_hearts);
    EXPECT_EQ(Manille::filter_cards(deck, Suit::DIAMONDS), expected_diamonds);
    EXPECT_EQ(Manille::filter_cards(deck, Suit::CLUBS), expected_clubs);
    EXPECT_EQ(Manille::filter_cards(deck, Suit::SPADES), expected_spades);
}


TEST(Manille, filter_cards_higher)
{
    CardVector deck = {
            Card(Suit::HEARTS, Value::SEVEN),
            Card(Suit::HEARTS, Value::EIGHT),
            Card(Suit::HEARTS, Value::NINE),
            Card(Suit::HEARTS, Value::JACK),
            Card(Suit::DIAMONDS, Value::SEVEN),
            Card(Suit::DIAMONDS, Value::EIGHT),
            Card(Suit::DIAMONDS, Value::NINE),
            Card(Suit::DIAMONDS, Value::JACK),
            Card(Suit::CLUBS, Value::ACE),
            Card(Suit::CLUBS, Value::EIGHT),
            Card(Suit::CLUBS, Value::QUEEN),
            Card(Suit::CLUBS, Value::JACK),
            Card(Suit::SPADES, Value::SEVEN),
            Card(Suit::SPADES, Value::EIGHT),
            Card(Suit::SPADES, Value::KING),
            Card(Suit::SPADES, Value::ACE),
            Card(Suit::SPADES, Value::TEN),
    };

    CardVector expected_hearts = {
            Card(Suit::HEARTS, Value::NINE),
            Card(Suit::HEARTS, Value::JACK),
    };

    CardVector expected_diamonds = {
            Card(Suit::DIAMONDS, Value::EIGHT),
            Card(Suit::DIAMONDS, Value::NINE),
            Card(Suit::DIAMONDS, Value::JACK),
    };

    CardVector expected_clubs = {
            Card(Suit::CLUBS, Value::ACE),
            Card(Suit::CLUBS, Value::QUEEN),
            Card(Suit::CLUBS, Value::JACK),
    };

    CardVector expected_spades = {
            Card(Suit::SPADES, Value::KING),
            Card(Suit::SPADES, Value::ACE),
            Card(Suit::SPADES, Value::TEN),
    };

    EXPECT_EQ(Manille::filter_cards_higher(deck, Suit::HEARTS, {Suit::HEARTS, Value::EIGHT}), expected_hearts);
    EXPECT_EQ(Manille::filter_cards_higher(deck, Suit::DIAMONDS, {Suit::HEARTS, Value::SEVEN}), expected_diamonds);
    EXPECT_EQ(Manille::filter_cards_higher(deck, Suit::CLUBS, {Suit::HEARTS, Value::EIGHT}), expected_clubs);
    EXPECT_EQ(Manille::filter_cards_higher(deck, Suit::SPADES, {Suit::HEARTS, Value::JACK}), expected_spades);
}