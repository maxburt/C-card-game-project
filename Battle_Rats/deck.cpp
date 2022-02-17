#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

Node::Node() : card(nullptr), next(nullptr), prev(nullptr){}

Node::Node(const Node & a_node) : next(nullptr), prev(nullptr)
{
	Card * a_card = a_node.card;

	Card * card_node = nullptr;
	if (a_card->type() == "Creature")
	{
		string type = a_card->type();
		string name = a_card->name();
		string info = a_card->info();
		int power = a_card->power();
		int toughness = a_card->toughness();
		card_node = new Creature(type, name, info, power, toughness);
	}
	else if (a_card->type() == "Spell")
	{
		string type = a_card->type();
                string name = a_card->name();
                string info = a_card->info();
                int power = a_card->power();
                card_node = new Spell(type, name, info, power);
	}
}

Node::~Node()
{

	if (card != nullptr)
	{
		delete card;
		card = nullptr;
	}
	
}

Card * Node::getCard(){return card;}

Node * Node::getNext(){return next;}
                
Node * Node::getPrev(){return prev;}

void Node::setCard(Card* a_card){card = a_card;}
                
void Node::setNext(Node* a_node){next = a_node;}

void Node::setPrev(Node* a_node){prev = a_node;}

Deck::Deck() : head(nullptr), size(0){}

