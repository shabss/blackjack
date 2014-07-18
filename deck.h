
#ifndef __BLACKJACK_DECK__
#define __BLACKJACK_DECK__

#include "blackjack.h"

#define CARDS_PER_DECK 52

class Deck
{
protected:
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


typedef struct _DeckUTInfo {
    BYTE *pCards;
    int nCards;
    _DeckUTInfo() {
        pCards = NULL;
        nCards = 0;
    }
} DeckUTInfo;


class DeckUT: public Deck
{
protected:
    DeckUTInfo*   m_Info;

public:
    DeckUT(int nDecks, DeckUTInfo* info);
    virtual ~DeckUT();
    int Init();
    int Shuffle();
};

#endif //__BLACKJACK_DECK__