#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testBaron() {

    printf("TESTING BARON\n");

	// Set card array
	int k[10] = { baron, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// Declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Set player's card to be baron
	G.hand[0][0] = 15;

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
	HandCount = G.handCount[0];
	for(int i=0; i < HandCount; i++){
		G.hand[0][i] = 0;
	}
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
	} else {
		printf("Baron test passed\n");
	}

	// Check estate card has been discarded
	if(G.hand[0][0] == 1){
		printf("BARON TEST FAILED: Failed to discard estate card\n");
	} else {
		printf("Baron test passed\n");
	}


	//
	// TEST: Discard estate card as last card in hand
	//

	// Add estate card to END of hand, others cards to 0
	HandCount = G.handCount[0];
	for(int i=0; i < HandCount; i++){
		G.hand[0][i] = 0;
	}
	G.hand[0][HandCount] = 1;

	// Get starting coin count
	startCoinCount = G.coins;

	// Play card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	// Get ending coin count
	endCoinCount = G.coins;

	// Check 4 coins have been added
	if(startCoinCount != (endCoinCount - 4)){
		printf("BARON TEST FAILED: 4 coins not added upon discard\n");
	} else {
		printf("Baron test passed\n");
	}

	// Check estate card has been discarded
	if(G.hand[0][HandCount] == 1){
		printf("BARON TEST FAILED: Failed to discard estate card\n");
	} else {
		printf("Baron test passed\n");
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
	} else if (startSupplyCount > (endSupplyCount + 1)) {
		printf("BARON TEST FAILED: Multiple estate cards removed from supply\n");
	} else {
		printf("Baron test passed\n");
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
	} else {
		printf("Baron test passed\n");
	}

}

int main(int argc, char *argv[])
{
    testBaron();
    return 0;
}