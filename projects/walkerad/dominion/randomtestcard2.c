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

int testMinion(int numPlayers) {

	// Counter variables
	int i, j, drawCounter;

	// Test variables
	int startCoinCount;
	int endCoinCount;
	int startNumActions;
	int endNumActions;
	int startHandCount;
	int endHandCount;

	// Set card array
	int k[10] = { minion, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };

	// Play minion card
	int p = 17;
	int bonus = 0;

	// Game state
	struct gameState G;
	
	// Declare the game state
	// Use random number of players
	initializeGame(numPlayers, k, 2, &G);

	// Randomly assign a handcount to each player
	for(i=0; i < numPlayers; i++){

		G.handCount[i] = (rand() % MAX_HAND_COUNT) + 1;

	}

	// Redraw each player's hands
	for ( i = 0; i < numPlayers; i++){

		// Shuffle deck
		shuffle(i, &G);

		// Redraw each card
		drawCounter = G.handCount[i];
	    for ( j = 0; j < drawCounter; j++){
	    
	    	discardCard(j, i, &G, 0);
	    	drawCard(i, &G);
	    
	    }

	}

	// Draw 1 or 2 for choice
	int choice = (rand() % 2) + 1;

	// Get starting coin count and number of actions
	startCoinCount = G.coins;
	startNumActions = G.numActions;
	startHandCount = G.handCount[1];
	// printf("startCoinCount is %d\n", startCoinCount);
	// printf("startNumActions is %d\n", startNumActions);
	// printf("startHandCount is %d\n", startHandCount);

	// Play card
	if( choice==1 ){

		cardEffect(p, choice, 0, 0, &G, 0, &bonus);

	} else {

		cardEffect(p, 0, choice, 0, &G, 0, &bonus);

	}

	// Get ending coin count
	endCoinCount = G.coins;
	endNumActions = G.numActions;
	endHandCount = G.handCount[1];
	// printf("endCoinCount is %d\n", endCoinCount);
	// printf("endNumActions is %d\n", endNumActions);
	// printf("endHandCount is %d\n", endHandCount);

	// Choice validation
	if( (choice == 1) &&  ( (startCoinCount != (endCoinCount - 2)) || (startNumActions != (endNumActions - 1)) ) ){

		printf("MINION TEST FAILED: CHOICE 1\n");
		return 1;

	} else if( (choice == 2) && (startHandCount >= 5) && (endHandCount != 4) ){

		printf("MINION TEST FAILED: CHOICE 2\n");
		return 1;

	} else {

		return 0;

	}

}

int main(int argc, char *argv[])
{

	srand(time(NULL));
    printf("TESTING MINION\n");

    int totalTests = 2000;
	int failedTests = 0; 
	int numPlayers;
    for (int n = 0; n < totalTests; n++) {

    	// Randomly choose number of players
    	numPlayers = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

    	// Run test
    	int testResult = testMinion(numPlayers);

    	// Update failed test counter
    	failedTests = failedTests + testResult;

    }	

    printf("Finished Minion random tests. Summary:\n");
    printf("Ran %d tests\n", totalTests);
    printf("Failed %d tests\n", failedTests);

    return 0;

}
