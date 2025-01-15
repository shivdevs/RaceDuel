// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation of Upgrades class which is a specialized version of Card class.

/*
 * This file contains the implementation of the `Upgrades` class, a derived class in the racing-themed card game.
 * The `Upgrades` class extends the `Card` base class to represent significant performance enhancements to a car,
 * affecting attributes like acceleration, handling, and braking.
 *
 * Key functionalities include:
 * - `set_powers` method to assign attribute values within the 40-60 range, representing major upgrades.
 * - `set_description` method to provide a unique description detailing the upgrade's impact.
 * - Overloaded operators (`+`, `+=`, `<<`) to support combination of attributes and output formatting.
 * - String-based exception handling to ensure robustness in cases of invalid descriptions, power values, and other data.
 *
 * This implementation leverages `std::string` for description handling, providing automatic memory management and
 * simplified code for setting and modifying upgrade descriptions.
 */

#include "cards.h"

// Default constructor
Upgrades::Upgrades() : description(""), acceleration(0), handling(0), braking(0) {}

// Destructor
Upgrades::~Upgrades() = default;  // std::string handles memory for description

// Sets the description based on the card's name from the base class, and calls base class's set_info function
int Upgrades::set_description() {
    int index = set_info(3);  // Set the card type to Upgrades
    const char* upgrades_descriptions[] = {
        "A powerful nitrous system boosts speed for short bursts during critical moments.",
        "Lightweight carbon fiber body kit reduces weight, improving acceleration and handling.",
        "Supercharged engine enhances power output, significantly boosting acceleration.",
        "A race-tuned exhaust optimizes performance, adding a slight boost to speed and sound.",
        "Advanced turbocharger increases engine output, providing a high-speed advantage.",
        "High-performance ECU enhances engine control, improving overall performance.",
        "Lightweight racing wheels enhance handling and acceleration through reduced weight.",
        "High-capacity radiator keeps the engine cool, allowing for prolonged high-speed operation.",
        "Enhanced transmission enables faster gear shifts, providing quicker acceleration.",
        "Racing-grade brake system improves stopping power, allowing for later braking."
    };

    if (index < 0 || index >= 10) {  // Validate index range
        throw "Invalid description index in set_description.";
    }

    description = upgrades_descriptions[index];
    return index;
}

// Sets the car's attributes with values within a specified range of 40-60
int Upgrades::set_powers() {
    if (acceleration < 0 || handling < 0 || braking < 0) {
        throw "Invalid power range in set_powers.";
    }

    acceleration = random_num(50, 80);
    handling = random_num(50, 80);
    braking = random_num(50, 80);
    total_power = acceleration + handling + braking;
    return 1;
}

// Ensures the card is fully set up with all necessary information
int Upgrades::build() {
    set_description();
    set_powers();
    if (description.empty()) {  // Validate description is set
        throw "Description not set in build.";
    }
    return 1;
}

// Plays the card by resetting its powers, preventing further use of the current values
int Upgrades::play_card() {
    if (total_power <= 0) {
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
Upgrades Upgrades::operator+(const Upgrades & op2) const {
    Upgrades temp;
    static_cast<Card&>(temp) = Card::operator+(op2);

    temp.description = "Combo Card";  // Set as a generic combined card description
    temp.acceleration = effect_type * acceleration + op2.effect_type * op2.acceleration;
    temp.handling = effect_type * handling + op2.effect_type * op2.handling;
    temp.braking = effect_type * braking + op2.effect_type * op2.braking;
    return temp;
}

// Adds the passed-in object's values to the current object and returns by reference
Upgrades & Upgrades::operator+=(const Upgrades & op2) {
    Card::operator+=(op2);

    description = "Combo Card";  // Set as a generic combined card description
    acceleration += op2.effect_type * op2.acceleration;
    handling += op2.effect_type * op2.handling;
    braking += op2.effect_type * op2.braking;
    return *this;
}

// Displays all data for the current and base class in a formatted way
std::ostream & operator<<(std::ostream & O, const Upgrades & op2) {
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
