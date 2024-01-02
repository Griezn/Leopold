#include <gtest/gtest.h>
#include "../Card.hpp"


TEST(Card, default_constructor)
{
    Card card;
    EXPECT_EQ(card.suit, Suit::NONE);
    EXPECT_EQ(card.value, Value::NONE);
    EXPECT_EQ(card.player, 0);
    EXPECT_FALSE(card.valid());
}


TEST(Card, constructor_with_suit_and_value)
{
    Card card(Suit::HEARTS, Value::JACK);
    EXPECT_EQ(card.suit, Suit::HEARTS);
    EXPECT_EQ(card.value, Value::JACK);
    EXPECT_EQ(card.player, 0);
    EXPECT_TRUE(card.valid());
}


TEST(Card, compare)
{
    Card card1(Suit::HEARTS, Value::JACK);
    Card card2(Suit::HEARTS, Value::JACK);
    Card card3(Suit::HEARTS, Value::SEVEN);
    Card card4(Suit::DIAMONDS, Value::JACK);

    EXPECT_TRUE(card1 == card2);
    EXPECT_FALSE(card1 == card3);
    EXPECT_FALSE(card1 == card4);

    EXPECT_FALSE(card1 != card2);
    EXPECT_TRUE(card1 != card3);
    EXPECT_TRUE(card1 != card4);

    EXPECT_FALSE(card1 < card2);
    EXPECT_FALSE(card1 < card3);
    EXPECT_FALSE(card1 < card4);

    EXPECT_FALSE(card1 > card2);
    EXPECT_TRUE(card1 > card3);
    EXPECT_FALSE(card1 > card4);

    EXPECT_TRUE(card1 <= card2);
    EXPECT_FALSE(card1 <= card3);
    EXPECT_TRUE(card1 <= card4);

    EXPECT_TRUE(card1 >= card2);
    EXPECT_TRUE(card1 >= card3);
    EXPECT_TRUE(card1 >= card4);
}


TEST(Card, deck)
{
    auto deck = Card::get_deck();
    EXPECT_EQ(deck.size(), 32);
    EXPECT_EQ(deck[0], Card(Suit::HEARTS, Value::SEVEN));
    EXPECT_EQ(deck[31], Card(Suit::DIAMONDS, Value::TEN));
}


TEST(Card, to_int)
{
    auto card = Card(Suit::HEARTS, Value::SEVEN);
    EXPECT_EQ(static_cast<int>(card), 0);

    card = Card(Suit::SPADES, Value::SEVEN);
    EXPECT_EQ(static_cast<int>(card), 8);

    card = Card(Suit::CLUBS, Value::SEVEN);
    EXPECT_EQ(static_cast<int>(card), 16);

    card = Card(Suit::DIAMONDS, Value::TEN);
    EXPECT_EQ(static_cast<int>(card), 31);

    card = Card(Suit::NONE, Value::NONE);
    EXPECT_EQ(static_cast<int>(card), -9);
}


TEST(Card, from_int)
{
    auto card = Card(0);
    EXPECT_EQ(card, Card(Suit::HEARTS, Value::SEVEN));

    card = Card(8);
    EXPECT_EQ(card, Card(Suit::SPADES, Value::SEVEN));

    card = Card(16);
    EXPECT_EQ(card, Card(Suit::CLUBS, Value::SEVEN));

    card = Card(31);
    EXPECT_EQ(card, Card(Suit::DIAMONDS, Value::TEN));

    card = Card(-9);
    EXPECT_EQ(card, Card(Suit::NONE, Value::NONE));
}
