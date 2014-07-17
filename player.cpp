
#include "blackjack.h"
#include "deck.h"
#include "player.h"

/*static*/
Player* Player::Create(void* info)
{
    //ToDo: Create a UT version as per info
    return new Player();
}

Player::Player()
{
    m_CardVal = 0;
    m_nCardIdx = PLYR_CARD_IDX_RESET;
    m_Cards[m_nCardIdx] = (BYTE) PLYR_CARD_TERM;
    //memset(m_Cards, 0, sizeof(m_Cards));
}

Player::~Player()
{
    
}

int Player::Init()
{
    m_CardVal = 0;
    m_nCardIdx = PLYR_CARD_IDX_RESET;
    m_Cards[m_nCardIdx] = PLYR_CARD_TERM;
    return BJ_ERR_SUCCESS;
}

int Player::Hit(BYTE card)
{
    if (m_nCardIdx >= (PLYR_MAX_CARDS - 1)) {
        return BJ_ERR_PROGRAM_ERR;
    }
    if (card <= 0) {
        return BJ_ERR_PROGRAM_ERR;
    }

    m_Cards[m_nCardIdx++] = card;
    m_Cards[m_nCardIdx] = PLYR_CARD_TERM;

    return Score();
}

int Player::Score()
{
    const BYTE* hand = GetHand();
    BYTE card = 0;
    int score = 0;
    int aces = 0;

    while ((card = (BYTE) *hand) != PLYR_CARD_TERM) {
        switch (card) {
            case 1: 
                //got an ace
                card = 11; 
                aces++; 
                break;
            case 11:
            case 12:
            case 13: 
                card = 10;
                break;
        }
        score += card;
        hand++;
    }

    while ((score > 21) && (aces > 0)) {
        score -= 10;
        aces--;
    }
    return score;
}

int Player::Stand()
{
    //Do we have to do anything?
    return BJ_ERR_SUCCESS;
}

const BYTE* Player::GetHand()
{
    return (const BYTE*) m_Cards;
}

///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////

/*static*/
Dealer* Dealer::Create(void* info)
{
    //ToDo: Create a UT version as per info
    return new Dealer();
}

Dealer::Dealer()
{
    //calls default constructor for ::player
}

Dealer::~Dealer()
{

}

int Dealer::Stand()
{
    //dealer cannot not stand
    //ToDo: get clarty
    return BJ_ERR_PROGRAM_ERR;
}