Deck::Deck(const Deck & a_deck) : head(nullptr), size(0)
{
	//size gets incremended by add_card function
	

	Node * curr = a_deck.head; 
	while(curr != nullptr)
	{
		if (curr->getCard()->type() == "Creature")
		{
			string type =curr->getCard()->type();
			string name = curr->getCard()->name();
			string info = curr->getCard()->info();
			int power = curr->getCard()->power();
			int toughness = curr->getCard()->toughness();
			Creature* a_card = new Creature(type, name, info, power, toughness);
			Node * a_node = new Node();
			a_node->setCard(a_card);
			this->addCard(a_node);

		}
		else if (curr->getCard()->type() == "Spell")
		{
			string type = curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
			Spell * a_card = new Spell(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

		}
		else if (curr->getCard()->type() == "Enchantment")
		{
			string type = curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        Enchantment * a_card = new Enchantment(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);
		}
		curr = curr->getNext();
	}

}

Deck::~Deck()
{
	Node* curr = head;
	while (curr != nullptr)
	{
		Node* deleteMe = curr;
		curr = curr->getNext();
		delete deleteMe;
	}
}

Node * Deck::getHead(){return head;}

void Deck::clearDead(){}

void Deck::boostAttack(int a){}

void Deck::print()
{
	if (head == nullptr)
	{
		cout << "Empty\n";
	}
	else
	{
		Node* curr = head;
		while (curr != nullptr)
		{
			
			curr->getCard()->inspect();
			cout << endl;
			curr = curr->getNext();
		}
	}
}

void Deck::generateCards()
{
	int rats, big_rats, heals, enchants;
        cout << "How many basic rats do you want in your deck? Choose1-7\n";
        cin >> rats;
        cout << "How many big rats do you want in your deck? Choose 0-3\n";
        cin >> big_rats;
        cout << "How many healing spells do you want in your deck? Choose 0-4\n";
        cin >> heals;
        cout << "How many enchantments do you want?\n";
        cin >> enchants;

	int idx = 0;
        while (idx < rats)
        {
                Creature * rat = new Creature("Creature", "Rat", "A basic rat", 1, 1);
                Node * aNode = new Node();
                aNode->setCard(rat);
                this->addCard(aNode);
                idx++;
        }
        idx = 0;
        while (idx < big_rats)
        {
                Creature * big_rat = new Creature("Creature", "Big Rat", "A larger basic rat", 2, 2);
                Node * aNode = new Node();
                aNode->setCard(big_rat);
                this->addCard(aNode);
                idx++;
        }
        idx = 0;
        while (idx < heals)
        {
                Spell * heal = new Spell("Spell", "Heal", "A weak healing spell", 1);
                Node * aNode = new Node();
                aNode->setCard(heal);
                this->addCard(aNode);
                idx++;
        }
        idx = 0;
        while (idx < enchants)
        {
                Enchantment * enchantment = new Enchantment("Enchantment", "Rally The Rats", "Boosts all creatures on battlefield attack", 2);
                Node * aNode = new Node();
                aNode->setCard(enchantment);
                this->addCard(aNode);
                idx++;
        }


}

int Deck::getSize() const { return size; }

bool Deck::isEmpty() const
{
	if (head == nullptr) return true;
	else return false;
}

bool Deck::contains(string name) const
{
	bool contains = false;
	Node * curr = head;
	while (curr != nullptr)
	{
		if (curr->getCard()->name() == name) contains = true;
		curr = curr->getNext();
	}
	return contains;
}

bool Deck::containsType(string type) const
{
	bool contains = false;
        Node * curr = head;
        while (curr != nullptr)
        {
                if (curr->getCard()->type() == type) contains = true;
                curr = curr->getNext();
        }
        return contains;
}

//only the pointer to the node is passed into
//deck class
void Deck::addCard(Node * new_node)
{
	size++;
	if (head == nullptr)
	{
		head = new_node;
	}
	else
	{
		insert(head, new_node);
	}
}

void Deck::insert(Node* head, Node* insert_me)
{
	if (head->getNext() == nullptr)
	{
		head->setNext(insert_me);
		insert_me->setPrev(head);
		insert_me->setNext(nullptr);
	}
	else
	{
		insert(head->getNext(), insert_me);
	}

}

Node * Deck::draw()
{
	size--;
	if (head != nullptr)
	{
		Node* drawNode = head;
		head = head->getNext();	    //set head to next node
		head->setPrev(nullptr);

		drawNode->setNext(nullptr); //disconnect drawNode from current deck
		drawNode->setPrev(nullptr); //disconnect drawNode from current deck
		return drawNode;
	}
	else
	{
		cout << "Deck is empty. Cannot Draw.\n";
		return nullptr;
	}
}

Node * Deck::drawByName(string name)
{
	if (head == nullptr)            //empty deck
        {
                size = 0;
                cout << "Deck is empty. Cannot Draw.\n";
                return nullptr;
        }
	else if (this->contains(name) == true)
	{
		Node * curr = head;
		while (curr != nullptr)
		{
			if (curr->getCard()->name() == name)
			{
				break;
			}
			curr = curr->getNext();
		}
		if (curr != nullptr)
		{
			//curr is now draw node
			if (head->getNext() == nullptr)    //only one card left
        		{
                		size = 0;
                		Node* a_node = head;
                		head = nullptr;
                		a_node->setNext(nullptr);
                		a_node->setPrev(nullptr);
                		return a_node;
        		}
			else if (curr->getPrev() == nullptr) //curr is head
                	{
                        	head = head->getNext();
                        	head->setPrev(nullptr);
                        	curr->setNext(nullptr);
                        	curr->setPrev(nullptr);
                        	size--;
                        	return curr;
                	}
			else
			{
				curr->getPrev()->setNext(curr->getNext());
                        	if (curr->getNext() != nullptr) curr->getNext()->setPrev(curr->getPrev());
                        	curr->setPrev(nullptr);
                        	curr->setNext(nullptr);
                        	size--;
                        	return curr;
			}
		}
		return nullptr;
	}
	else return nullptr;
}

Node * Deck::drawRandom()
{
	if (head == nullptr)		//empty deck
	{
		size = 0;
		cout << "Deck is empty. Cannot Draw.\n";
                return nullptr;
	}
	else if (head->getNext() == nullptr)	//only one card left
	{
		size = 0;
		Node* a_node = head;
		head = nullptr;
		a_node->setNext(nullptr);
		a_node->setPrev(nullptr);
		return a_node;
	}
	else					//draws a random card
        {
		Node* curr = head;
		srand((unsigned) time(0));
		int n = 1 + (rand() % size);	//nth node will be drawn
		int idx = 1;
		while (idx < n && curr->getNext() != nullptr)//traverse list to nth node
		{
			curr = curr->getNext();
			idx++;
		}
		if (curr->getPrev() == nullptr) //curr could be any node in the list
						//even the head, this checks if its the head
		{
			head = head->getNext();
			head->setPrev(nullptr);
			curr->setNext(nullptr);
			curr->setPrev(nullptr);
			size--;
			return curr;
		}
		else
		{
			curr->getPrev()->setNext(curr->getNext());
			if (curr->getNext() != nullptr) curr->getNext()->setPrev(curr->getPrev());
			curr->setPrev(nullptr);
			curr->setNext(nullptr);
			size--;
			return curr;
		}
        }

}

Hand::Hand() : Deck() {}

Hand::Hand(const Hand & a_hand)
{
        Node * curr = a_hand.head;
        while(curr != nullptr)
        {
                if (curr->getCard()->type() == "Creature")
                {
                        string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        int toughness = curr->getCard()->toughness();
                        Creature* a_card = new Creature(type, name, info, power, toughness);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

                }
                else if (curr->getCard()->type() == "Spell")
                {
                        string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        Spell * a_card = new Spell(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

                }
		else if (curr->getCard()->type() == "Enchantment")
                {
                        string type = curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        Enchantment * a_card = new Enchantment(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);
                }
                curr = curr->getNext();
        }

}

Hand::~Hand()
{
	Node* curr = head;
        while (curr != nullptr)
        {
                Node* deleteMe = curr;
                curr = curr->getNext();
                delete deleteMe;
        }
	head = nullptr;
}

//PLAY CARD NOT DONE
void Hand::playCard(int card_to_play, Deck * battle_field, Player * self, Player * opponent)
{
	if (head == nullptr)
	{
		cout << "\nHand is empty. You can't play a card\n";
	}
	else
	{
		int idx = 1;
        	Node * curr = head;
        	while (idx < card_to_play && curr->getNext() != nullptr)
		{
			curr = curr->getNext();
			idx++;
		}
		
		if (curr->getCard()->type() == "Creature" || curr->getCard()->type() == "Enchantment")
		{
			cout << "\nYou play " << curr->getCard()->name() << " onto the battle field.\n";
			if (curr->getCard()->type() == "Enchantment")
			{
				curr->getCard()->boost(battle_field);
			}
			battle_field->addCard(this->drawByName(curr->getCard()->name()));
		}
		else
		{
			cout << "You cast " << curr->getCard()->name() << "\n";
			if (curr->getCard()->name() == "Heal") curr->getCard()->cast(*self);
			battle_field->addCard(this->drawByName(curr->getCard()->name()));//to remove it from hand
			battle_field->clearDead();//to get rid of non-permanent heal spell from battlefield
		}


	}
}

Battle_Field::Battle_Field() : Deck() {}

Battle_Field::Battle_Field(const Battle_Field & a_field)
{
	Node * curr = a_field.head;
        while(curr != nullptr)
        {
                if (curr->getCard()->type() == "Creature")
                {
                        string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        int toughness = curr->getCard()->toughness();
                        Creature* a_card = new Creature(type, name, info, power, toughness);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

                }
	        else if (curr->getCard()->type() == "Spell")
                {
                        string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        Spell * a_card = new Spell(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

                }
		else if (curr->getCard()->type() == "Enchantment")
                {
                        string type = curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        Enchantment * a_card = new Enchantment(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);
                }
                curr = curr->getNext();
        }
	
}

Battle_Field::Battle_Field(Deck & a_deck)
{
        Node * curr = a_deck.getHead();
        while(curr != nullptr)
        {
                if (curr->getCard()->type() == "Creature")
                {
                        string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        int toughness = curr->getCard()->toughness();
                        Creature* a_card = new Creature(type, name, info, power, toughness);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

                }
		else if (curr->getCard()->type() == "Spell")
                {
                        string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int power = curr->getCard()->power();
                        Spell * a_card = new Spell(type, name, info, power);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);

                }
		else if (curr->getCard()->type() == "Enchantment")
		{
			string type =curr->getCard()->type();
                        string name = curr->getCard()->name();
                        string info = curr->getCard()->info();
                        int modifier = curr->getCard()->power();
                        Enchantment * a_card = new Enchantment(type, name, info, modifier);
                        Node * a_node = new Node();
                        a_node->setCard(a_card);
                        this->addCard(a_node);
		}
                curr = curr->getNext();
        }
}

Battle_Field::~Battle_Field()
{
	Node* curr = head;
        while (curr != nullptr)
        {
                Node* deleteMe = curr;
                curr = curr->getNext();
                delete deleteMe;
        }
	head = nullptr;
}

void Battle_Field::boostAttack(int a)
{
	cout << "Boosting allied cards by " << a << " power\n"; 
	Node* curr = head;
	while (curr != nullptr)
	{
		curr->getCard()->boostPower(a);
		curr = curr->getNext();
	}
}

void Battle_Field::boostAttack(string name, int a)
{
	Node* curr = head;
        while (curr != nullptr)
        {
                if (curr->getCard()->name() == name) 
		{
			curr->getCard()->boostPower(a);
		}
                curr = curr->getNext();
        }
}

void Battle_Field::takeDamage(int a)
{
	cout << "All allied creatures take " << a << " damage\n";
        Node* curr = head;
        while (curr != nullptr)
        {
                curr->getCard()->takeDamage(a);
                curr = curr->getNext();
        }
}

void Battle_Field::takeDamage(string name, int a)
{
        cout << "All allied " << name << "s take " << a << " damage\n";
        Node* curr = head;
        while (curr != nullptr)
        {
                if (curr->getCard()->name() == name)
                {
                        curr->getCard()->takeDamage(a);
                }
                curr = curr->getNext();
        }
}

void Battle_Field::playCard(int n, Player * opponent, Player * self)
{
	if (head != nullptr)
	{
		Node* curr = head;
		int idx = 1;
		while (curr->getNext() != nullptr && idx < n)
		{
			curr = curr->getNext();
			idx++;
		}
		if (curr->getCard()->type() == "Creature")
		{
			curr->getCard()->attack(*opponent);
		}
		else if (curr->getCard()->type() == "Spell")
		{
				curr->getCard()->cast(*self);
		}
	}

}

void Battle_Field::playCard(int card_to_play, int card_to_attack, Player * opponent, Player * self)
{

}

void Battle_Field::clearDead()
{
	if (head == nullptr)
	{
		cout << "\nBattle Field is empty\n";
		return;
	}
	else
	{
		clear_dead_recursive(head);
	}
}

void Battle_Field::clear_dead_recursive(Node * the_head)
{
	if (the_head == nullptr)
	{
		return;
	}

	clear_dead_recursive(the_head->getNext());

	bool dies = false;
	if (the_head->getCard()->type() == "Spell") //all spells get cleared
	{
		dies = true;
		cout << the_head->getCard()->name() << " dissolves into the ether\n\n";
		size--;
	}
	else if (the_head->getCard()->type() == "Enchantment")
	{
		//do nothing
		//enchantments dont get cleared
	}
	else if (the_head->getCard()->toughness() <= 0) //creatures with 0 or less toughness get cleared
	{
		dies = true;
		cout << the_head->getCard()->name() << " dies\n\n";
		size--;
	}
	if (dies == true)
	{
		Node* temp = the_head;

		if (temp->getNext() != nullptr && temp->getPrev() != nullptr) 
		{
			temp->getNext()->setPrev(temp->getPrev());
			temp->getPrev()->setNext(temp->getNext());
		}
		else if (temp->getNext() == nullptr && temp->getPrev() != nullptr)
		{
			temp->getPrev()->setNext(nullptr);
		}
		else if (temp->getNext() != nullptr && temp->getPrev() == nullptr)
		{
			// new head is needed
			head = head->getNext();
			head->setPrev(nullptr);
		}
		else if (temp->getNext() == nullptr && temp->getPrev() == nullptr)
		{
			head = nullptr;
		}
		delete temp;
	}
	return;
}
