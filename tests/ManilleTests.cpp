#include <gtest/gtest.h>
#include "../Manille.hpp"


TEST(Manille, get_highest_card)
{
    CardVector trick = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK)
    };
    EXPECT_EQ(Manille::get_highest_card(trick, HEARTS_MASK), Card(HEARTS_MASK, JACK_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(CLUBS_MASK, NINE_MASK),
            Card(SPADES_MASK, JACK_MASK),
    };
    EXPECT_EQ(Manille::get_highest_card(trick, HEARTS_MASK), Card(HEARTS_MASK, SEVEN_MASK));
    EXPECT_EQ(Manille::get_highest_card(trick, DIAMONDS_MASK), Card(DIAMONDS_MASK, EIGHT_MASK));
    EXPECT_EQ(Manille::get_highest_card(trick, CLUBS_MASK), Card(CLUBS_MASK, NINE_MASK));
    EXPECT_EQ(Manille::get_highest_card(trick, SPADES_MASK), Card(SPADES_MASK, JACK_MASK));

    trick = {
            Card(DIAMONDS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, SEVEN_MASK, 3),
            Card(CLUBS_MASK, SEVEN_MASK, 4),
    };
    EXPECT_EQ(Manille::get_highest_card(trick, HEARTS_MASK), Card(HEARTS_MASK, SEVEN_MASK));
    EXPECT_EQ(Manille::get_highest_card(trick, DIAMONDS_MASK), Card(DIAMONDS_MASK, EIGHT_MASK));
    EXPECT_EQ(Manille::get_highest_card(trick, CLUBS_MASK), Card(CLUBS_MASK, SEVEN_MASK));
}


TEST(Manille, filter_cards)
{
    CardVector deck = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK),
            Card(DIAMONDS_MASK, SEVEN_MASK),
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, NINE_MASK),
            Card(DIAMONDS_MASK, JACK_MASK),
            Card(CLUBS_MASK, SEVEN_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(CLUBS_MASK, NINE_MASK),
            Card(CLUBS_MASK, JACK_MASK),
            Card(SPADES_MASK, SEVEN_MASK),
            Card(SPADES_MASK, EIGHT_MASK),
            Card(SPADES_MASK, NINE_MASK),
            Card(SPADES_MASK, JACK_MASK),
    };

    CardVector expected_hearts = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK),
    };

    CardVector expected_diamonds = {
            Card(DIAMONDS_MASK, SEVEN_MASK),
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, NINE_MASK),
            Card(DIAMONDS_MASK, JACK_MASK),
    };

    CardVector expected_clubs = {
            Card(CLUBS_MASK, SEVEN_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(CLUBS_MASK, NINE_MASK),
            Card(CLUBS_MASK, JACK_MASK),
    };

    CardVector expected_spades = {
            Card(SPADES_MASK, SEVEN_MASK),
            Card(SPADES_MASK, EIGHT_MASK),
            Card(SPADES_MASK, NINE_MASK),
            Card(SPADES_MASK, JACK_MASK),
    };

    EXPECT_EQ(Manille::filter_cards(deck, HEARTS_MASK), expected_hearts);
    EXPECT_EQ(Manille::filter_cards(deck, DIAMONDS_MASK), expected_diamonds);
    EXPECT_EQ(Manille::filter_cards(deck, CLUBS_MASK), expected_clubs);
    EXPECT_EQ(Manille::filter_cards(deck, SPADES_MASK), expected_spades);
}


TEST(Manille, filter_cards_higher)
{
    CardVector deck = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK),
            Card(DIAMONDS_MASK, SEVEN_MASK),
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, NINE_MASK),
            Card(DIAMONDS_MASK, JACK_MASK),
            Card(CLUBS_MASK, ACE_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(CLUBS_MASK, QUEEN_MASK),
            Card(CLUBS_MASK, JACK_MASK),
            Card(SPADES_MASK, SEVEN_MASK),
            Card(SPADES_MASK, EIGHT_MASK),
            Card(SPADES_MASK, KING_MASK),
            Card(SPADES_MASK, ACE_MASK),
            Card(SPADES_MASK, TEN_MASK),
    };

    CardVector expected_hearts = {
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK),
    };

    CardVector expected_diamonds = {
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, NINE_MASK),
            Card(DIAMONDS_MASK, JACK_MASK),
    };

    CardVector expected_clubs = {
            Card(CLUBS_MASK, ACE_MASK),
            Card(CLUBS_MASK, QUEEN_MASK),
            Card(CLUBS_MASK, JACK_MASK),
    };

    CardVector expected_spades = {
            Card(SPADES_MASK, KING_MASK),
            Card(SPADES_MASK, ACE_MASK),
            Card(SPADES_MASK, TEN_MASK),
    };

    EXPECT_EQ(Manille::filter_cards_higher(deck, HEARTS_MASK, {HEARTS_MASK, EIGHT_MASK}), expected_hearts);
    EXPECT_EQ(Manille::filter_cards_higher(deck, DIAMONDS_MASK, {HEARTS_MASK, SEVEN_MASK}), expected_diamonds);
    EXPECT_EQ(Manille::filter_cards_higher(deck, CLUBS_MASK, {HEARTS_MASK, EIGHT_MASK}), expected_clubs);
    EXPECT_EQ(Manille::filter_cards_higher(deck, SPADES_MASK, {HEARTS_MASK, JACK_MASK}), expected_spades);
}


