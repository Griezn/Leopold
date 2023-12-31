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

    trick = {
            Card(Suit::DIAMONDS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::SEVEN, 3),
            Card(Suit::CLUBS, Value::SEVEN, 4),
    };
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::HEARTS), Card(Suit::HEARTS, Value::SEVEN));
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::DIAMONDS), Card(Suit::DIAMONDS, Value::EIGHT));
    EXPECT_EQ(Manille::get_highest_card(trick, Suit::CLUBS), Card(Suit::CLUBS, Value::SEVEN));
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


TEST(Manille, choose_trump)
{
    CardVector deck = {
            Card(Suit::HEARTS, Value::TEN),
            Card(Suit::HEARTS, Value::ACE),
            Card(Suit::CLUBS, Value::QUEEN),
            Card(Suit::CLUBS, Value::NINE),
            Card(Suit::CLUBS, Value::EIGHT),
            Card(Suit::DIAMONDS, Value::ACE),
            Card(Suit::DIAMONDS, Value::QUEEN),
            Card(Suit::SPADES, Value::TEN),
    };
    EXPECT_EQ(Manille::choose_trump(deck), Suit::HEARTS);

    deck = {
            Card(Suit::HEARTS, Value::QUEEN),
            Card(Suit::HEARTS, Value::JACK),
            Card(Suit::CLUBS, Value::KING),
            Card(Suit::CLUBS, Value::EIGHT),
            Card(Suit::DIAMONDS, Value::SEVEN),
            Card(Suit::SPADES, Value::QUEEN),
            Card(Suit::SPADES, Value::NINE),
            Card(Suit::SPADES, Value::SEVEN),
    };
    EXPECT_EQ(Manille::choose_trump(deck), Suit::HEARTS);
}


TEST(Manille, get_leader)
{
    CardVector trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::HEARTS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::NINE, 3),
            Card(Suit::HEARTS, Value::JACK, 4)
    };
    EXPECT_EQ(Manille::get_leader(trick, Suit::HEARTS), 4);


    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::EIGHT, 2),
            Card(Suit::CLUBS, Value::NINE, 3),
            Card(Suit::SPADES, Value::JACK, 4),
    };
    EXPECT_EQ(Manille::get_leader(trick, Suit::HEARTS), 1);
    EXPECT_EQ(Manille::get_leader(trick, Suit::DIAMONDS), 2);
    EXPECT_EQ(Manille::get_leader(trick, Suit::CLUBS), 3);
    EXPECT_EQ(Manille::get_leader(trick, Suit::SPADES), 4);
}


TEST(Manille, is_partner_leading)
{
    CardVector trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::HEARTS, Value::EIGHT, 2)
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::HEARTS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::NINE, 3)
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::HEARTS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::NINE, 3),
            Card(Suit::HEARTS, Value::JACK, 4)
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::TEN, 2)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::TEN, 2),
            Card(Suit::SPADES, Value::ACE, 3)
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::TEN, 2),
            Card(Suit::SPADES, Value::ACE, 3),
            Card(Suit::HEARTS, Value::JACK, 4),
    };
    EXPECT_FALSE(Manille::is_partner_leading(trick, 3, Suit::HEARTS));

    trick = {
            Card(Suit::DIAMONDS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::SEVEN, 3),
            Card(Suit::CLUBS, Value::SEVEN, 4),
    };
    EXPECT_TRUE(Manille::is_partner_leading(trick, 1, Suit::HEARTS));
}


TEST(Manille, determine_winner)
{
    CardVector trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::TEN, 2),
            Card(Suit::SPADES, Value::ACE, 3),
            Card(Suit::HEARTS, Value::JACK, 4),
    };
    Suit trump = Suit::HEARTS;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 4);

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::TEN, 2),
            Card(Suit::SPADES, Value::ACE, 3),
            Card(Suit::HEARTS, Value::JACK, 4),
    };
    trump = Suit::DIAMONDS;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 2);

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::TEN, 2),
            Card(Suit::SPADES, Value::ACE, 3),
            Card(Suit::HEARTS, Value::JACK, 4),
    };
    trump = Suit::SPADES;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 3);

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::HEARTS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::NINE, 3),
            Card(Suit::HEARTS, Value::JACK, 4)
    };
    trump = Suit::SPADES;
    EXPECT_EQ(Manille::determine_winner(trick, trump), 4);
}


