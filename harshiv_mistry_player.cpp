// Harshiv Mistry, 10-29-2024, CS302 Fall 2024, Program #2
// FileName: player.cpp
//
// This file contains the implementation for the player class.

#include "harshiv_mistry_player.h"

/* The Player class includes functions to build decks, draw cards, build a car, and display each deck.
 * It also provides overloaded operators for comparison of players based on car power, as well as input
 * and output stream operators for reading and displaying player information.  
 */

//default constructor
Player::Player(): name(""), car_power(0)
{}

//destructor
Player::~Player()
{
	name = "";
	car_power = 0;
}

//calls the build functions for all the decks.
int Player::build_all_decks(int size)
{
	tuning_deck.build_deck(size);
	driver_deck.build_deck(size);
	upgrades_deck.build_deck(size);
	return 1;	
}

//prompts the user for which deck they would like to 
//draw a card from and adds the card to thier car's base level.
int Player::draw_card()
{
	int choice {6};	//player's choice of card to pick
	int res {1};
	int input {0};	//flag for error handling bad input
	int valid_input{0};	//flag for error handling bad input.
	while (!valid_input || (choice < 1 || choice > 4))
	{
		cout 	<< "\nWhich deck to pick the card from?\n"
			<< " [1] Tuning Deck\t--> Low Change\n"
			<< " [2] Driver Deck\t--> Moderate Change\n"
			<< " [3] Upgrades Deck\t--> High Change\n"
			<< " [4] Shuffle All Decks \n"
			<< "RESPONSE: ";
		cin 	>> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input. Please enter an integer.\n";
		}
		else
		{
			if (!(choice < 1 || choice > 3))	//just error checking for bad input.
			{
				valid_input = 1;
				cin.ignore(1000, '\n');

				while (!input || (res < 1 || res > 2))
				{

					cout << "\nFrom Top(1) or Bottom(2): ";
					cin >> res;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input. Please enter an integer.\n";
					}
					else
					{
						cin.ignore(1000, '\n');
						input = 1;
						if (res < 1 || res > 2)
							cout << "\nInvalid choice!!\nTry again!\n";
					}
				}
			}
			if (choice == 1)	//draw tuning card.
			{
				Tuning draw;
				display_tuning();
				if (res == 1) //draw from top
					tuning_deck.pick_card_top(draw);	
				else if (res == 2) //draw from bottom.
					tuning_deck.pick_card_bottom(draw);
				cout << "\n\n\n"
					<< "YOU GOT:\n"
					<< draw
					<< "\n\n\n";
				car_power += draw.play_card();
				cout << "\n\nYour New Car Power: " << car_power << endl << endl;
			}
			else if (choice == 2) //draw driver card.
			{
				Driver draw;
				display_driver();
				if (res == 1) //draw from top
					driver_deck.pick_card_top(draw);	
				else if (res == 2) //draw from bottom.
					driver_deck.pick_card_bottom(draw);
				cout << "\n\n\n"
					<< "YOU GOT:\n"
					<< draw
					<< "\n\n\n";
				car_power += draw.play_card();
				cout << "\n\nYour New Car Power: " << car_power << endl << endl;

			}
			else if (choice == 3)	//draw upgrades card.
			{
				Upgrades draw;
				display_upgrades();
				if (res == 1) //draw from top
					upgrades_deck.pick_card_top(draw);	
				else if (res == 2) //draw from bottom.
					upgrades_deck.pick_card_bottom(draw);
				cout << "\n\n\n"
					<< "YOU GOT:\n"
					<< draw
					<< "\n\n\n";
				car_power += draw.play_card();
				cout << "\n\nYour New Car Power: " << car_power << endl << endl;

			}
			else if (choice == 4)	//shuffle decks
			{
				tuning_deck.shuffle();
				driver_deck.shuffle();
				upgrades_deck.shuffle();	
				cout << "\n\nAll decks have been shuffled!!\n";
				//draw_card();
			}
			else
				cout << "\nInvalid choice!!\nTry again\n";
		}
	}

	return 1;
}
//builds the user's car -- basically setting the car 
//at a random value from a predeterminded range.
int Player::build_car(int power)
{
	if (!power) return 0;
	car_power = power;
	return 1;
}

//calls the display function for tuning deck.
int Player::display_tuning()
{
	return tuning_deck.display_all();
}

//calls the display function for driver deck.
int Player::display_driver()
{
	return driver_deck.display_all();
}

//calls the display function for upgrades deck.
int Player::display_upgrades()
{
	return upgrades_deck.display_all();
}

/*overloaded operator --  <;>; <=; >=; ==; !=; <<; >>*/

//returns true if car_power < other's car_power.
bool Player::operator <(const Player & other) const
{
	if (car_power < other.car_power) 
		return true;
	return false;
}

//returns true if car_power > other's car_power.
bool Player::operator >(const Player & other) const
{
	if (car_power > other.car_power) 
		return true;
	return false;
}

//returns true if car_power <= other's car_power.
bool Player::operator <=(const Player & other) const
{
	if (car_power <= other.car_power) 
		return true;
	return false;

}

//returns true if car_power >= other's car_power.
bool Player::operator >=(const Player & other) const
{
	if (car_power >= other.car_power) 
		return true;
	return false;

}

//returns true if car_power == other's car_power.
bool Player::operator ==(const Player & other) const
{
	if (car_power == other.car_power) 
		return true;
	return false;

}

//returns true if car_power != other's car_power.
bool Player::operator !=(const Player & other) const
{
	if (car_power != other.car_power) 
		return true;
	return false;

}

//displays the name and carpower.
ostream & operator <<(ostream & O, const Player & to_disp)
{
	O << "\nName: " << to_disp.name << "\nCar Power: " << to_disp.car_power;
	return O;
}

//reads in the name of the player. 
istream & operator >>(istream & IN, Player & to_read)
{
	getline(IN, to_read.name);
	return IN;
}

