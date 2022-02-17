#include "game.h"
#include "deck.h"
#include "card.h"
#include "player.h"
#include <fstream>
#include <iostream>
using namespace std;

void Game::randomEvent(Player* a_player, Player* opponent, Battle_Field* player_field, Deck* a_deck)
{
	srand((unsigned) time(0));
	int n = 1 + (rand() % 3);
	
	if (n == 1) fireball(a_player, opponent);
	else if (n == 2) frost(player_field, opponent);  
	else if (n == 3) eat(player_field, opponent);  
}

void Game::fireball(Player* a_player, Player* opponent)
{
	srand((unsigned) time(0));
	int damage = 1 + (rand() % 3);
	cout << opponent->name() << " hurls a huge fireball at " << a_player->name() << ", dealing " << damage;
	cout << endl << endl;
	a_player->takeDamage(damage);
}

void Game::frost(Battle_Field* player_field, Player* opponent)
{
	cout << opponent->name() << " causes a frost on the battle field, dealing 1 damage to all your creatures.\n\n";
	player_field->takeDamage(1);
}

void Game::eat(Battle_Field* player_field, Player* opponent)
{
	if (!player_field->isEmpty())
	{
		//drawrandom totally removes the node from the battle field
		Node* rat_to_be_eaten = player_field->drawRandom();

		cout << opponent->name() << " eats your " << rat_to_be_eaten->getCard()->name();
		cout << endl << endl;

		//delete rat_to_be_eaten->getCard();
		delete rat_to_be_eaten;
	}
}


