// by Max Burt
// for Projct 1 in CS202
//
// Creates a player class, to store info about player's
// name life total, cards, etc.
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <fstream>
class Player
{
	public: 
		//Constructors
		Player();
		Player(int startingHealth);
		Player(std::string name);
		Player(int startingHealh, std::string name);
		Player(std::string name, int startingHealth);
		void initPlayer();
                void initComputer();

		//Getters
		//For use in Game class
		std::string name() const;
		int life() const;
		void display() const;
		bool isDead() const;
		
		//Modifiers
		void takeDamage(int d);
		void heal(int h);
	
	protected:
		int _life;
		std::string _name;

		// to read in ascii art for fun
		std::string getText(std::ifstream & File);
};
#endif
