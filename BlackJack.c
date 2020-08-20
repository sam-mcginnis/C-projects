#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3

//samuel mcginnis
//blackjack
//5/2/2016
enum{ TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

int Deck[52];
int CurrentDealCard;
int Dealer[20], Player[20];
int DealerCards, PlayerCards;
int DealerScore, PlayerScore;
int choice;

void DoShuffle()
{
    int i, nextcard;
    int Used[52];

  
    for (i = 0; i < 52; i++) Used[i] = 0;

    /* Loop through the deck of cards, there are 52 values */
    for (i = 0; i < 52; i++)
    {
        
        do
        {
            nextcard = rand() % 52; /* Value from 0 to 51 */

        } while (Used[nextcard] == 1); 


       
        Used[nextcard] = 1;

       
        Deck[i] = nextcard;
    }
}

void DrawCard(int rank, int suit)
{

    switch (rank)
    {
    case TWO:
        printf("Two ");
        break;
    case THREE:
        printf("Three ");
        break;
    case FOUR:
        printf("Four ");
        break;
    case FIVE:
        printf("Five ");
        break;
    case SIX:
        printf("Six ");
        break;
    case SEVEN:
        printf("Seven ");
        break;
    case EIGHT:
        printf("Eight ");
        break;
    case NINE:
        printf("Nine ");
        break;
    case TEN:
        printf("Ten ");
        break;
    case JACK:
        printf("Jack ");
        break;
    case QUEEN:
        printf("Queen ");
        break;
    case KING:
        printf("King ");
        break;
    case ACE:
        printf("Ace ");
        break;
    }

    switch (suit)
    {
    case CLUBS:
        printf("Clubs");
        break;
    case DIAMONDS:
        printf("Diamonds");
        break;
    case HEARTS:
        printf("Hearts");
        break;
    case SPADES:
        printf("Spades");
        break;
    }

}

void DisplayShuffledDeck()
{
    int i, suit, rank;

    for (i = 0; i < 52; i++)
    {
        suit = Deck[i] / 13;
        rank = Deck[i] % 13;
        DrawCard(rank, suit);
        printf("\n");
    }

}

void DealCards()
{
    PlayerCards = DealerCards = CurrentDealCard = 0;

    Player[PlayerCards++] = Deck[CurrentDealCard++];
    Dealer[DealerCards++] = Deck[CurrentDealCard++];
    Player[PlayerCards++] = Deck[CurrentDealCard++];

    //1. Do not show dealer hole card//
    if (choice == 2)
        Dealer[DealerCards++] = Deck[CurrentDealCard++];

}

void DisplayDealtCards()
{
    int i;

    printf("\n\n\nDealer:\n");
    for (i = 0; i < DealerCards; i++) DrawCard(Dealer[i] % 13, Dealer[i] / 13), printf( "    " );
    printf("Dealer Score is %d\n\n\nPlayer:", DealerScore);
    for (i = 0; i < PlayerCards; i++) DrawCard(Player[i] % 13, Player[i] / 13), printf("    ");
    printf("Player Score is %d\n\n", PlayerScore);

}

void DisplayChoice()
{
    printf("What would you like to do?\n");
    printf("1. Hit\n2. Stand\n3. Double down\n");
}

int GetChoice(int min, int max)
{

    do
    {
        printf("Make a choice from %d to %d:  ", min, max);
        scanf("%d", &choice);
    } while (choice < min || choice > max);

    return(choice);
}

void CalculateScores()
{
    int i, rank, suit, AceCount;

    PlayerScore = 0;
    for (i = 0; i < PlayerCards; i++)
    {
        rank = Player[i] % 13;
        suit = Player[i] / 13;

        if (rank >= TWO && rank <= TEN) PlayerScore += (rank + 2);

        else if (rank >= JACK && rank <= KING) PlayerScore += 10;
        else if (rank == ACE)
        {

        if(PlayerScore <= 10 && rank>KING)
        {
            PlayerScore +=11;
            AceCount++;

        }

        if(PlayerScore > 21 && AceCount>=1)
        {
            PlayerScore -=10;
        }
    }
    }

    DealerScore = 0;
    for (i = 0; i < DealerCards; i++)
    {
        rank = Dealer[i] % 13;
        suit = Dealer[i] / 13;

        if (rank >= TWO && rank <= TEN) DealerScore += (rank + 2);

        else if (rank >= JACK && rank <= KING) DealerScore += 10;
        else DealerScore += 11;
    }

}



int main()
{
    int choice;
    int secondchoice, i;

    srand(time(0));

    DoShuffle();

    DealCards();
    CalculateScores();
    DisplayDealtCards();

    DisplayChoice();
    choice = GetChoice(1, 3);
    if (choice == 1)
    {
        Player[PlayerCards++] = Deck[CurrentDealCard++];
        CalculateScores();
        DisplayDealtCards();

        while (PlayerScore < 21 )
        {
            printf(" Press 1 for yes, 2 to stand");
            scanf("%d", &choice);
            if (choice == 1) /* Included this in order to make the code functional. this ensures that the player can hit until 21+*/
            {Player[PlayerCards++] = Deck[CurrentDealCard++];
            CalculateScores();
            DisplayDealtCards();
            }
            else if (choice ==2 )
            {
               /* Dealer[DealerCards++] = Deck[CurrentDealCard++];
                CalculateScores();
                DisplayDealtCards(); */
                Dealer[DealerCards++] = Deck[CurrentDealCard++];
                if ( DealerScore <17 )
                {Dealer[DealerCards++] = Deck[CurrentDealCard++];}

                CalculateScores();
                DisplayDealtCards(); /* This gives the dealer the cards if the user decides to stand*/

                break;
            }
            else
            {
                Player[PlayerCards++] = Deck[CurrentDealCard++];
                Player[PlayerCards++] = Deck[CurrentDealCard++];
                CalculateScores();
                DisplayDealtCards(); /* This gives the user two cards after their first three if they decide to double up.*/
            }

        }

	}

	else
    {
        Dealer[DealerCards++] = Deck[CurrentDealCard++]; /* Gives dealer cards if <= 16 as requested.*/
        if ( DealerScore <17 )
            {Dealer[DealerCards++] = Deck[CurrentDealCard++];}

            CalculateScores();
            DisplayDealtCards();

    }


//Tell the player when they lose.//
    if(PlayerScore > 21)
    {
        printf("\n\nYou have lost.\n\n");
    }

    //Tell the player when they win (Get 21).//
    if(PlayerScore == 21)
    {
      printf("Black jack!");
    }





	return 0;
}

