//
// Created by Seppe Degryse on 31/12/2023.
//

#ifndef LEOPOLD_I_STATE_HPP
#define LEOPOLD_I_STATE_HPP

#include <vector>
#include "Card.hpp"

struct State;

typedef std::vector<Card> CardVector;
typedef std::vector<State> StateVector;


struct State {
public:
    /**
     * Creates a new state.
     * @param player_cards the cards that the player has
     * @param remaining_cards the cards that are still in the game
     * @param trick_cards the cards that are already played in the trick
     * @param trump the trump suit
     * @param player the index of the player that has to play
     */
    State(CardVector player_cards, CardVector remaining_cards, CardVector trick_cards, Suit trump, int player);


    /**
     * Returns whether the state is terminal.
     * @return whether the state is terminal
     */
    [[nodiscard]] bool is_terminal() const;


    /**
     * Returns the score of the state.
     * @return the score of the state
     */
    [[nodiscard]] int get_score() const;


    /**
     * Returns the children of the state.
     * @return the children of the state
     */
    [[nodiscard]] StateVector get_children() const;


    /**
     * Returns the index of the next player.
     * @return the index of the next player
     */
    [[nodiscard]] int get_next_player() const;


    /**
     * Returns the index of the player that has to play.
     * @return the index of the player that has to play
     */
    [[nodiscard]] int get_player() const { return player; }


private:
    CardVector player_cards;
    CardVector remaining_cards;
    CardVector trick_cards;
    Suit trump;
    int player;
    int score;


    /**
     * Generates the children of the state for the opponent.
     * @param children the vector to store the children in
     */
    void generate_children_opponent(StateVector &children) const;


    /**
     * Generates the children of the state for the player.
     * @param children the vector to store the children in
     */
    void generate_children_player(StateVector &children) const;


    /**
     * Completes the trick of the state. Calculates the score and clears the trick cards.
     * @param child the child to complete the trick for
     * @post the trick cards are cleared
     * @post the score is calculated
     */
    void complete_trick(State &child) const;
};


#endif //LEOPOLD_I_STATE_HPP
