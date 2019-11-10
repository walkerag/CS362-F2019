#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testTribute() {

    printf("TESTING TRIBUTE\n");

	// Set card array
	int k[10] = { tribute, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// Declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Play tribute card
	int p = 19;
	int bonus = 0;

	// Test variables
	int startNumActions;
	int endNumActions;
	int startCoinCount;
	int endCoinCount;

	// Current Player hand
	G.handCount[0] = 5;
	G.hand[0][0] = 1; // Add estate card to hand
	G.hand[0][1] = 17;
	G.hand[0][2] = 17;
	G.hand[0][3] = 20;
	G.hand[0][4] = 4;


	//
	// TEST: Two different action cards on top of next player's deck
	//

	// Next Player hand
	G.handCount[1] = 5;
	G.hand[1][0] = 1; // Add estate card to hand
	G.hand[1][1] = 1;
	G.hand[1][2] = 1;
	G.hand[1][3] = 9; // Action card
	G.hand[1][4] = 8; // Action card

	startNumActions = G.numActions;

	// Play tribute card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	endNumActions = G.numActions;

	// Check 2 coins have been added
	if(startNumActions != (endNumActions - 4)){
		printf("TRIBUTE TEST FAILED: 4 actions not added\n");
	} else {
		printf("Tribute test passed\n");
	}


	//
	// TEST: Two of the same action cards on top of next player's deck
	//

	// Next player hand
	G.handCount[1] = 5;
	G.hand[1][0] = 1;
	G.hand[1][1] = 1;
	G.hand[1][2] = 1;
	G.hand[1][3] = 9; // Action card
	G.hand[1][4] = 9; // Action card

	// Current player num actions
	startNumActions = G.numActions;

	// Play tribute card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	endNumActions = G.numActions;

	// Check 2 coins have been added
	if(startNumActions != (endNumActions - 2)){
		printf("TRIBUTE TEST FAILED: 2 actions not added\n");
	} else {
		printf("Tribute test passed\n");
	}


	//
	// TEST: Two treasure cards in discard pile
	//

	// Set hand and deck count to zero
	G.handCount[1] = 0;
	G.deckCount[1] = 0;

	// Add 2 different treasure cards to discard pile
	G.discardCount[1] = 2;
	G.discard[1][0] = 4; // Treasure cards
	G.discard[1][1] = 5;

	// Starting coins
	startCoinCount = G.coins;

	// Play tribute card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	// Ending coins
	endCoinCount = G.coins;

	// Check 4 coins have been added to current player coin count
	if(startCoinCount != (endCoinCount - 4)){
		printf("TRIBUTE TEST FAILED: 4 coins not added\n");
	} else {
		printf("Tribute test passed\n");
	}

}

int main(int argc, char *argv[])
{
    testTribute();
    return 0;
}