#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testMine() {

    printf("TESTING MINE\n");

	// Set card array
	int k[10] = { tribute, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// Declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Play mine card
	int p = 11;
	int bonus = 0;

	// Test variables
	int startHandCount;
	int endHandCount;
	int firstCard;

	// Current Player hand
	G.handCount[0] = 5;
	G.hand[0][0] = 4; // Add copper to hand
	G.hand[0][1] = 17;
	G.hand[0][2] = 17;
	G.hand[0][3] = 20;
	G.hand[0][4] = 20;

	//
	// TEST: Discard copper for silver
	//

	startHandCount = G.handCount[0];

	// Play mine
	// Request silver
	cardEffect(p, 0, 5, 0, &G, 0, &bonus);

	endHandCount = G.handCount[0];
	firstCard = G.hand[0][0];

	// Check hand count unchanged
	if(startHandCount != endHandCount){
		printf("MINE TEST FAILED: Incorrect card count\n");
	} else {
		printf("Mine test passed\n");
	}

	// Check silver added
	if(firstCard != 5){
		printf("MINE TEST FAILED: Failed to add silver\n");
	} else {
		printf("Mine test passed\n");
	}


	//
	// TEST: Discard copper for adventurer
	//

	// Current Player hand
	G.handCount[0] = 5;
	G.hand[0][0] = 4; // Add copper to hand
	G.hand[0][1] = 17;
	G.hand[0][2] = 17;
	G.hand[0][3] = 20;
	G.hand[0][4] = 20;

	// Play mine
	// Request adventurer
	cardEffect(p, 0, 7, 0, &G, 0, &bonus);
	firstCard = G.hand[0][0];

	// Check if adventurer added
	if(firstCard == 7){
		printf("MINE TEST FAILED: Able to add adventurer for copper\n");
	} else {
		printf("Mine test passed\n");
	}

}

int main(int argc, char *argv[])
{
    testMine();
    return 0;
}