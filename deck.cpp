/*
    Header goes here
 **/

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>     /* memsett */
#include <assert.h>

#include "deck.h"

const BYTE g_Cards[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
/*static*/
Deck* Deck::Create(int nDecks, void* info)
{
    Deck* deck = NULL;
    if (!info) {
        deck = new Deck(nDecks);
    } else {
        deck = new DeckUT(nDecks, (DeckUTInfo*) info);
    }
    return deck;
}

Deck::Deck(int nDecks)
{
    m_nDecks    = nDecks;
    m_nCards    = 0;
    m_Cards     = NULL;
    m_CardIdx   = 0;
}

Deck::~Deck()
{
    if (m_Cards) {
        delete [] m_Cards;
        m_Cards = NULL;
    }
}

int Deck::Init()
{
    int rv = BJ_ERR_SUCCESS;
    
    if (m_Cards) {
        //should not init twice
        return BJ_ERR_PROGRAM_ERR;
    }

    if (m_nDecks <= 0) {
        //force to 1 if value is invalid
        m_nDecks = 1;
    }
    m_nCards = CARDS_PER_DECK * m_nDecks;

    m_Cards = new BYTE[m_nCards];
    if (!m_Cards) {
        return BJ_ERR_UNKNOWN;
    }
    for (int i=0; i < m_nCards; i+= sizeof(g_Cards)) {
        memcpy(&m_Cards[i], g_Cards, sizeof(g_Cards));
    }

    srand((unsigned int)time(NULL));
    return Shuffle();
}


int Deck::Shuffle() 
{
    if (!m_Cards) {
        return BJ_ERR_PROGRAM_ERR;
    }
    m_CardIdx = 0;

    //Fisher–Yates shuffle algo. Google it!
    for (int i = m_nCards - 1; i >= 1; i--) {
        int pos = rand() % i;
        BYTE card = m_Cards[pos];
        m_Cards[pos] = m_Cards[i];
        m_Cards[i] = card;
    }
    return BJ_ERR_SUCCESS;
}

int Deck::GetNextCard()
{
    //Note return type is overloaded
    //BYTE when success
    //-ve int on failure
    int rv = BJ_ERR_SUCCESS;
    if (m_CardIdx >= m_nCards) {
        rv = Shuffle();
    }
    if (rv != BJ_ERR_SUCCESS) {
        return rv;
    }
    return m_Cards[m_CardIdx++];
}


////////////////////////////
////////////////////////////

DeckUT::DeckUT(int nDecks, DeckUTInfo* info) : Deck(nDecks)
{
    m_Info = info;

}

DeckUT::~DeckUT()
{
    
}

int DeckUT::Init() 
{
    //To Do: Init based on info
    //for now just call parent's Info
    return Deck::Init();
}

int DeckUT::Shuffle()
{
    //ToDo: Layout cards in as per m_Info
    for (int i=0; i < m_nCards; i+= sizeof(g_Cards)) {
        memcpy(&m_Cards[i], g_Cards, sizeof(g_Cards));
    }
    return BJ_ERR_SUCCESS;
}

