//
//
//by Max Burt
//For project 1 in CS202
//
//This file defines a few classes
//First, base class Card, which acts as a hub
//with virual functions, for use in dynamic binding
//with the two classes derived from Card.
//
//These other three classes are Creature
//Spell, and Enchantment.
//
//Spells are nonpermnant and are removed from the game after they are cast from the hand
//Creaures stay in the battle field after they are played, until they are killed
//Enchantments also stay on the battlefield and can be destroyed./

#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include "player.h"
#include "deck.h"

class Card
{
	public:
		//Constructors
		Card();			
		Card(std::string type, std::string name, std::string info);	

		//Accessors
		std::string type() const;
		std::string name() const;
		std::string info() const;
	
		//FOR USE IN DERIVED CLASSES
		virtual void inspect() const;
		virtual void attack();
		virtual void attack(Player & a_Player); 
		virtual void setPower(int);
		virtual void boostPower(int);
		virtual void setToughness(int);
		virtual void takeDamage(int);
		virtual void takeSpell(int);
		virtual int power() const;
		virtual int toughness() const;
		virtual bool isDead() const;	
		virtual void cast();
		virtual void cast(Card & a_creature);
                virtual void cast(Player & a_player);
		virtual void boost(class Deck * a_field);
                virtual void unBoost(Deck * a_field);

	protected:
		std::string _type;
		std::string _name;
		std::string _info;
};

class Creature : public Card
{
	public:
		//Constructors
		Creature();
		Creature(std::string t, std::string n, std::string i, int power, int toughness);

		int power() const;
		int toughness() const;
		void setPower(int power);
		void boostPower(int power);
		void setToughness(int toughness);
		void takeSpell(int damage);			// increases or decreases _toughness
		void takeDamage (int damage);			// similar to takeSpell
		void inspect() const;				// displays info about Creature		
		bool isDead() const;				// returns true if toughness is 0 or less
		
		void attack(Creature & a_creature); 		// function to attack a creature
		void attack(Player & a_Player);     		// functtion to attack a player
	protected:
		int _power;
		int _toughness;

};

class Spell : public Card
{
	public:
		Spell();
		Spell(std::string t, std::string n, std::string i, int p);

		int power() const;
		void setPower(int p);
		void inspect() const; 
		void cast(Card & a_creature);		//casts spell on creature
		void cast(Player & a_player);		//casts spell on player

	protected:
		int spell_power;	//is greater negative for offensive spells, is positive for healing spells
};

class Enchantment : public Card
{
	public:
		Enchantment();
		Enchantment(int p);
		Enchantment(std::string t, std::string n, std::string i, int p);
		void inspect() const;
		int power() const;
		void boost(Deck * a_field);	//Boosts creatures on battle field's attack by modifer
		void unBoost(Deck * a_field); 	//if the enchantment is removed from battlefield, its modifer is removed from allied creatues)
	protected:
		int modifier;
};

#endif
