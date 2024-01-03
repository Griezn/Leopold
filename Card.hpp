//
// Created by Seppe Degryse on 27/12/2023.
//

#ifndef CARD_HPP
#define CARD_HPP

struct Card;
typedef std::uint8_t byte;
typedef byte Suit;
typedef byte Value;
typedef std::vector<Card> CardVector;
constexpr int CARD_COUNT = 32;

// MASKS
constexpr byte VALUE_MASK   = 0b0000'1111;
constexpr byte SUIT_MASK    = 0b0011'0000;
constexpr byte PLAYER_MASK  = 0b1100'0000;

constexpr byte HEARTS_MASK  = 0b0000'0000;
constexpr byte SPADES_MASK  = 0b0001'0000;
constexpr byte CLUBS_MASK   = 0b0010'0000;
constexpr byte DIAMONDS_MASK= 0b0011'0000;

constexpr byte SEVEN_MASK   = 0b0000'0000;
constexpr byte EIGHT_MASK   = 0b0000'0001;
constexpr byte NINE_MASK    = 0b0000'0010;
constexpr byte JACK_MASK    = 0b0000'0011;
constexpr byte QUEEN_MASK   = 0b0000'0100;
constexpr byte KING_MASK    = 0b0000'0101;
constexpr byte ACE_MASK     = 0b0000'0110;
constexpr byte TEN_MASK     = 0b0000'0111;

constexpr byte P1_MASK      = 0b0000'0000;
constexpr byte P2_MASK      = 0b0100'0000;
constexpr byte P3_MASK      = 0b1000'0000;
constexpr byte P4_MASK      = 0b1100'0000;

struct Card {
    byte card;

    explicit Card(int value) : Card((value/8) << 4, value % 8)
    {
    }


    Card() : card(255)
    {
    }


    Card(Suit suit, Value value) : Card(suit, value, 1)
    {
    }


    Card(Suit suit, Value value, int player)
    {
        card = ((player - 1) << 6) | suit | value;
    }

    inline bool operator==(const Card &other) const
    {
        return (card & ~PLAYER_MASK) == (other.card & ~PLAYER_MASK);
    }


    inline bool operator!=(const Card &other) const
    {
        return !(*this == other);
    }


    inline bool operator<(const Card &other) const
    {
        return (this->card & VALUE_MASK) < (other.card & VALUE_MASK);
    }


    inline bool operator>(const Card &other) const
    {
        return (other.card & VALUE_MASK) < (this->card & VALUE_MASK);
    }


    inline bool operator<=(const Card &other) const
    {
        return !(other < *this);
    }


    inline bool operator>=(const Card &other) const
    {
        return !(*this < other);
    }


    [[nodiscard]] inline Suit suit() const
    {
        return card & SUIT_MASK;
    }


    [[nodiscard]] inline Value value() const
    {
        return card & VALUE_MASK;
    }


    [[nodiscard]] inline int player() const
    {
        return (card >> 6) + 1;
    }


    inline void set_player(int player)
    {
        card = card | ((player - 1) << 6);
    }


    explicit operator int() const
    {
        return (card & VALUE_MASK) + ((card & SUIT_MASK) >> 4) * 8;
    }


    [[nodiscard]] int points() const
    {
        switch (card & VALUE_MASK) {
            case JACK_MASK:
                return 1;
            case QUEEN_MASK:
                return 2;
            case KING_MASK:
                return 3;
            case ACE_MASK:
                return 4;
            case TEN_MASK:
                return 5;
            default:
                return 0;
        }
    }


    [[nodiscard]] inline bool valid() const
    {
        return card != 255;
    }


    static CardVector get_deck()
    {
        CardVector deck;
        for (int i = 0; i < 32; ++i) {
            deck.emplace_back(i);
        }
        return deck;
    }
};

#endif //CARD_HPP
