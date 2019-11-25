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
#define MAX_CARD_NUM 26

int testBaron(int numPlayers) {

	// Counter variables
	int i, j, drawCounter;

	// Set card array
	int k[10] = { baron, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };

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
	    	G.hand[i][j] = (rand() % MAX_CARD_NUM);	    	    
	    }

	}

	// // Check first player's hand
	// // printf("Handcount pre-loop is %d\n", G.handCount[0]);
	// for( i = 0; i < G.handCount[0]; i++){
	// 	// printf("%d\n", i);
	// 	// printf("Card is %d\n", G.hand[0][i]);
	// }
	
	// Play baron card
	int p = 15;
	int bonus = 0;

	// Test variables
	int startCoinCount;
	int endCoinCount;
	int startSupplyCount;
	int endSupplyCount;
	int HandCount;

	//
	// TEST: Discard estate card as first card in hand
	//

	// Add estate card to START of hand, others cards to 0
	G.hand[0][0] = 1;

	// Get starting coin count
	startCoinCount = G.coins;

	// Play card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	// Get ending coin count
	endCoinCount = G.coins;

	// Check 4 coins have been added
	if(startCoinCount != (endCoinCount - 4)){

		printf("BARON TEST FAILED: 4 coins not added upon discard\n");
		return 1;

	}

	// Check estate card has been discarded
	if(G.hand[0][0] == 1){

		printf("BARON TEST FAILED: Failed to discard estate card\n");
		return 1;

	}

	//
	// TEST: Discard estate card as last card in hand
	//

	// Add estate card to END of hand, others cards to 0
	G.hand[0][G.handCount[0]] = 1;

	// Get starting coin count
	startCoinCount = G.coins;

	// Play card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	// Get ending coin count
	endCoinCount = G.coins;

	// Check 4 coins have been added
	if(startCoinCount != (endCoinCount - 4)){

		printf("BARON TEST FAILED: 4 coins not added upon discard\n");
		return 1;

	}

	// Check estate card has been discarded
	if(G.hand[0][G.handCount[0]] == 1){

		printf("BARON TEST FAILED: Failed to discard estate card\n");
		return 1;

	}


	//
	// TEST: Add estate card to hand
	//

	// Starting estate card count
	startSupplyCount = supplyCount(estate, &G);

	// Play with choice1 set to zero, to add estate card
	cardEffect(p, 0, 0, 0, &G, 0, &bonus);

	// Ending estate card count
	endSupplyCount = supplyCount(estate, &G);

	// Check estate card removed from supply
	if(startSupplyCount == endSupplyCount ){

		printf("BARON TEST FAILED: Estate card not removed from supply\n");
		return 1;

	} else if (startSupplyCount > (endSupplyCount + 1)) {

		printf("BARON TEST FAILED: Multiple estate cards removed from supply\n");
		return 1;

	}


	//
	// TEST: Try to discard estate card with no estate card in hand
	//

	// Ensure no estate cards in hand
	HandCount = G.handCount[0];
	for(int i=0; i < HandCount; i++){
		G.hand[0][i] = 0;
	}

	// Get starting coin count
	startCoinCount = G.coins;

	// Play card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	// Get ending coin count
	endCoinCount = G.coins;

	// Check coin count unchanged
	if(startCoinCount < endCoinCount){
		printf("BARON TEST FAILED: Coins added\n");
		return 1;

	}

	// All tests passed
	return 0;

}

int main(int argc, char *argv[])
{

	srand(time(NULL));
    printf("TESTING BARON\n");

    int totalTests = 2000;
	int failedTests = 0; 
	int numPlayers;
    for (int n = 0; n < totalTests; n++) {

    	// Randomly choose number of players
    	numPlayers =  (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

    	// Run test
    	int testResult = testBaron(numPlayers);

    	// Update failed test counter
    	failedTests = failedTests + testResult;

    }	

    printf("Finished Baron random tests. Summary:\n");
    printf("Ran %d tests\n", totalTests);
    printf("Failed %d tests\n", failedTests);

    return 0;
}







