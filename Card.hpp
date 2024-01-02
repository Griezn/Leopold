//
// Created by Seppe Degryse on 27/12/2023.
//

#ifndef CARD_HPP
#define CARD_HPP

struct Card;
typedef std::vector<Card> CardVector;
constexpr int CARD_COUNT = 32;

enum class Suit {
    NONE,
    HEARTS,
    SPADES,
    CLUBS,
    DIAMONDS
};

enum class Value {
    NONE,
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

    Card() : Card(Suit::NONE, Value::NONE)
    {}

    explicit Card(int card) : Card(static_cast<Suit>(card / 8 + 1), static_cast<Value>(card % 8 + 1))
    {}

    Card(const Suit suit, const Value value) : Card(suit, value, 0)
    {}

    Card(const Suit suit, const Value value, const int player) : suit(suit), value(value), player(player)
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


    explicit operator int() const
    {
        return (static_cast<int>(suit) - 1) * 8 + (static_cast<int>(value) - 1);
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
        return suit != Suit::NONE && value != Value::NONE;
    }

    static CardVector get_deck()
    {
        CardVector deck;
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 8; j++) {
                deck.emplace_back(static_cast<Suit>(i), static_cast<Value>(j));
            }
        }
        return deck;
    }
};

#endif //CARD_HPP