TEST(Manille, choose_trump)
{
    CardVector deck = {
            Card(HEARTS_MASK, TEN_MASK),
            Card(HEARTS_MASK, ACE_MASK),
            Card(CLUBS_MASK, QUEEN_MASK),
            Card(CLUBS_MASK, NINE_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, ACE_MASK),
            Card(DIAMONDS_MASK, QUEEN_MASK),
            Card(SPADES_MASK, TEN_MASK),
    };
    EXPECT_EQ(Manille::choose_trump(deck), HEARTS_MASK);

    deck = {
            Card(HEARTS_MASK, QUEEN_MASK),
            Card(HEARTS_MASK, JACK_MASK),
            Card(CLUBS_MASK, KING_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, SEVEN_MASK),
            Card(SPADES_MASK, QUEEN_MASK),
            Card(SPADES_MASK, NINE_MASK),
            Card(SPADES_MASK, SEVEN_MASK),
    };
    EXPECT_EQ(Manille::choose_trump(deck), HEARTS_MASK);
}


TEST(Manille, get_leader)
{
    CardVector trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(HEARTS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, NINE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4)
    };
    EXPECT_EQ(Manille::get_leader(trick, HEARTS_MASK), 4);


    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, EIGHT_MASK, 2),
            Card(CLUBS_MASK, NINE_MASK, 3),
            Card(SPADES_MASK, JACK_MASK, 4),
    };
    EXPECT_EQ(Manille::get_leader(trick, HEARTS_MASK), 1);
    EXPECT_EQ(Manille::get_leader(trick, DIAMONDS_MASK), 2);
    EXPECT_EQ(Manille::get_leader(trick, CLUBS_MASK), 3);
    EXPECT_EQ(Manille::get_leader(trick, SPADES_MASK), 4);
}


TEST(Manille, is_partner_leading)
{
    CardVector trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(HEARTS_MASK, EIGHT_MASK, 2)
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(HEARTS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, NINE_MASK, 3)
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(HEARTS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, NINE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4)
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, TEN_MASK, 2)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, TEN_MASK, 2),
            Card(SPADES_MASK, ACE_MASK, 3)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, TEN_MASK, 2),
            Card(SPADES_MASK, ACE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4),
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, HEARTS_MASK));

    trick = {
            Card(DIAMONDS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, SEVEN_MASK, 3),
            Card(CLUBS_MASK, SEVEN_MASK, 4),
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 1, HEARTS_MASK));
}


TEST(Manille, determine_winner)
{
    CardVector trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, TEN_MASK, 2),
            Card(SPADES_MASK, ACE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4),
    };
    Suit trump = HEARTS_MASK;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 4);

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, TEN_MASK, 2),
            Card(SPADES_MASK, ACE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4),
    };
    trump = DIAMONDS_MASK;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 2);

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, TEN_MASK, 2),
            Card(SPADES_MASK, ACE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4),
    };
    trump = SPADES_MASK;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 3);

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(HEARTS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, NINE_MASK, 3),
            Card(HEARTS_MASK, JACK_MASK, 4)
    };
    trump = SPADES_MASK;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 4);
}


TEST(Manille, get_score)
{
    CardVector trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1), // 0
            Card(DIAMONDS_MASK, TEN_MASK, 2), // 5
            Card(SPADES_MASK, ACE_MASK, 3), // 4
            Card(HEARTS_MASK, JACK_MASK, 4), // 1
    };
    EXPECT_EQ(Manille::get_score(trick), 10);

    trick = {
            Card(HEARTS_MASK, JACK_MASK, 1),
            Card(DIAMONDS_MASK, QUEEN_MASK, 2),
            Card(SPADES_MASK, KING_MASK, 3),
            Card(HEARTS_MASK, ACE_MASK, 4),
    };
    EXPECT_EQ(Manille::get_score(trick), 10);

    trick = {
            Card(HEARTS_MASK, SEVEN_MASK, 1),
            Card(DIAMONDS_MASK, SEVEN_MASK, 2),
            Card(SPADES_MASK, EIGHT_MASK, 3),
            Card(HEARTS_MASK, NINE_MASK, 4),
    };
    EXPECT_EQ(Manille::get_score(trick), 0);
}


