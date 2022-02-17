#include "card.h"
#include "player.h"
#include "deck.h"
#include <iostream>

using namespace std;

Card::Card() : _type(""), _name(""),  _info("") {}	

Card::Card(string type, string name, string info) : _type(type), _name(name), _info(info) {}

string Card::name() const { return _name; }

string Card::info() const { return _info; }

string Card::type() const { return _type; }

void Card::inspect() const
{
	cout << "Type: " << type() << endl;
	cout << "Name: " << name() << endl;
	cout << "Text: " << info() << endl;
}

void Card::attack(){}

void Card::attack(Player & a_Player){}

void Card::setPower(int){}

void Card::boostPower(int){}

void Card::setToughness(int){}

void Card::takeDamage(int){}

void Card::takeSpell(int){}

int Card::power() const {return 0;}

int Card::toughness() const {return 0;}

bool Card::isDead() const {return false;}

void Card::cast(){}

void Card::cast(Card & a_creature){}

void Card::cast(Player & a_player){}

void Card::boost(class Deck * a_field){}

void Card::unBoost(Deck * a_field){}

///CREATURE CLASS FUNCTIONS
Creature::Creature() : Card(), _power(-1), _toughness(-1) {}

Creature::Creature(string t, string n, string i, int power, int toughness)
	: Card(t, n, i), _power(power), _toughness(toughness) {}

int Creature::power() const { return _power; }

int Creature::toughness() const { return _toughness; }

void Creature::setPower(int p) { _power = p; }

void Creature::boostPower(int p) { _power += p; }

void Creature::setToughness(int t) { _toughness = t; }

void Creature::takeSpell(int d) { _toughness += d; } //d can be positive for healing spells, and negative for damage spells

void Creature::takeDamage(int d) { _toughness -= d; }

void Creature::inspect() const
{
 	cout << "\tType: " << type() << endl;
        cout << "\tName: " << name() << endl;
        cout << "\tText: " << info() << endl;
	cout << "\tPower: " << power() << endl;
	cout << "\tToughness: " << toughness() << endl;
}

//Creature attacks other creatue, they both take damage
void Creature::attack(Creature & a_creature)
{
	a_creature._toughness -= _power;

	_toughness -= a_creature._power;

	cout << endl;
	cout << _name << " attacks the " << a_creature.name();
	cout << " for " << _power << " damage\n";
	cout << a_creature.name() << " now has " << a_creature.toughness() << " life left";
	cout << endl << endl;
}

//creatue attacks other player, only player takes damage
void Creature::attack(Player & a_player)
{
	a_player.takeDamage(_power);

	cout << endl;
        cout << _name << " attacks " << a_player.name();
        cout << " for " << _power << " damage\n";
        cout << a_player.name() << " now has " << a_player.life() << " life left";
        cout << endl << endl;
}

bool Creature::isDead() const
{
	if (_toughness <= 0)
	{
		return true;
	}
	else return false;
}



//Spell Functions

Spell::Spell() : Card(), spell_power(0){}

Spell::Spell(string t, string n, string i, int p)
	: Card(t, n, i), spell_power(p){}

int Spell::power() const { return spell_power; }

void Spell::setPower(int p) { spell_power = p; }

void Spell::inspect() const
{
	cout << "\tType: " << type() << endl;
        cout << "\tName: " << name() << endl;
        cout << "\tText: " << info() << endl;
        cout << "\tSpell Power: " << abs(spell_power) << endl;

}

void Spell::cast(Card & a_creature)
{
	a_creature.takeSpell(spell_power);
	cout << endl;
	cout << _name << " is cast on " << a_creature.name() << ", ";
	if (spell_power > 0) cout << "healing it for " << spell_power << " points";
	else cout << "dealing " << abs(spell_power) << " damage to it";
	cout << endl << endl;
}

void Spell::cast(Player & a_player)
{
	if (spell_power > 0) a_player.heal(spell_power);
	else a_player.takeDamage(abs(spell_power));
        
	cout << endl;
        cout << _name << " is cast on " << a_player.name() << ", ";
        if (spell_power > 0) cout << "healing them for " << spell_power << " points";
        else cout << "dealing " << -1 * spell_power << " damage to them";
	cout << endl << a_player.name() << " current life: " << a_player.life();
        cout << endl << endl;
}

Enchantment::Enchantment() : Card(), modifier(0){}

Enchantment::Enchantment(int n) : Card(), modifier(n){}

Enchantment::Enchantment(string t, string n, string i, int p) : Card(t, n, i), modifier(p){}

int Enchantment::power() const {return modifier;}

void Enchantment::inspect() const
{
	cout << "\tType: " << type() << endl;
        cout << "\tName: " << name() << endl;
        cout << "\tText: " << info() << endl;
        cout << "\tPower: " << modifier << endl;

}

void Enchantment::boost(Deck * a_field)
{
	cout << "\nEnchantment enters the battle field\n";
	cout << "Boosting allied creatures by " << modifier;
	cout << "\n";
	a_field->boostAttack(modifier);
}

void Enchantment::unBoost(Deck * a_field)
{
	int n = modifier * -1;
	cout << "\nEnchantment is destroyed\n";
	cout << "Allied creatures lose " << modifier;
	cout << " attack\n";
	a_field->boostAttack(n);
}

