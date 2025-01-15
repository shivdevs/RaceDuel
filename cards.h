// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the class definitions for the cards and the derived classes from cards (the core hierarchy)

/*	---OVERVIEW---
 * * This header file defines the core hierarchy for a racing-themed card game, where players use various types of 
 * cards to modify and enhance their vehicles. The `Card` class serves as the base class, encompassing common attributes 
 * shared by all cards, such as the card's name, total power, and effect type (positive or negative). Derived from `Card`,
 * three specialized card types (`Tuning`, `Driver`, and `Upgrades`) provide specific effects on a car’s attributes, 
 * including Acceleration, Handling, and Braking.
 *       
 *       --Core Hierarchy--
 *
 *				 Card
 *			   /  |  \
 *			  /   |   \
 *			 /    |    \
 *		Tuning Driver Upgrades

 * - `Tuning` cards represent minor adjustments made to a car, introducing small changes in performance, which can be either 
 *    positive or negative.
 * - `Driver` cards simulate the influence of a driver’s skills, offering moderate adjustments to car performance based on 
 *    the driver’s strengths or weaknesses.
 * - `Upgrades` cards provide significant modifications, mirroring the effect of major car improvements, and apply larger 
 *    adjustments to core attributes.
 *
 * The file also includes several overloaded operators for each class to enable easy interaction and modifications between 
 * card objects, allowing for seamless integration into the game’s mechanics.*
 */

//Libraries needed
#include <vector>
#include <string>
#include <cstring>
#include <string>
#include <random>
#include <iostream>

using namespace std;

/* The Card class is the base class in the core hierarchy in this project. It will include
 * all the common attributes that make sense for all types of cards used in this game, such as
 * the name of the card. the total power of the card, whether the card will have positive or 
 * negative effect on the player's car.
 */
class Card
{
	public:
		Card();				//default constructor
		Card(const Card &);	//copy constructor
		~Card();			//destructor
		int set_info(int type);	//sets the name, type of card and, effect_type of the card.
		int set_name();	//sets the name from a list of names based on card type.
		int decide_type();		//decides whether the card will be positive change or negative change card.
		int random_num(int min, int max);	//returns a random number from the given range.
		
		/*overloaded operators -- = ; + ; +=; <<(for cout) -- */
		Card & operator =(const Card&);		//overloaded assignment operator.
		Card operator +(const Card & op2) const;	//adds current obj and op2 and returns a new object with added values.
		Card & operator += (const Card & op2);		//adds the op2 values to current obj, and returns it.
		friend ostream & operator<<(ostream &, const Card &);	//overloaded to work in cout << & prints formatted.

	protected:
		int total_power;		//the numeric value that changes the base level of the car.
		int effect_type;		//1 meaning positive change, and -1 meaning negative change.
	private:
		char * name;			//the name or title of the card.
		int card_type;			//holds the type of card it is -- (1)Tuning, (2)Driver, & (3)Upgrades.
};

/* The Tuning class is derived from Card, it a specialized card type, that imitates behaviours 
 * of tuning a car in real world. As such it make low effect change to the car (can be good or bad).
 * The class will manage things such as description of what the card does, the specific values of 
 * acceleration, handling and braking which will changes the levels of the player's car.
 */
class Tuning: public Card
{
	public:
		Tuning();					//default constructor
		Tuning(const Tuning &);		//copy constructor
		~Tuning();					//destructor
		int set_description();		//sets the description.
		int set_powers();			//sets car attributes randomly.
		int build();				//calls all the necessary functions to "build" a completed card.
		int play_card();			//lets the user play the powers of the card.
		
		/*overloaded operators -- = ; + ; +=; <<(for cout) -- */
		Tuning & operator =(const Tuning&);		//overloaded assignment operator.
		Tuning operator +(const Tuning & op2) const;	//adds current obj and op2 and returns a new object with added values.
		Tuning & operator += (const Tuning & op2);		//adds the op2 values to current obj, and returns it.
		friend ostream & operator <<(ostream &, const Tuning &);	//overloaded to work in cout << & prints formatted.

	private:
		char * description;		//description of what the card is or does.
		int acceleration;		//adds to acceleration
		int handling;			//adds to handling
		int braking;			//adds to braking
};

/* The Driver class is derived from Card, it a specialized card type, that imitates behaviours 
 * of what a car driver brings to a race in real world. As such it makes moderate effect change 
 * to the car (can be good or bad). The class will manage things such as description of what the 
 * card does, the specific values of acceleration, handling and braking which will changes the 
 * levels of the player's car.
 * 
 */
class Driver: public Card
{
	public:
		Driver();					//default constructor
		~Driver();					//destructor
		int set_description();		//sets the description.
		int set_powers();			//sets car attributes randomly.
		int build();				//calls all the necessary functions to "build" a completed card.
		int play_card();			//lets the user play the powers of the card.
		
		/*overloaded operators -- = ; + ; +=; <<(for cout) -- */
		Driver operator +(const Driver & op2) const;	//adds current obj and op2 and returns a new object with added values.
		Driver & operator += (const Driver & op2);		//adds the op2 values to current obj, and returns it.
		friend ostream & operator <<(ostream &, const Driver &);	//overloaded to work in cout << & prints formatted.

	private:
		string description;		//description of what the card is or does.
		int acceleration;		//adds to acceleration
		int handling;			//adds to handling
		int braking;			//adds to braking
};

/* The Upgrades class is derived from Card, it a specialized card type, that imitates behaviours 
 * of what major upgrades to cars does to car's power in real world. As such it makes moderate effect change 
 * to the car (can be good or bad). The class will manage things such as description of what the 
 * card does, the specific values of acceleration, handling and braking which will changes the 
 * levels of the player's car.
 */
class Upgrades: public Card
{
	public:
		Upgrades();					//default constructor
		~Upgrades();					//destructor
		int set_description();		//sets the description.
		int set_powers();			//sets car attributes randomly.
		int build();				//calls all the necessary functions to "build" a completed card.
		int play_card();			//lets the user play the powers of the card.
		
		/*overloaded operators -- = ; + ; +=; <<(for cout) -- */
		Upgrades operator +(const Upgrades & op2) const;	//adds current obj and op2 and returns a new object with added values.
		Upgrades & operator += (const Upgrades & op2);		//adds the op2 values to current obj, and returns it.
		friend ostream & operator <<(ostream &, const Upgrades &);	//overloaded to work in cout << & prints formatted.

	private:
		string description;		//description of what the card is or does.
		int acceleration;		//adds to acceleration
		int handling;			//adds to handling
		int braking;			//adds to braking
};
