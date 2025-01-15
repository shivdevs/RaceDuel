// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation of Driver class which is a specialized version of Card class.

/*
 * This file contains the implementation of the `Driver` class, a derived class in the racing-themed card game.
 * The `Driver` class extends the `Card` base class to represent the unique abilities of different drivers,
 * affecting the car’s performance attributes: acceleration, handling, and braking.
 *
 * The class includes:
 * - Randomized `set_powers` method that sets attribute values within a specified range (30-50).
 * - A `set_description` method that assigns a unique description based on the driver’s expertise.
 * - Overloaded operators (`+`, `+=`, `<<`) to support attribute combination and output formatting.
 * - Exception handling to ensure robustness in cases of invalid descriptions, power values, and other data.
 *
 * This implementation leverages `std::string` for automatic memory management of descriptions, simplifying
 * the handling of dynamic content and improving overall reliability.
 */

#include "cards.h"

// Default constructor
Driver::Driver() : description(""), acceleration(0), handling(0), braking(0) {}

// Destructor
Driver::~Driver()
{
	description = "";
	acceleration = 0;
	handling = 0;
	braking = 0;
	//std::string automatically manages memory for description
}
// Sets the description to match the name from the base class and calls base class's set_info function
int Driver::set_description() {
    int index = set_info(2);  // Set the card type to Driver
    const char* driver_descriptions[] = {
        "Excels in taking tight corners at high speed, adding stability in critical moments.",
        "Known for aggressive overtakes, pushing the car's limits while passing opponents.",
        "Master of drafting, gains speed by reducing drag behind other cars.",
        "Skillfully brakes late before turns, maximizing time at high speeds.",
        "Drifting expert, uses controlled slides to navigate tight bends quickly.",
        "Optimizes fuel consumption, extending race duration without sacrificing speed.",
        "Has intimate knowledge of each track, gaining advantage in navigation.",
        "Remains calm under pressure, avoiding mistakes during high-stress situations.",
        "Obsessed with speed, takes risks to gain maximum velocity.",
        "Possesses lightning-fast reflexes, reacting quickly to sudden obstacles."
    };

    if (index < 0 || index >= 10) {  // Validate index range
        throw "Invalid description index in set_description.";
    }

    description = driver_descriptions[index];
    return index;
}

// Sets the individual car attributes randomly within the specified range of 30-50
int Driver::set_powers() {
    if (acceleration < 0 || handling < 0 || braking < 0) {
        throw "Invalid power range in set_powers.";
    }

    acceleration = random_num(30, 50);
    handling = random_num(30, 50);
    braking = random_num(30, 50);
    total_power = acceleration + handling + braking;
    return 1;
}

// Ensures the card is fully set up with all necessary information
int Driver::build() {
    set_description();
    set_powers();
    if (description.empty()) {  // Validate description is set
        throw "Description not set in build.";
    }
    return 1;
}

// Plays the card by resetting its powers, preventing further use of the current values
int Driver::play_card() {
    if (total_power == 0) {
        throw "Cannot play a card with zero or negative total power.";
    }

    int power = total_power * effect_type;
    total_power = 0;
    acceleration = 0;
    braking = 0;
    handling = 0;
    return power;
}

/* Overloaded operators -- + ; +=; << (for cout) */

// Adds the current object and passed-in object, returning a copy of the combined values
Driver Driver::operator+(const Driver & op2) const {
    Driver temp;
    static_cast<Card&>(temp) = Card::operator+(op2);

    temp.description = "Combo Card";  // Set as a generic combined card description
    temp.acceleration = effect_type * acceleration + op2.effect_type * op2.acceleration;
    temp.handling = effect_type * handling + op2.effect_type * op2.handling;
    temp.braking = effect_type * braking + op2.effect_type * op2.braking;
    return temp;
}

// Adds the passed-in object's values to the current object and returns by reference
Driver & Driver::operator+=(const Driver & op2) {
    Card::operator+=(op2);

    description = "Combo Card";  // Set as a generic combined card description
    acceleration += op2.effect_type * op2.acceleration;
    handling += op2.effect_type * op2.handling;
    braking += op2.effect_type * op2.braking;
    return *this;
}

// Displays all data for the current and base class in a formatted way
std::ostream & operator<<(std::ostream & O, const Driver & op2) {
    O << static_cast<const Card&>(op2);
    if (!op2.description.empty())
        O << "\nDescription: \t" << op2.description; 
    else 
        O << "\nDescription: \t<empty>";
    O << "\nAcceleration: \t" << op2.acceleration;
    O << "\nHandling: \t" << op2.handling;
    O << "\nBraking: \t" << op2.braking;
    return O;
}

