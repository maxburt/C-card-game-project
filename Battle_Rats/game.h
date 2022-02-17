//
//by Max Burt
//For project 1 in CS202
//	
//functions here are for the PVE
//aspect of battlerats
//where the player fights a computer opponent
//The functions act as teh computer opponent's "attacks"
//
#ifndef GAME_H
#define GAME_H
#include "deck.h"
#include "player.h"
#include "card.h"
#include "fstream"


class Game
{
	public:
		// randomEvent triggers one of the event functions
		// found in private section
		void randomEvent(Player* a_player, Player* opponent, Battle_Field* player_field, Deck* a_deck);

	private:
		int event_types = 3;

		// RANDOM EVENTS (COMPUTER'S SET OF MOVES)
		void fireball(Player* a_player, Player* opponent); //damages player
		void frost(Battle_Field* player_field, Player* opponent); //damages all cards on battle field
		void eat(Battle_Field* player_field, Player* opponent);  //destroys one card on battlefield
};
#endif
