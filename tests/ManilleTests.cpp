#include <gtest/gtest.h>
#include "../Manille.hpp"


std::bitset<32> vector_to_bitset(const CardVector &cards)
{
    std::bitset<32> result;
    for (const auto &card : cards) {
        result[(int) card] = true;
    }
    return result;
}


TEST(Manille, vector_to_bitset)
{
    CardVector trick = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK)
    };
    std::bitset<32> expected = 0b0001'0001'0001'0001'0000'0000'0000'0000;
    EXPECT_EQ(vector_to_bitset(trick), expected);

    trick = {
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(SPADES_MASK, EIGHT_MASK),
    };
    expected = 0b0000'1111'0000'0000'0000'0000'0000'0000;
    EXPECT_EQ(vector_to_bitset(trick), expected);
}


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
    CardBitset deck_bitset = vector_to_bitset(deck);

    CardVector expected_hearts = {
            Card(HEARTS_MASK, SEVEN_MASK),
            Card(HEARTS_MASK, EIGHT_MASK),
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK),
    };
    CardBitset expected_hearts_bitset = vector_to_bitset(expected_hearts);

    CardVector expected_diamonds = {
            Card(DIAMONDS_MASK, SEVEN_MASK),
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, NINE_MASK),
            Card(DIAMONDS_MASK, JACK_MASK),
    };
    CardBitset expected_diamonds_bitset = vector_to_bitset(expected_diamonds);

    CardVector expected_clubs = {
            Card(CLUBS_MASK, SEVEN_MASK),
            Card(CLUBS_MASK, EIGHT_MASK),
            Card(CLUBS_MASK, NINE_MASK),
            Card(CLUBS_MASK, JACK_MASK),
    };
    CardBitset expected_clubs_bitset = vector_to_bitset(expected_clubs);

    CardVector expected_spades = {
            Card(SPADES_MASK, SEVEN_MASK),
            Card(SPADES_MASK, EIGHT_MASK),
            Card(SPADES_MASK, NINE_MASK),
            Card(SPADES_MASK, JACK_MASK),
    };
    CardBitset expected_spades_bitset = vector_to_bitset(expected_spades);

    EXPECT_EQ(Manille::filter_cards(deck, HEARTS_MASK), expected_hearts);
    EXPECT_EQ(Manille::filter_cards(deck, DIAMONDS_MASK), expected_diamonds);
    EXPECT_EQ(Manille::filter_cards(deck, CLUBS_MASK), expected_clubs);
    EXPECT_EQ(Manille::filter_cards(deck, SPADES_MASK), expected_spades);

    EXPECT_EQ(Manille::filter_bitset(deck_bitset, HEARTS_MASK), expected_hearts_bitset);
    EXPECT_EQ(Manille::filter_bitset(deck_bitset, DIAMONDS_MASK), expected_diamonds_bitset);
    EXPECT_EQ(Manille::filter_bitset(deck_bitset, CLUBS_MASK), expected_clubs_bitset);
    EXPECT_EQ(Manille::filter_bitset(deck_bitset, SPADES_MASK), expected_spades_bitset);
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
    CardBitset deck_bitset = vector_to_bitset(deck);

    CardVector expected_hearts = {
            Card(HEARTS_MASK, NINE_MASK),
            Card(HEARTS_MASK, JACK_MASK),
    };
    CardBitset expected_hearts_bitset = vector_to_bitset(expected_hearts);

    CardVector expected_diamonds = {
            Card(DIAMONDS_MASK, EIGHT_MASK),
            Card(DIAMONDS_MASK, NINE_MASK),
            Card(DIAMONDS_MASK, JACK_MASK),
    };
    CardBitset expected_diamonds_bitset = vector_to_bitset(expected_diamonds);

    CardVector expected_clubs = {
            Card(CLUBS_MASK, ACE_MASK),
            Card(CLUBS_MASK, QUEEN_MASK),
            Card(CLUBS_MASK, JACK_MASK),
    };
    CardBitset expected_clubs_bitset = vector_to_bitset(expected_clubs);

    CardVector expected_spades = {
            Card(SPADES_MASK, KING_MASK),
            Card(SPADES_MASK, ACE_MASK),
            Card(SPADES_MASK, TEN_MASK),
    };
    CardBitset expected_spades_bitset = vector_to_bitset(expected_spades);

    EXPECT_EQ(Manille::filter_cards_higher(deck, HEARTS_MASK, {HEARTS_MASK, EIGHT_MASK}), expected_hearts);
    EXPECT_EQ(Manille::filter_cards_higher(deck, DIAMONDS_MASK, {HEARTS_MASK, SEVEN_MASK}), expected_diamonds);
    EXPECT_EQ(Manille::filter_cards_higher(deck, CLUBS_MASK, {HEARTS_MASK, EIGHT_MASK}), expected_clubs);
    EXPECT_EQ(Manille::filter_cards_higher(deck, SPADES_MASK, {HEARTS_MASK, JACK_MASK}), expected_spades);

    EXPECT_EQ(Manille::filter_bitset_higher(deck_bitset, HEARTS_MASK, {HEARTS_MASK, EIGHT_MASK}), expected_hearts_bitset);
    EXPECT_EQ(Manille::filter_bitset_higher(deck_bitset, DIAMONDS_MASK, {HEARTS_MASK, SEVEN_MASK}), expected_diamonds_bitset);
    EXPECT_EQ(Manille::filter_bitset_higher(deck_bitset, CLUBS_MASK, {HEARTS_MASK, EIGHT_MASK}), expected_clubs_bitset);
    EXPECT_EQ(Manille::filter_bitset_higher(deck_bitset, SPADES_MASK, {HEARTS_MASK, JACK_MASK}), expected_spades_bitset);
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
    EXPECT_EQ(Manille::choose_trump(vector_to_bitset(deck)), HEARTS_MASK);

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
    EXPECT_EQ(Manille::choose_trump(vector_to_bitset(deck)), HEARTS_MASK);
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
    CardBitset player_bitset = vector_to_bitset(player);
    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, trump), player_bitset);

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
    player_bitset = vector_to_bitset(player);

    CardVector expected = {
            Card(HEARTS_MASK, ACE_MASK, 1),
    };
    CardBitset expected_bitset = vector_to_bitset(expected);
    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, trump), expected_bitset);
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
    CardBitset player_bitset = vector_to_bitset(player);

    CardVector expected = {
            Card(CLUBS_MASK, KING_MASK, 1),
            Card(CLUBS_MASK, EIGHT_MASK, 1)
    };
    CardBitset expected_bitset = vector_to_bitset(expected);
    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, trump), expected_bitset);

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
    player_bitset = vector_to_bitset(player);

    expected = {
            Card(CLUBS_MASK, KING_MASK, 1),
    };
    expected_bitset = vector_to_bitset(expected);
    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, trump), expected_bitset);

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
    player_bitset = vector_to_bitset(player);

    expected = {
            Card(DIAMONDS_MASK, SEVEN_MASK, 1),
    };
    expected_bitset = vector_to_bitset(expected);
    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, trump), expected_bitset);

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
    player_bitset = vector_to_bitset(player);

    expected = {
            Card(HEARTS_MASK, JACK_MASK, 1),
    };
    expected_bitset = vector_to_bitset(expected);
    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, trump), expected_bitset);
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
    CardBitset player_bitset = vector_to_bitset(player);

    EXPECT_EQ(Manille::get_allowed_cards(player_bitset, trick, 1, HEARTS_MASK), player_bitset);
}