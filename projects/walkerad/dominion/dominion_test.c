#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testCheck(){

	printf("Test Baron Card!\n");

	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine
	 , remodel, smithy, village, baron, great_hall };
	
	// declare the game state
	struct gameState G;

	// declare the arrays of all coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	printf("Begin Testing someFunction():\n");
	
	// set the state of your variables so that you will trigger the bug for feast
	//memset(&G, 23, sizeof(struct gameState)); // clear the game state

	initializeGame(2, k, 2, &G);	
	// initializeGame(numPlayer, k, seed, &G); // initialize a new game

	int handCount = 1;
	int p = 1;	
	int bonus = 1;

	G.handCount[p] = handCount; // set this up to trigger bug
	memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set this up to trigger bug
	
	// call the function that will trigger the bug
	cardEffect(p, 0, 0, 0, &G, 1, &bonus);
	
	// verify that you found the bug with failing asserts
	assert(G.coins == handCount * 1 + bonus); // check a condition
	
	printf("Test completed!\n");

}


void testBaron(){

	printf("Testing Baron Card!\n");

	// Set card array
	int k[10] = { baron, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Set player's card to be baron
	G.hand[0][0] = 15;

	// Get starting hand count
	int startHandCount = G.handCount[0];

	// Play baron card
	int p = 15;	// Play baron card
	int bonus = 1;
	cardEffect(p, 0, 0, 0, &G, 0, &bonus);

	// Get ending hand count
	int endHandCount = G.handCount[0];

	// Check card discarded
	assert(startHandCount == (endHandCount + 1));
	
	printf("Test completed!\n");

}


void testFeast(){

	printf("Testing Feast Card!\n");

	// Set card array
	int k[10] = { baron, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Set player's card to be feast
	G.hand[0][0] = 9;

	// Get starting coin count
	int startCoinCount = G.coins;
	// printf("Starting coin count is: %d\n", startCoinCount);

	// Play feast card
	// Set choice1 to buy mine card (should not affect coin count)
	int p = 9;
	int choice1 = 11;
	int bonus = 1;
	cardEffect(p, choice1, 0, 0, &G, 0, &bonus);

	// Get ending coin count
	int endCoinCount = G.coins;
	// printf("Ending coin count is: %d\n", endCoinCount);

	// Check coin count unchanged
	assert(startCoinCount == endCoinCount);
	
	printf("Test completed!\n");

}


void testMine(){

	printf("Testing Mine Card!\n");

	// Set card array
	int k[10] = { baron, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Set player's card to be Mine
	G.hand[0][0] = 11;

	// Play Mine card
	// Set choice1 to -1
	// Don't want to discard a treasure
	int p = 11;
	int choice1 = -1;
	int bonus = 1;
	int cardEffectReturn = cardEffect(p, choice1, 0, 0, &G, 0, &bonus);

	// Check return value is 0
	assert(cardEffectReturn == 0);
	
	printf("Test completed!\n");

}


void testRemodel(){

	printf("Testing Remodel Card!\n");

	// Set card array
	int k[10] = { baron, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Set player's card to be Remodel
	G.hand[0][0] = 12;

	// Play remodel card
	int p = 12;
	int bonus = 1;

	int choice1 = 1; // Card to trash

	// Card to acquire
	// Choosing cutpurse, a card not available in deck
	int choice2 = 21;
	
	int cardEffectReturn = cardEffect(p, choice1, choice2, 0, &G, 0, &bonus);

	// Check return value is -1
	assert(cardEffectReturn == -1);
	
	printf("Test completed!\n");

}



void testRemodelCost(){

	printf("Testing Remodel Card!\n");

	// Set card array
	// Make sure ambassador and adventurer are both included
	int k[10] = { ambassador, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Set player's card to be Remodel
	G.hand[0][0] = 12;

	// Play remodel card
	int p = 12;
	int bonus = 1;

	// Trashing ambassador
	int choice1 = 20; // Card to trash

	// Acquiring adventurer
	int choice2 = 7;
	
	int cardEffectReturn = cardEffect(p, choice1, choice2, 0, &G, 0, &bonus);

	// Check that cardEffect returns error
	assert(cardEffectReturn == -1);
	
	printf("Test completed!\n");

}

int main (int argc, char** argv) {
    // struct gameState G;
    // int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
    //              sea_hag, tribute, smithy
    //             };

    // printf ("Starting game.\n");
    
	//testBaron();
	testRemodelCost();

    return 0;

}





