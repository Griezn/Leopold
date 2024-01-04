#include <gtest/gtest.h>
#include "../Card.hpp"


TEST(Card, default_constructor)
{
    Card card;
    EXPECT_EQ(card.suit(), 3 << 4);
    EXPECT_EQ(card.value(), 15);
    EXPECT_EQ(card.player(), 4);
    EXPECT_FALSE(card.valid());
}


TEST(Card, constructor_with_suit_and_value)
{
    Card card(HEARTS_MASK, JACK_MASK);
    EXPECT_EQ(card.suit(), HEARTS_MASK);
    EXPECT_EQ(card.value(), JACK_MASK);
    EXPECT_EQ(card.player(), 1);
    EXPECT_TRUE(card.valid());
}


TEST(Card, compare)
{
    Card card1(HEARTS_MASK, JACK_MASK);
    Card card2(HEARTS_MASK, JACK_MASK);
    Card card3(HEARTS_MASK, SEVEN_MASK);
    Card card4(DIAMONDS_MASK, JACK_MASK);

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
    EXPECT_EQ(deck[0], Card(HEARTS_MASK, TEN_MASK));
    EXPECT_EQ(deck[31], Card(DIAMONDS_MASK, SEVEN_MASK));
}


TEST(Card, to_int)
{
    EXPECT_EQ(int(Card(HEARTS_MASK, TEN_MASK)), 0);
    EXPECT_EQ(int(Card(HEARTS_MASK, ACE_MASK)), 4);
    EXPECT_EQ(int(Card(HEARTS_MASK, KING_MASK)), 8);
    EXPECT_EQ(int(Card(HEARTS_MASK, QUEEN_MASK)), 12);
    EXPECT_EQ(int(Card(HEARTS_MASK, JACK_MASK)), 16);
    EXPECT_EQ(int(Card(HEARTS_MASK, NINE_MASK)), 20);
    EXPECT_EQ(int(Card(HEARTS_MASK, EIGHT_MASK)), 24);
    EXPECT_EQ(int(Card(HEARTS_MASK, SEVEN_MASK)), 28);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, SEVEN_MASK)), 31);
}


TEST(Card, from_int)
{
    auto card = Card(0);
    EXPECT_EQ(card, Card(HEARTS_MASK,TEN_MASK));

    card = Card(4);
    EXPECT_EQ(card, Card(HEARTS_MASK, ACE_MASK));

    card = Card(8);
    EXPECT_EQ(card, Card(HEARTS_MASK, KING_MASK));

    card = Card(12);
    EXPECT_EQ(card, Card(HEARTS_MASK, QUEEN_MASK));

    card = Card(16);
    EXPECT_EQ(card, Card(HEARTS_MASK, JACK_MASK));

    card = Card(20);
    EXPECT_EQ(card, Card(HEARTS_MASK, NINE_MASK));

    card = Card(24);
    EXPECT_EQ(card, Card(HEARTS_MASK, EIGHT_MASK));

    card = Card(28);
    EXPECT_EQ(card, Card(HEARTS_MASK, SEVEN_MASK));

    card = Card(31);
    EXPECT_EQ(card, Card(DIAMONDS_MASK, SEVEN_MASK));
}


TEST(Card, set_player)
{
    auto card = Card(HEARTS_MASK, SEVEN_MASK);
    EXPECT_EQ(card.player(), 1);
    card.set_player(1);
    EXPECT_EQ(card.player(), 1);

    card = Card(SPADES_MASK, SEVEN_MASK, 4);
    EXPECT_EQ(card.player(), 4);
}


TEST(Card, player)
{
    auto card = Card(HEARTS_MASK, SEVEN_MASK);
    EXPECT_EQ(card.player(), 1);
    card.set_player(3);
    EXPECT_EQ(card.player(), 3);

    card = Card(SPADES_MASK, SEVEN_MASK, 4);
    EXPECT_EQ(card.player(), 4);
}
