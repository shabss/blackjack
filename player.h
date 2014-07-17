
#ifndef __BLACKJACK_PLAYER__
#define __BLACKJACK_PLAYER__

//Max 11 cards can make value >= 21
//4x1 + 4x2 + 3x3 == 21
//+1 spot to terminate
#define PLYR_MAX_CARDS          12
#define PLYR_CARD_IDX_RESET     0
#define PLYR_CARD_TERM          0

class Player 
{
protected:
    int     m_CardVal;  
    BYTE    m_Cards[PLYR_MAX_CARDS];
    int     m_nCardIdx;

public:
    static Player* Create(void* info);
    Player();
    virtual ~Player();
    virtual int Init();
    virtual int Hit(BYTE card);
    virtual int Stand();
    virtual int Score();
    virtual const BYTE* GetHand();
};


///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////

class Dealer : public Player
{

public:
    static Dealer* Create(void* info);
    Dealer();
    virtual ~Dealer();
    int Stand();
};


#endif //__BLACKJACK_PLAYER__