#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testAmbassador() {

    printf("TESTING AMBASSADOR\n");

	// Set card array
	int k[10] = { ambassador, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// Declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Play ambassador card
	int p = 20;
	int bonus = 0;

	// Test variables
	int returnVal;
	int estateFound;


	//
	// TEST: Try to discard ambassador card
	//

	// Play card, set choice 1 == handPos
	returnVal = cardEffect(p, 0, 0, 0, &G, 0, &bonus);

	// Check return value is not success
	if(returnVal == 0){
		printf("AMBASSADOR TEST FAILED: Discarded ambassador card successfully\n");
	} else {
		printf("Ambassador test passed\n");
	}


	//
	// TEST: Discard estate card
	//

	G.handCount[0] = 5;
	G.hand[0][0] = 1; // Add estate card to hand
	G.hand[0][1] = 17;
	G.hand[0][2] = 17;
	G.hand[0][3] = 20;
	G.hand[0][4] = 4;

	// Choice 1: card to discard, 1 for estate card
	// Choice 2: Num of cards to discard, 1
	// Hand position: Location of ambassador card, 3
	returnVal = cardEffect(p, 1, 1, 0, &G, 3, &bonus);

	// Check if estate card still in hand
	estateFound = 0;
	for(int i=0; i < 5; i++){
		if(G.hand[0][i] == 1){
			estateFound = 1;
		}
	}

	// Check return value is not success
	if(estateFound){
		printf("AMBASSADOR TEST FAILED: Failed to discard estate card\n");
	} else {
		printf("Ambassador test passed\n");
	}

}

int main(int argc, char *argv[])
{
    testAmbassador();
    return 0;
}