TEST(Manille, get_score)
{
    CardVector trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1), // 0
            Card(Suit::DIAMONDS, Value::TEN, 2), // 5
            Card(Suit::SPADES, Value::ACE, 3), // 4
            Card(Suit::HEARTS, Value::JACK, 4), // 1
    };
    EXPECT_EQ(Manille::get_score(trick), 10);

    trick = {
            Card(Suit::HEARTS, Value::JACK, 1),
            Card(Suit::DIAMONDS, Value::QUEEN, 2),
            Card(Suit::SPADES, Value::KING, 3),
            Card(Suit::HEARTS, Value::ACE, 4),
    };
    EXPECT_EQ(Manille::get_score(trick), 10);

    trick = {
            Card(Suit::HEARTS, Value::SEVEN, 1),
            Card(Suit::DIAMONDS, Value::SEVEN, 2),
            Card(Suit::SPADES, Value::EIGHT, 3),
            Card(Suit::HEARTS, Value::NINE, 4),
    };
    EXPECT_EQ(Manille::get_score(trick), 0);
}


TEST(Manille, get_allowed_cards)
{
    // Non trump trick partner leading
    Suit trump = Suit::HEARTS;
    CardVector trick = {
            Card(Suit::DIAMONDS, Value::EIGHT, 2),
            Card(Suit::HEARTS, Value::SEVEN, 3),
            Card(Suit::CLUBS, Value::SEVEN, 4),
    };

    CardVector player = {
            Card(Suit::HEARTS, Value::ACE, 1),
            Card(Suit::SPADES, Value::QUEEN, 1),
            Card(Suit::SPADES, Value::NINE, 1)
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), player);

    // Non trump trick partner not leading
    trump = Suit::HEARTS;
    trick = {
            Card(Suit::CLUBS, Value::SEVEN, 3),
            Card(Suit::CLUBS, Value::KING, 4),
    };

    player = {
            Card(Suit::HEARTS, Value::ACE, 1),
            Card(Suit::SPADES, Value::QUEEN, 1),
    };

    CardVector expected = {
            Card(Suit::HEARTS, Value::ACE, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);
}


TEST(Manille, get_allowed_cards2)
{
    Suit trump = Suit::HEARTS;
    CardVector trick = {
            Card(Suit::CLUBS, Value::TEN, 2),
            Card(Suit::CLUBS, Value::QUEEN, 3),
            Card(Suit::CLUBS, Value::NINE, 4)
    };

    CardVector player = {
            Card(Suit::HEARTS, Value::QUEEN, 1),
            Card(Suit::HEARTS, Value::JACK, 1),
            Card(Suit::CLUBS, Value::KING, 1),
            Card(Suit::CLUBS, Value::EIGHT, 1),
            Card(Suit::DIAMONDS, Value::SEVEN, 1),
            Card(Suit::SPADES, Value::QUEEN, 1),
            Card(Suit::SPADES, Value::NINE, 1),
            Card(Suit::SPADES, Value::SEVEN, 1),
    };

    CardVector expected = {
            Card(Suit::CLUBS, Value::KING, 1),
            Card(Suit::CLUBS, Value::EIGHT, 1)
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);

    trick = {
            Card(Suit::CLUBS, Value::JACK, 2),
            Card(Suit::HEARTS, Value::NINE, 3),
            Card(Suit::CLUBS, Value::SEVEN, 4)
    };

    player = {
            Card(Suit::HEARTS, Value::QUEEN, 1),
            Card(Suit::HEARTS, Value::JACK, 1),
            Card(Suit::CLUBS, Value::KING, 1),
            Card(Suit::DIAMONDS, Value::SEVEN, 1),
            Card(Suit::SPADES, Value::QUEEN, 1),
            Card(Suit::SPADES, Value::NINE, 1),
            Card(Suit::SPADES, Value::SEVEN, 1),
    };

    expected = {
            Card(Suit::CLUBS, Value::KING, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);

    trick = {
            Card(Suit::DIAMONDS, Value::TEN, 3),
            Card(Suit::DIAMONDS, Value::EIGHT, 4)
    };

    player = {
            Card(Suit::HEARTS, Value::JACK, 1),
            Card(Suit::DIAMONDS, Value::SEVEN, 1),
            Card(Suit::SPADES, Value::QUEEN, 1),
            Card(Suit::SPADES, Value::NINE, 1),
            Card(Suit::SPADES, Value::SEVEN, 1),
    };

    expected = {
            Card(Suit::DIAMONDS, Value::SEVEN, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);

    trick = {
            Card(Suit::DIAMONDS, Value::JACK, 3),
            Card(Suit::HEARTS, Value::EIGHT, 4)
    };

    player = {
            Card(Suit::HEARTS, Value::JACK, 1),
            Card(Suit::SPADES, Value::QUEEN, 1),
            Card(Suit::SPADES, Value::NINE, 1),
            Card(Suit::SPADES, Value::SEVEN, 1),
    };

    expected = {
            Card(Suit::HEARTS, Value::JACK, 1),
    };
    EXPECT_EQ(Manille::get_allowed_cards(player, trick, trump), expected);
}