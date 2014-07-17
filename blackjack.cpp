// blackjack.cpp : Defines the entry point for the console application.
//


//#include <curses.h>
#include "blackjack.h"
#include "player.h"
#include "deck.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <conio.h>
#include <ctype.h>
#include <string.h>

#ifdef WIN32
#define getch _getch
#endif

BlackJack::BlackJack()
{
    m_Player = NULL;
    m_Dealer = NULL;
    m_Deck = NULL;
    m_GameResult = BJ_GMSTATE_UNKNOWN;
}

BlackJack::~BlackJack()
{
    if (m_Player) {
        delete m_Player;
        m_Player = NULL;
    }
    if (m_Dealer) {
        delete m_Dealer;
        m_Dealer = NULL;
    }
    if (m_Deck) {
        delete m_Deck;
        m_Deck = NULL;
    }
}


int BlackJack::Init(void *info)
{
    int rv = BJ_ERR_SUCCESS;
    m_Deck = Deck::Create(1, info);
    if (!m_Deck) {
        return BJ_ERR_UNKNOWN;
    }
    rv = m_Deck->Init();
    if (rv != BJ_ERR_SUCCESS) {
        return rv;
    }

    m_Dealer = Dealer::Create(info);
    if (!m_Dealer) {
        return BJ_ERR_UNKNOWN;
    }
    rv = m_Dealer->Init();
    if (rv != BJ_ERR_SUCCESS) {
        return rv;
    }


    m_Player = Player::Create(info);
    if (!m_Player) {
        return BJ_ERR_UNKNOWN;
    }
    rv = m_Player->Init();
    if (rv != BJ_ERR_SUCCESS) {
        return rv;
    }

    return rv;
}

/**
Rules:
1a. The player or players are dealt an initial two-card hand and 
    add together the value of their cards.
1b. In a given round, the player or the dealer wins by having a 
    score of 21 or by having the highest score that is less than 21. 
1c. A player may win by having any final score equal to or less 
    than 21 if the dealer busts.

2a. The dealer has to take hits until his or her cards total 17 or 
    more points
2b. Players win if they do not bust and have a total that is higher 
    than the dealer's
 */

int BlackJack::NewGame()
{
    int rv      = BJ_ERR_SUCCESS;
    int plyhit  = TRUE;
    int dScore  = 0;
    int pScore  = 0;

    if ((!m_Deck) || (!m_Dealer) || (!m_Player)) {
        return BJ_ERR_PROGRAM_ERR;
    }
    m_GameResult = BJ_GMSTATE_UNKNOWN;
    rv = m_Dealer->Init();
    rv = m_Player->Init();
    rv = m_Deck->Shuffle();
    //To Do: Check rv

    m_Dealer->Hit(m_Deck->GetNextCard());
    m_Player->Hit(m_Deck->GetNextCard());
    //To Do: Check rv

    while (TRUE) {
        rv = m_Dealer->Hit(m_Deck->GetNextCard());
        rv = plyhit ? m_Player->Hit(m_Deck->GetNextCard()) : BJ_ERR_SUCCESS;

        //To Do: Check rv
        rv = DisplayHands();

        dScore = m_Dealer->Score();
        pScore = m_Player->Score();

        if ((dScore >= 17) || (pScore > 21)) {
            break;
        }
        plyhit = GetHitOrStandChoice();
    }

    if (rv != BJ_ERR_SUCCESS) {
        return rv;
    }

    m_GameResult = BJ_GMSTATE_DRAW;
    if (dScore > 21) {
        m_GameResult = BJ_GMSTATE_PLAYER_WON;
    } else if (pScore > 21) {
        m_GameResult = BJ_GMSTATE_DEALER_WON;
    } else if (pScore > dScore) {
        m_GameResult = BJ_GMSTATE_PLAYER_WON;
    } else if (pScore < dScore) {
        m_GameResult = BJ_GMSTATE_DEALER_WON;
    }

    rv = DisplayResults();
    return rv;
}

int BlackJack::DisplayHands()
{
    BYTE card = 0;
    printf("Dealer's Hand: ");
    DisplayHand(m_Dealer);
    printf("\nPlayer's Hand: ");
    DisplayHand(m_Player);
    printf("\n\n");
    return BJ_ERR_SUCCESS;
}

int BlackJack::DisplayHand(Player* ply)
{
    const BYTE* hand = ply->GetHand();
    
    BYTE card = 0;
    char strCard[3];

    while ((card = (BYTE) *hand) != PLYR_CARD_TERM) {
        //ToDo: Check if card value is sane
        switch (card) {
            case 1 : strcpy(strCard, "A"); break;
            case 10: strcpy(strCard, "10"); break;
            case 11: strcpy(strCard, "J"); break;
            case 12: strcpy(strCard, "Q"); break;
            case 13: strcpy(strCard, "K"); break;
            default: 
                strCard[0] = card + 48; 
                strCard[1] = 0;
                break;
        }
        printf("%s ", strCard);
        hand++;
    }
    return BJ_ERR_SUCCESS;
}

int BlackJack::DisplayResults()
{
    switch (m_GameResult) {
        case BJ_GMSTATE_DRAW:       printf("Game was draw\n"); break;
        case BJ_GMSTATE_PLAYER_WON: printf("Player won!\n"); break;
        case BJ_GMSTATE_DEALER_WON: printf("Dealer won!\n"); break;
        default: break;
    }
    return BJ_ERR_SUCCESS;
}

//Returns 1 for a hit 0 for Stand
int BlackJack::GetHitOrStandChoice()
{
    int hit = TRUE;
    printf("(H)it or (S)tand?\n");

    char c = 0;
    while ((c!='h') && (c!='s')) {
        c = tolower(getch());
        if (c == 'h') {
            hit = TRUE;
            break;
        } else if (c == 's') {
            hit = FALSE;
            break;
        }
    }
    return hit;
}

int BlackJack::Start()
{
    int rv = BJ_ERR_SUCCESS;
    while (TRUE) {
        rv = NewGame();
        if (rv != BJ_ERR_SUCCESS) {
            break;
        }

        if (!GetReplay()) {
            break;
        }
    }

    if (rv != BJ_ERR_SUCCESS) {
        printf("%s:%d: Exiting with error code %d\n",
            __FUNCTION__, __LINE__, rv);
    }

    return rv;
}

int BlackJack::GetReplay()
{
    int replay = 0;

    printf("Replay (Y)es/(N)o?\n");
    char yn = 0;
    while((yn != 'y') && (yn != 'n')) {
        yn = tolower(getch());
    }
    if ('y' == yn) {
        replay = TRUE;
    }
    return replay;
}

void main(void)
{
    BlackJack BjGame;
    
    BjGame.Init(NULL);
    BjGame.Start();
}

