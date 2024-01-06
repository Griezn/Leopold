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
    EXPECT_EQ(int(Card(SPADES_MASK, TEN_MASK)), 1);
    EXPECT_EQ(int(Card(CLUBS_MASK, TEN_MASK)), 2);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, TEN_MASK)), 3);

    EXPECT_EQ(int(Card(HEARTS_MASK, ACE_MASK)), 4);
    EXPECT_EQ(int(Card(SPADES_MASK, ACE_MASK)), 5);
    EXPECT_EQ(int(Card(CLUBS_MASK, ACE_MASK)), 6);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, ACE_MASK)), 7);

    EXPECT_EQ(int(Card(HEARTS_MASK, KING_MASK)), 8);
    EXPECT_EQ(int(Card(SPADES_MASK, KING_MASK)), 9);
    EXPECT_EQ(int(Card(CLUBS_MASK, KING_MASK)), 10);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, KING_MASK)), 11);

    EXPECT_EQ(int(Card(HEARTS_MASK, QUEEN_MASK)), 12);
    EXPECT_EQ(int(Card(SPADES_MASK, QUEEN_MASK)), 13);
    EXPECT_EQ(int(Card(CLUBS_MASK, QUEEN_MASK)), 14);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, QUEEN_MASK)), 15);

    EXPECT_EQ(int(Card(HEARTS_MASK, JACK_MASK)), 16);
    EXPECT_EQ(int(Card(SPADES_MASK, JACK_MASK)), 17);
    EXPECT_EQ(int(Card(CLUBS_MASK, JACK_MASK)), 18);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, JACK_MASK)), 19);

    EXPECT_EQ(int(Card(HEARTS_MASK, NINE_MASK)), 20);
    EXPECT_EQ(int(Card(SPADES_MASK, NINE_MASK)), 21);
    EXPECT_EQ(int(Card(CLUBS_MASK, NINE_MASK)), 22);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, NINE_MASK)), 23);

    EXPECT_EQ(int(Card(HEARTS_MASK, EIGHT_MASK)), 24);
    EXPECT_EQ(int(Card(SPADES_MASK, EIGHT_MASK)), 25);
    EXPECT_EQ(int(Card(CLUBS_MASK, EIGHT_MASK)), 26);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, EIGHT_MASK)), 27);

    EXPECT_EQ(int(Card(HEARTS_MASK, SEVEN_MASK)), 28);
    EXPECT_EQ(int(Card(SPADES_MASK, SEVEN_MASK)), 29);
    EXPECT_EQ(int(Card(CLUBS_MASK, SEVEN_MASK)), 30);
    EXPECT_EQ(int(Card(DIAMONDS_MASK, SEVEN_MASK)), 31);
}


TEST(Card, from_int)
{
    EXPECT_EQ(Card(0), Card(HEARTS_MASK,TEN_MASK));
    EXPECT_EQ(Card(1), Card(SPADES_MASK, TEN_MASK));
    EXPECT_EQ(Card(2), Card(CLUBS_MASK, TEN_MASK));
    EXPECT_EQ(Card(3), Card(DIAMONDS_MASK, TEN_MASK));

    EXPECT_EQ(Card(4), Card(HEARTS_MASK, ACE_MASK));
    EXPECT_EQ(Card(5), Card(SPADES_MASK, ACE_MASK));
    EXPECT_EQ(Card(6), Card(CLUBS_MASK, ACE_MASK));
    EXPECT_EQ(Card(7), Card(DIAMONDS_MASK, ACE_MASK));

    EXPECT_EQ(Card(8), Card(HEARTS_MASK, KING_MASK));

    EXPECT_EQ(Card(12), Card(HEARTS_MASK, QUEEN_MASK));

    EXPECT_EQ(Card(16), Card(HEARTS_MASK, JACK_MASK));
    EXPECT_EQ(Card(17), Card(SPADES_MASK, JACK_MASK));
    EXPECT_EQ(Card(18), Card(CLUBS_MASK, JACK_MASK));
    EXPECT_EQ(Card(19), Card(DIAMONDS_MASK, JACK_MASK));

    EXPECT_EQ(Card(20), Card(HEARTS_MASK, NINE_MASK));

    EXPECT_EQ(Card(24), Card(HEARTS_MASK, EIGHT_MASK));
    EXPECT_EQ(Card(25), Card(SPADES_MASK, EIGHT_MASK));
    EXPECT_EQ(Card(26), Card(CLUBS_MASK, EIGHT_MASK));
    EXPECT_EQ(Card(27), Card(DIAMONDS_MASK, EIGHT_MASK));

    EXPECT_EQ(Card(28), Card(HEARTS_MASK, SEVEN_MASK));

    EXPECT_EQ(Card(31), Card(DIAMONDS_MASK, SEVEN_MASK));
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