TEST(Manille, get_allowed_cards)
{
    // Non trump trick partner leading
    Suit trump = HEARTS_MASK;
    CardVector trick = {
            Card(DIAMONDS_MASK, EIGHT_MASK, 2),
            Card(HEARTS_MASK, SEVEN_MASK, 3),
            Card(CLUBS_MASK, SEVEN_MASK, 4),
    };

    CardVector player = {
            Card(HEARTS_MASK, ACE_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
            Card(SPADES_MASK, NINE_MASK, 1)
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), player);

    // Non trump trick partner not leading
    trump = HEARTS_MASK;
    trick = {
            Card(CLUBS_MASK, SEVEN_MASK, 3),
            Card(CLUBS_MASK, KING_MASK, 4),
    };

    player = {
            Card(HEARTS_MASK, ACE_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
    };

    CardVector expected = {
            Card(HEARTS_MASK, ACE_MASK, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);
}


TEST(Manille, get_allowed_cards2)
{
    Suit trump = HEARTS_MASK;
    CardVector trick = {
            Card(CLUBS_MASK, TEN_MASK, 2),
            Card(CLUBS_MASK, QUEEN_MASK, 3),
            Card(CLUBS_MASK, NINE_MASK, 4)
    };

    CardVector player = {
            Card(HEARTS_MASK, QUEEN_MASK, 1),
            Card(HEARTS_MASK, JACK_MASK, 1),
            Card(CLUBS_MASK, KING_MASK, 1),
            Card(CLUBS_MASK, EIGHT_MASK, 1),
            Card(DIAMONDS_MASK, SEVEN_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
            Card(SPADES_MASK, NINE_MASK, 1),
            Card(SPADES_MASK, SEVEN_MASK, 1),
    };

    CardVector expected = {
            Card(CLUBS_MASK, KING_MASK, 1),
            Card(CLUBS_MASK, EIGHT_MASK, 1)
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);

    trick = {
            Card(CLUBS_MASK, JACK_MASK, 2),
            Card(HEARTS_MASK, NINE_MASK, 3),
            Card(CLUBS_MASK, SEVEN_MASK, 4)
    };

    player = {
            Card(HEARTS_MASK, QUEEN_MASK, 1),
            Card(HEARTS_MASK, JACK_MASK, 1),
            Card(CLUBS_MASK, KING_MASK, 1),
            Card(DIAMONDS_MASK, SEVEN_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
            Card(SPADES_MASK, NINE_MASK, 1),
            Card(SPADES_MASK, SEVEN_MASK, 1),
    };

    expected = {
            Card(CLUBS_MASK, KING_MASK, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);

    trick = {
            Card(DIAMONDS_MASK, TEN_MASK, 3),
            Card(DIAMONDS_MASK, EIGHT_MASK, 4)
    };

    player = {
            Card(HEARTS_MASK, JACK_MASK, 1),
            Card(DIAMONDS_MASK, SEVEN_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
            Card(SPADES_MASK, NINE_MASK, 1),
            Card(SPADES_MASK, SEVEN_MASK, 1),
    };

    expected = {
            Card(DIAMONDS_MASK, SEVEN_MASK, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);

    trick = {
            Card(DIAMONDS_MASK, JACK_MASK, 3),
            Card(HEARTS_MASK, EIGHT_MASK, 4)
    };

    player = {
            Card(HEARTS_MASK, JACK_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
            Card(SPADES_MASK, NINE_MASK, 1),
            Card(SPADES_MASK, SEVEN_MASK, 1),
    };

    expected = {
            Card(HEARTS_MASK, JACK_MASK, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);
}


TEST(Manille, get_allowed_cards3)
{
    CardVector trick = {};

    CardVector player = {
            Card(HEARTS_MASK, QUEEN_MASK, 1),
            Card(HEARTS_MASK, JACK_MASK, 1),
            Card(CLUBS_MASK, KING_MASK, 1),
            Card(CLUBS_MASK, EIGHT_MASK, 1),
            Card(DIAMONDS_MASK, SEVEN_MASK, 1),
            Card(SPADES_MASK, QUEEN_MASK, 1),
            Card(SPADES_MASK, NINE_MASK, 1),
            Card(SPADES_MASK, SEVEN_MASK, 1),
    };

    EXPECT_EQ(Manille::get_allowed_cards(player, trick, HEARTS_MASK), player);
}