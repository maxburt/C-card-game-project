//Max Burt
//Card Game called Battle Rats
//Not very fun


#include "card.h"
#include "player.h"
#include "deck.h"
#include "game.h"
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	//STEP 1, initilize data for the game
	
	Game game;//init game class

	//init user health/name
	Player* you = new Player();
	you->initPlayer();
	cout << endl;

	//init computer opponent
	Player* opponent = new Player();
	opponent->initComputer();
	cout << endl;

	//init user's deck and battlefield
	Deck* player_deck = new Deck();
        Battle_Field* player_battle_field = new Battle_Field(); 
	Hand * player_hand = new Hand();
        player_deck->generateCards();	//prompt user for cards they want in their deck

	//Step 2: Begin Game Loop

	//begin game loop
	bool game_over = false;
	int loops = 1;
	while (game_over == false)
	{
		//PLAYER TURN BEGIN
		//SUPSTEP 1: Draw card to hand
		cout << "\nYou draw a card\n";
               	player_hand->addCard(player_deck->drawRandom());
        	cout << "\nYour hand is now:\n";
		player_hand->print();
		
		
		//SUPSTEP 2: play card from hand
		int n = 0;
        	if (player_hand->getSize() > 0)
       	 	{
                	cout << "Choose card you wish to play from 1 to ";
                	cout << player_hand->getSize() << ": ";
                	cin >> n;
                	cin.clear();
        	}
        	if (n > 0) player_hand->playCard(n, player_battle_field, you, opponent);
		

		//SUPSTEP 3: show user their hand and battle field
		cout << "\nHand is now:\n";
        	player_hand->print();
		cout << "\nBattle field is now:\n";
        	player_battle_field->print();

		int n2 = 0;
        	if (!player_battle_field->isEmpty())
        	{
                	cout << "Choose card from battle field to attack with from 1 to ";
                	cout << player_battle_field->getSize() << ": ";
                	cin >> n2;
                	cin.clear();
        	}
        	if (n2 != 0) player_battle_field->playCard(n2, opponent, you);
		
		
		//SUBSTEP 4: check for end game conditions
		if (opponent->isDead())
                {
                        game_over = true;
			cout << "\nOpponent is defeated! You win\n";
                }
                else if (player_deck->isEmpty() == true)
                {
                        game_over = true;
                        cout << "You ran out of cards, you lose.\n";
                }
		else//SUPSTEP 4: opponent attacks
		{	
			game.randomEvent(you, opponent, player_battle_field, player_deck);
			player_battle_field->clearDead();
		}


	}

	//STEP 3: Delete the memory
	delete player_battle_field;
	delete opponent;
	delete you;
	delete player_deck;
	delete player_hand;

	return 0;
}
