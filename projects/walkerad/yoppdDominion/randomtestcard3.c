#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define MAX_HAND_COUNT 5
#define MAX_DECK_COUNT 5
#define MAX_DISCARD_COUNT 5
#define MAX_CARD_NUM 26

int testTribute(int numPlayers) {

	// Counter variables
	int i, j, deckCounter, handCounter, discardCounter;

	// Test variables
	int startNumActions;
	int endNumActions;
	int startNumCoins;
	int endNumCoins;
	int startNumCards;
	int endNumCards;

	// Set card array
	int k[10] = { tribute, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };

	// Play tribute card
	int p = 19;
	int bonus = 0;

	// Game state
	struct gameState G;
	
	// Declare the game state
	// Use random number of players
	initializeGame(numPlayers, k, 2, &G);

	// Randomly assign a handcount, deckcount, discard count to each player
	// Allowing to be zero
	for(i=0; i < numPlayers; i++){

		G.deckCount[i] = (rand() % MAX_DECK_COUNT);		
		G.handCount[i] = (rand() % MAX_HAND_COUNT);
		G.discardCount[i] = (rand() % MAX_DISCARD_COUNT);

	}

	// Redraw each player's deck, hand, and discard piles
	for ( i = 0; i < numPlayers; i++){

		// Redraw deck
		deckCounter = G.deckCount[i];
	    for ( j = 0; j < deckCounter; j++){	    
	    	G.deck[i][j] = (rand() % MAX_CARD_NUM);
	    }	        

		// Redraw hand
		handCounter = G.handCount[i];
	    for ( j = 0; j < handCounter; j++){	    
	    	G.hand[i][j] = (rand() % MAX_CARD_NUM);
	    }

		// Redraw discard
		discardCounter = G.discardCount[i];
	    for ( j = 0; j < discardCounter; j++){	    
	    	G.discard[i][j] = (rand() % MAX_CARD_NUM);
	    }

	}

	startNumActions = G.numActions;
	startNumCards = G.handCount[0];
	startNumCoins = G.coins;

	// printf("startNumActions is %d\n", startNumActions);
	// printf("startNumCards is %d\n", startNumCards);
	// printf("startNumCoins is %d\n", startNumCoins);	

	// Play tribute card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	endNumActions = G.numActions;
	endNumCards = G.handCount[0];
	endNumCoins = G.coins;

	// printf("endNumActions is %d\n", endNumActions);
	// printf("endNumCards is %d\n", endNumCards);
	// printf("endNumCoins is %d\n", endNumCoins);	

	// Search for outcome failures
	if(startNumActions < (endNumActions - 4)){
		printf("TRIBUTE TEST FAILED: Too many actions added\n");
		return 1;
	}

	if(startNumCards < (endNumCards - 4)){
		printf("TRIBUTE TEST FAILED: Too many cards added\n");
		return 1;
	}

	if(startNumCoins < (endNumCoins - 4)){
		printf("TRIBUTE TEST FAILED: Too many coins added\n");
		return 1;
	}

	return 0;

}

int main(int argc, char *argv[])
{

	srand(time(NULL));
    printf("TESTING TRIBUTE\n");

    int totalTests = 2000;
	int failedTests = 0; 
	int numPlayers;
    for (int n = 0; n < totalTests; n++) {

    	// Randomly choose number of players
    	numPlayers = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

    	// Run test
    	int testResult = testTribute(numPlayers);

    	// Update failed test counter
    	failedTests = failedTests + testResult;

    }	

    printf("Finished Tribute random tests. Summary:\n");
    printf("Ran %d tests\n", totalTests);
    printf("Failed %d tests\n", failedTests);

    return 0;

}
