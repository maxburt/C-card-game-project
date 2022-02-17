//Max Burt
//This file defines several classes.

//First is  a Node
//	The Node contains a card pointer, and next and prev pointers
//	The Node class will be used by the Deck, Hand, and Battle_field classes
//

//Second is a Deck
//	The Deck is a base class for a linked list of nodes (i.e. cards).
//

//Third is Battle_Field
//	The Battle_Field class is where cards go after they are played.
//	It is like a deck in that it is a list of nodes (i.e. cards)
//	But it has added functionality for clearing dead cards (creatures with < 0 toughness)
//	



#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "player.h"
#include <iostream>
#include <string>

class Node
{
	public:
		Node();
		Node(const Node & a_node);
		~Node();
		class Card * getCard();
		Node * getNext();
		Node * getPrev();

		void setCard(Card* a_card);
		void setNext(Node* a_node);
		void setPrev(Node* a_node);
	private:
		Card * card;
		Node * next;
		Node * prev;
};

class Deck
{
	public:
		Deck();
		~Deck();
		Deck(const Deck & a_deck);
		Node * getHead();
		int getSize() const;

		void print();
		void addCard(Node* a_node);
		void generateCards();			//fills deck with cards, allocates memory
		Node * draw();				//draws first card
		Node * drawRandom();			//draws random card
		Node * drawByName(std::string name);	//draws card that matches name (for use in hand class)
		bool isEmpty() const;
		bool contains(std::string name) const;
		bool containsType(std::string type) const;
		virtual void clearDead();
		virtual void boostAttack(int a);

	protected:
		void insert(Node* head, Node* insert_me); //recursive helper function
		Node * head;
		int size;
};

class Hand : public Deck
{
	public:
		Hand();
		~Hand();
		Hand(const Hand & a_hand);
		void playCard(int card_to_play, Deck * the_battle_field , Player * self, Player * opponent);

};

class Battle_Field : public Deck
{
	public:
		Battle_Field();
		Battle_Field(const Battle_Field & a_field);
		Battle_Field(Deck & a_deck);
		~Battle_Field();
		void boostAttack(int a); //boosts attack of all creatures
	       	void boostAttack(std::string name, int a);//boosts specific creatures
		void takeDamage(int a); // damages all creatures
		void takeDamage(std::string name, int a); //damages only name creaures

		void playCard(int card_to_play, Player * opponent, Player * self);



		void playCard(int card_to_play, int card_to_attack, Player * opponent, Player * self);
		//The above function is for P2P, not implemented yet
		//the second integer parameter is the card on the opponents battlefield that
		//the player is attacking


		// clearDead removes dead creatures and spell cards (which are non permanent) from the battlefield
		void clearDead();
	protected:
		void clear_dead_recursive(Node * a_head); //recursive helper function

};
#endif
