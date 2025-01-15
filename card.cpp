// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation of the Card class which is the base class for the core hierarchy.

/* 	-- OVERVIEW -- 
 *
 * This file contains the implementation of the `Card` class, the base class in the core hierarchy of a racing-themed card game.
 * The `Card` class provides attributes and methods common to all card types, including name, total power, and effect type.
 * It also includes functions for setting card information, generating random values, and handling memory management for 
 * dynamic string attributes. Operator overloading (e.g., `+`, `+=`, `=`) enables combining card attributes, while 
 * basic exception handling ensures robustness for invalid card types and ranges.
 */

#include "cards.h"

//using namespace std;
//default constructor
Card::Card(): total_power(0), effect_type(0), name(nullptr), card_type(0) {}

// Copy constructor with exception handling
Card::Card(const Card & source) : total_power(source.total_power), effect_type(source.effect_type), name(nullptr), card_type(source.card_type) {
    if (source.name == nullptr) {
        throw "Source Card's name is null in copy constructor.";
    }
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);
}

//destructor
Card::~Card()
{
	delete [] name;
	name = nullptr;
	total_power = 0;
	effect_type = 0;
	card_type = 0;
}

//sets all the private data member to build a
//card. Returns 1 for success, 0 failure.
int Card::set_info(int type)
{
	if (type < 1 || type > 3) {
        throw "Invalid Card Type: Must be 1 (Tuning), 2 (Driver), or 3 (Upgrades).";
    }
	//total power stays 0 until the dervied class sets it.
	card_type = type;
	int num = set_name();
	decide_type();		//sets effect_type to 1 or -1
	return num;
}



//sets the name from a random list of names based on 
//card type.
int Card::set_name()
{
	const char* tuning_names[] = {
		"Precision Alignment", 
		"Suspension Tweak", 
		"Enhanced Aerodynamics", 
		"High-Performance Tires", 
		"Engine Recalibration", 
		"Fine-Tuned Steering", 
		"Brake Adjustment", 
		"Turbo Boost", 
		"Power Steering Boost", 
		"Chassis Reinforcement"
	};	
	const char* driver_names[] = {
		"Expert Cornering", 
		"Aggressive Overtake", 
		"Drafting Master", 
		"Late Braker", 
		"Drift Prodigy", 
		"Fuel Efficiency Wizard", 
		"Track Knowledge", 
		"Calm Under Pressure", 
		"Speed Demon", 
		"Sharp Reflexes"
	};
	const char* upgrades_names[] = {
		"Nitrous Injection System", 
		"Carbon Fiber Body Kit", 
		"Supercharged Engine", 
		"Race-Tuned Exhaust", 
		"Advanced Turbocharger", 
		"Performance ECU", 
		"Lightweight Wheels", 
		"High-Capacity Radiator", 
		"Enhanced Transmission", 
		"Racing Brakes"
	};
	int size = 10;	//size of the const arrays of names.
	//random choice for which list and index
	int index = random_num(0,size-1);

	if (card_type == 1)	//tuning card
	{
		name = new char[strlen(tuning_names[index]) + 1];
		strcpy(name, tuning_names[index]);
	}
	else if (card_type == 2) //driver card
	{
		name = new char[strlen(driver_names[index]) + 1];
		strcpy(name, driver_names[index]);

	}
	else if (card_type == 3) //upgrades card
	{
		name = new char[strlen(upgrades_names[index]) + 1];
		strcpy(name, upgrades_names[index]);

	}
	else 
		throw "Unknown Card Type in set_name.";
	return index;
}

//decides on random whether the card will be a positive 
//or negative effect type card. returns 1 for success, 0 for failure
int Card::decide_type()
{
	//gets a random num for 2 posibilities 
	int number = random_num(0,1);

	if (number == 0)
	{
		effect_type = -1;
		return 1;
	}
	else if (number == 1)
	{
		effect_type = 1;
		return 1;
	}
	return 0;
}

//The function takes in min and max values and return a random num 
//within the bounds.
int Card::random_num(int min, int max)
{
	if (min > max) {
        throw "Invalid Range: min should be <= max.";
    }
	random_device rd;
	mt19937 gen(rd());	//gets the random num	
	uniform_int_distribution<> distrib(min,max);
	return distrib(gen);
}

// Assignment operator with exception handling for deep copy
Card& Card::operator=(const Card & source) {
    if (this != &source) {
        if (source.name == nullptr) {
            throw "Source Card's name is null in assignment operator.";
        }

        delete[] name;
        name = new char[strlen(source.name) + 1];
        strcpy(name, source.name);

        total_power = source.total_power;
        effect_type = source.effect_type;
        card_type = source.card_type;
    }
    return *this;
}

//only adds the total power in regards to effect_type.
Card Card::operator +(const Card & op2) const
{
	Card temp;
	temp.total_power = (total_power * effect_type) + (op2.total_power * op2.effect_type);
	if (temp.total_power < 0)	//negative result
	{
		temp.effect_type = -1;	//sets the accurate effect_type value
		temp.total_power = (temp.total_power * -1);	//to make the power value positive.
	}
	else
		temp.effect_type = 1;	//sets the accurate effect_type value
	temp.card_type = card_type;
	temp.name = new char[11];	//accurate size for message;
	strcpy(temp.name, "Combo Card");
	return temp;
}

//only adds the total power in regards to effect_type.
Card & Card::operator += (const Card & op2)
{
	total_power = (total_power * effect_type) + (op2.total_power * op2.effect_type);
	if (total_power < 0)	//negative result
	{
		effect_type = -1;	//sets the accurate effect_type value
		total_power = (total_power * -1); 	//to make the power value positive.
	}
	else
		effect_type = 1;	//sets the accurate effect_type value
	if (name)	//deletes name and reset it to be combo name.	
		delete[] name;
	name = new char[11];	//accurate size for message;
	strcpy(name, "Combo Card");
	return *this;
}

//displays all of the current data in a formatted way.
ostream & operator<<(ostream & O, const Card & to_disp)
{
	if (to_disp.name)
		O << "Name: \t\t" << to_disp.name << endl;
	else
		O << "Name: <empty>\n";
	O << "Total Power: \t" << (to_disp.total_power * to_disp.effect_type) << endl;
	O << "Effect Type: \t";
	if (to_disp.effect_type == 1)
		O << "Positive" << endl;
	else
		O << "Negative" << endl;
	O << "Card Type: \t";
	if (to_disp.card_type == 1)
		O << "Tuning Card";
	else if (to_disp.card_type == 2)
		O << "Driver Card";
	else if (to_disp.card_type == 3)
		O << "Upgrades Card";
	return O;
}

