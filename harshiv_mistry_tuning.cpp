// Harshiv Mistry, 10-29-2024, CS302 Fall 2024, Program #2
// FileName: tuning.cpp
//
// This file contains the implementation of Tuning class which is a specialized version of Card class.

/*
 * This file contains the implementation of the `Tuning` class, a specialized subclass of `Card`.
 * The `Tuning` class represents minor adjustments to a car’s performance, affecting acceleration, 
 * handling, and braking attributes.
 *
 * Key functionalities include:
 * - `set_description` and `set_powers` methods to initialize the card’s specific description and 
 *   attributes, with exception handling for invalid states.
 * - Overloaded operators (`=`, `+`, `+=`, `<<`) to enable deep copying, attribute combination, 
 *   and formatted output.
 * - A `build` method to fully configure the card, and a `play_card` method to reset its powers 
 *   after use.
 *
 * Exception handling is applied to ensure robustness, especially during deep copy operations
 * and in cases of missing or invalid data.
 */



#include "harshiv_mistry_cards.h"

//default constructor
Tuning::Tuning(): description(nullptr), acceleration(0), handling(0), braking(0)
{}

// Copy constructor with exception handling
Tuning::Tuning(const Tuning & source) : Card(source), description(nullptr), acceleration(source.acceleration), handling(source.handling), braking(source.braking) {
    if (source.description == nullptr) {
        throw "Source Tuning's description is null in copy constructor.";
    }
    description = new char[strlen(source.description) + 1];
    strcpy(description, source.description);
}

//destructor
Tuning::~Tuning()
{
	delete[] description;
	acceleration = 0;
	handling = 0;
	braking = 0;
}

//sets the description to matching name from the base class
//and also calls base class's set info function.
int Tuning::set_description()
{
	int index = set_info(1);
	const char* tuning_descriptions[] = {
		"Fine-tunes the wheels for optimal stability and control, reducing drift and improving handling through tight turns.",
		"Adjusts the suspension for a smoother ride, allowing the car to maintain speed on bumpy or uneven surfaces.",
		"Reduces drag by streamlining the car’s body, boosting speed slightly on straightaways while maintaining stability.",
		"Specialized tires that grip the road better, enhancing traction in corners and improving overall handling.",
		"Tunes the engine for a balance between power and efficiency, giving a small boost to acceleration without sacrificing control.",
		"Sharpens the car’s steering response, making it easier to handle during quick maneuvers and evasive actions.",
		"Improves brake responsiveness for precise stopping, allowing for later braking before corners without losing control.",
		"Adds a temporary power surge to the engine, granting a brief increase in speed to overtake opponents.",
		"Eases steering effort, reducing driver fatigue and providing better control during prolonged, high-speed races.",
		"Strengthens the car’s frame, allowing for improved stability and durability during high-speed turns and minor collisions."
	};

	if (index < 0 || index >= 10) {  // Validate index range
        throw "Invalid description index in set_description.";
	}
	description = new char[strlen(tuning_descriptions[index]) + 1];
	strcpy(description, tuning_descriptions[index]);
	return index;
}

//sets the individual car attributes at a random to be 
//within the range of the card.
int Tuning::set_powers()
{
	acceleration = random_num(10,30);
	handling = random_num(10,30);
	braking = random_num(10,30);
	total_power = acceleration + handling + braking;
	return 1;
}

//calls the necessary functions to ensure
//the card is built with all information set.
int Tuning::build()
{
	set_description();
	set_powers();
	if (!description) {  // Validate description is set
        throw "Description not set in build.";
	}
	return 1;
}

//used to play card but essentially just 
//deletes the powers in the card so it can't be cheated 
//with. returns the total power to be played. 
int Tuning::play_card()
{
	int power {0};
	power = total_power * effect_type;
	total_power = 0;
	acceleration = 0;
	braking = 0;
	handling = 0;
	return power;
}


/*overloaded operators -- = ; + ; +=; <<(for cout) -- */

// Assignment operator with exception handling for deep copy
Tuning & Tuning::operator=(const Tuning & source) {
    if (this != &source) {
        Card::operator=(source);  // Call base class assignment operator

        if (source.description == nullptr) {
            throw "Source Tuning's description is null in assignment operator.";
        }

        delete[] description;
        description = new char[strlen(source.description) + 1];
        strcpy(description, source.description);

        acceleration = source.acceleration;
        braking = source.braking;
        handling = source.handling;
    }
    return *this;
}
//adds the current obj and passed in obj and returns a copy 
//of the added values. 
Tuning Tuning::operator +(const Tuning & op2) const
{
	Tuning temp;
	static_cast<Card&>(temp) = Card::operator+(op2);
	temp.description = new char[11];	//accurate size for message;
	strcpy(temp.description, "Combo Card");
	temp.acceleration = effect_type * acceleration + op2.effect_type * op2.acceleration;
	temp.handling = effect_type * handling + op2.effect_type * op2.handling;
	temp.braking = effect_type * handling + op2.effect_type *  op2.handling;
	return temp;
}

//adds the passeed in object to the current object 
//and returns the object by reference.
Tuning & Tuning::operator += (const Tuning & op2)
{
	Card::operator+=(op2);
	if (description)
		delete[] description;
	description = new char[11];
	strcpy(description, "Combo Card");

	acceleration += op2.effect_type * op2.acceleration;
	handling += op2.effect_type * op2.handling;
	braking += op2.effect_type * op2.braking;	
	return *this;
}

//displays all data for current class and base class
//in formatted way.
ostream & operator <<(ostream & O, const Tuning & op2)
{
	O << static_cast<const Card&>(op2);
	if (op2.description)
		O << "\nDescription: \t" << op2.description; 
	else 
		O << "\nDescription: \t<empty>";
	O << "\nAcceleration: \t" << op2.acceleration;
	O << "\nHandling: \t" << op2.handling;
	O << "\nBraking: \t" << op2.braking;
	return O;
}



