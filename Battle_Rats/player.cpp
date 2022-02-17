#include "player.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

Player::Player() : _life(-1), _name(""){}

Player::Player(int h) : _life(h), _name(""){}

Player::Player(int h, string name) : _life(h), _name(name){}

Player::Player(string name, int h) : _life(h), _name(name){}

Player::Player(string name) : _name(name), _life(-1){}

void Player::initPlayer()
{
	//for fun ascii art
        ifstream Reader("rat1.txt");
        string art = getText(Reader);
        cout << art << endl;
        Reader.close ();
        ////////////////////
	

        string name = "";
        int life = 20;
        cout << "Welcome to battle rats. Enter your name: ";
        getline(cin, name);
        cin.clear();
        _name = name;
        _life = life;;
        cout << "You are now entering ";
        cout << "the Regal Arena. " << endl;
        cout << "Player:\n";
        this->display();
}

void Player::initComputer()
{
	string name = "Two Time Tony";
        int life = 20;
	_name = name;
	_life = life;
        cout << "Your opponent is:\n";
       	this->display();
}


string Player::name() const {return _name;}

int Player::life() const {return _life;}

void Player::takeDamage(int d){_life -= d;}

void Player::heal(int h){_life += h;}

bool Player::isDead() const
{
	if (_life <= 0)
		return true;
	else
		return false;
}

void Player::display() const
{
	cout << "Name: " << _name << endl;
	cout << "Life: " << _life << endl;
}

string Player::getText(ifstream & File)
{
    string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
        while (File.good ())
        {
            std::string TempLine;                  //Temp line
            std::getline (File , TempLine);        //Get temp line
            TempLine += "\n";                      //Add newline character

            Lines += TempLine;                     //Add newline
        }
        return Lines;
    }
    else                           //Return error
    {
        return "ERROR File does not exist.";
    }
}
