
#ifndef __BLACKJACK_DECK__
#define __BLACKJACK_DECK__

#include "blackjack.h"

#define CARDS_PER_DECK 52

class Deck
{
private:
    int     m_nDecks;
    int     m_nCards;
    BYTE*   m_Cards;
    int     m_CardIdx;

public:
    static Deck* Create(int nDecks, void* info);
    Deck(int nDecks = 1);
    virtual ~Deck();
    virtual int Init();
    virtual int Shuffle();
    virtual int GetNextCard();
};

//To Do:
class DeckUT: public Deck
{

public:
    int Init();
    int Shuffle();
};

#endif //__BLACKJACK_DECK__