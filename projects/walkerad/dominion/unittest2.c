#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testMinion() {

    printf("TESTING MINION\n");

	// Set card array
	int k[10] = { minion, council_room, feast, gardens, mine
	 , remodel, smithy, village, adventurer, great_hall };
	
	// Declare the game state
	struct gameState G;
	initializeGame(2, k, 2, &G);

	// Play minion card
	int p = 17;
	int bonus = 0;

	// Test variables
	int startCoinCount;
	int endCoinCount;
	int startNumActions;
	int endNumActions;
	int startPlayedCards;
	int endPlayedCards;
	int endHandCount;


	//
	// TEST: Choose choice 1, to gain 2 coins and an action
	//

	// Get starting coin count and number of actions
	startCoinCount = G.coins;
	startNumActions = G.numActions;

	// Play card
	cardEffect(p, 1, 0, 0, &G, 0, &bonus);

	// Get ending coin count
	endCoinCount = G.coins;
	endNumActions = G.numActions;

	// Check 2 coins have been added
	if(startCoinCount != (endCoinCount - 2)){
		printf("MINION TEST FAILED: 2 coins not added\n");
	} else {
		printf("Minion test passed\n");
	}

	// Check action has been added
	if(startNumActions != (endNumActions - 1)){
		printf("MINION TEST FAILED: action not added\n");
	} else {
		printf("Minion test passed\n");
	}


	//
	// TEST: Choose choice 2, check only 4 cards played
	//

	startPlayedCards = G.playedCardCount;
	
	// Play card
	cardEffect(p, 0, 1, 0, &G, 0, &bonus);

	endPlayedCards = G.playedCardCount;

	// Check action has been added
	if(startPlayedCards <= (endPlayedCards - 4)){
		printf("MINION TEST FAILED: too many cards played\n");
	} else {
		printf("Minion test passed\n");
	}


	//
	// TEST: Store 5 cards in player 2 hand, check redrawn down to 4
	//

	G.handCount[1] = 5;
	for(int i=0; i < 5; i++){
		G.hand[1][i] = 0;
	}

	// Play card
	cardEffect(p, 0, 1, 0, &G, 0, &bonus);

	// Ending handcount
	endHandCount = G.handCount[1];

	// Check handcount is 4
	if(endHandCount != 4){
		printf("MINION TEST FAILED: not 4 cards in hand\n");
	} else {
		printf("Minion test passed\n");
	}

}

int main(int argc, char *argv[])
{
    testMinion();
    return 0;
}