

#ifndef __BLACKJACK__
#define __BLACKJACK__

/**
We'd like you to implement a text-based Blackjack program in one of the 
following programming languages: Java, Clojure, Scala, C, C++, Python, 
or Ruby. There should be one player and one dealer. The dealer should 
hit until his hand value is 17 or greater. You should implement the 
basic actions of hitting and standing. Implementing the more advanced 
actions such as splitting is optional. The player should start with 100 
chips and must bet at least 1 chip each hand.

Any additional game play features are optional, but welcome.
*/

//Typedefs
typedef unsigned char BYTE;

#ifndef TRUE
#define TRUE 1
#endif //TRUE

#ifndef FALSE
#define FALSE 0
#endif //FALSE

#ifndef NULL
#define NULL 0
#endif

//RET VALs
#define BJ_ERR_SUCCESS           0
#define BJ_ERR_UNKNOWN          -1
#define BJ_ERR_PROGRAM_ERR      -2
#define BJ_ERR_BOUNDS           -3

#define BJ_GMSTATE_UNKNOWN          0
#define BJ_GMSTATE_DRAW             1
#define BJ_GMSTATE_PLAYER_WON       2
#define BJ_GMSTATE_DEALER_WON       3


//App #defs
class Player;
class Dealer;
class Deck;

class BlackJack 
{
protected:
    Player* m_Player;
    Dealer* m_Dealer;
    Deck*   m_Deck;
    int     m_GameResult;

public:
    BlackJack();
    virtual ~BlackJack();
    virtual int Init(void* info);
    virtual int Start();
    virtual int NewGame();

    //Following functions interact with a View
    virtual int DisplayHands();
    virtual int DisplayHand(Player* ply);
    virtual int GetHitOrStandChoice();
    virtual int DisplayResults();
    virtual int GetReplay();

};



#endif //__BLACKJACK__