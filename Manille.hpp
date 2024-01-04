//
// Created by Seppe Degryse on 27/12/2023.
//

#ifndef MANILLE_HPP
#define MANILLE_HPP

#include <vector>
#include <memory>
#include "Card.hpp"

typedef std::vector<Card> CardVector;


struct Manille {
    /**
     * Returns the cards that the player is allowed to play, given the cards that are already played in the trick and the
     * trump suit.
     * @param player the cards that the player has
     * @param trick the cards that are already played in the trick
     * @param trump the trump suit
     * @return the cards that the player is allowed to play
     */
    [[nodiscard]] static CardVector get_allowed_cards(const CardVector &player, const CardVector &trick, Suit trump);


    /**
     * Determines the winner of the trick, given the cards that are played and the trump suit.
     * @param trick the cards that are played in the trick
     * @param trump the trump suit
     * @return the index of the player that won the trick
     */
    [[nodiscard]] static int determine_winner(const CardVector &trick, Suit trump);


    /**
     * Determines the score of the trick, given the cards that are played and the trump suit.
     * @param trick the cards that are played in the trick
     * @param trump the trump suit
     * @return the score of the trick
     */
    [[nodiscard]] static int get_score(const CardVector &trick);


    /**
     * Determines the trump suit, given the cards that the player has.
     * @param player the cards that the player has
     * @return the trump suit
     */
    [[nodiscard]] static Suit choose_trump(const CardVector &player);


    /**
     * Determines the leader of a certain suit in a trick, given the cards that are played and the suit.
     * @param trick the cards that are played in the trick
     * @param suit the suit to the leader of
     * @return the index of the player that leads the suit
     */
    [[nodiscard]] static int get_leader(const CardVector &trick, Suit suit);


    /**
     * Determines whether the partner of the player is leading a suit in the trick, given the cards that are played, the index
     * of the player and the suit.
     * @param trick the cards that are played in the trick
     * @param player_index the index of the player
     * @param trump the trump suit
     * @return whether the partner of the player is leading in the trick
     */
    [[nodiscard]] static bool is_partner_leading(const CardVector &trick, int player_index, Suit suit);


    /**
     * Filters the cards that have a certain suit.
     * @param cards the cards to filter
     * @param suit the suit to filter on
     * @return the cards that have the suit
     */
    static CardVector filter_cards(const CardVector &cards, Suit suit);


    /**
     * Filters the cards that have a certain suit and are higher than a certain card.
     * @param cards the cards to filter
     * @param suit the suit to filter on
     * @param card the card to filter on
     * @return the cards that have the suit and are higher than the card
     */
    static CardVector filter_cards_higher(const CardVector &cards, Suit suit, Card card);


    /**
     * Returns the highest card of a certain suit.
     * @param cards the cards to find the highest card in
     * @param suit the suit to find the highest card of
     * @return the highest card of the suit
     */
    static Card get_highest_card(const CardVector &cards, Suit suit);
};


#endif // MANILLE_HPP
