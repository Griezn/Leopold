//
// Created by Seppe Degryse on 27/12/2023.
//

#ifndef CARD_HPP
#define CARD_HPP

struct Card;
typedef std::vector<Card> CardVector;

enum class Suit {
    NONE,
    HEARTS,
    SPADES,
    CLUBS,
    DIAMONDS
};

enum class Value {
    SEVEN,
    EIGHT,
    NINE,
    JACK,
    QUEEN,
    KING,
    ACE,
    TEN
};

struct Card {

    Suit suit;
    Value value;
    int player;

    Card() : Card(Suit::NONE, Value::SEVEN)
    {}

    Card(const Suit suit, const Value value) : Card(suit, value, 0)
    {}

    Card(const Suit suit, const Value value, const unsigned int player) : suit(suit), value(value), player(player)
    {}


    bool operator==(const Card &other) const
    {
        return this->suit == other.suit && this->value == other.value;
    }


    bool operator!=(const Card &other) const
    {
        return !(*this == other);
    }


    bool operator<(const Card &other) const
    {
        return this->value < other.value;
    }


    bool operator>(const Card &other) const
    {
        return other.value < this->value;
    }


    bool operator<=(const Card &other) const
    {
        return !(other < *this);
    }


    bool operator>=(const Card &other) const
    {
        return !(*this < other);
    }


    [[nodiscard]] int points() const
    {
        switch (value) {
            case Value::JACK:
                return 1;
            case Value::QUEEN:
                return 2;
            case Value::KING:
                return 3;
            case Value::ACE:
                return 4;
            case Value::TEN:
                return 5;
            default:
                return 0;
        }
    }

    [[nodiscard]] bool valid() const
    {
        return suit != Suit::NONE;
    }

    static CardVector get_deck()
    {
        CardVector deck;
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                deck.emplace_back(static_cast<Suit>(i), static_cast<Value>(j));
            }
        }
        return deck;
    }
};

#endif //CARD_HPP
