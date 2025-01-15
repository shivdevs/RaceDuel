# RaceDuel Game Project

## Overview
RaceDuel is a two-player, racing-themed card game where players strategically draw cards to modify their car’s attributes—acceleration, handling, and braking—and compete in head-to-head races. The game combines strategy, randomness, and resource management for an engaging gameplay experience.

---

## Game Mechanics

### Card Types
1. **Tuning Cards**
   - Represents minor adjustments to car performance.
   - Impacts attributes like acceleration, handling, and braking.
   - Effects can be positive or negative.

2. **Driver Cards**
   - Reflects a driver's unique expertise.
   - Introduces moderate changes to car attributes.
   - Includes skills like "Sharp Reflexes" and "Drafting Master."

3. **Upgrades Cards**
   - Represents major enhancements to the car.
   - Significantly improves attributes.
   - Features upgrades like "Supercharged Engine" and "Nitrous Injection."

### Gameplay Phases
1. **Build Car Phase**
   - Players draw five cards of their choice from any deck to boost their car’s initial power level.

2. **Race Phase**
   - Players take turns drawing additional cards and racing.
   - Races continue until one player wins five rounds.

### Win Condition
The first player to win five races is declared the champion.

---

## Features

- **Card System**
  - Three card types with unique attributes and effects.
  - Supports randomization, positive/negative effects, and operator overloading for card interactions.

- **Dynamic Deck Management**
  - Implements a doubly linked list (DLL) for efficient deck operations.
  - Allows shuffling and drawing cards from the top or bottom of the deck.

- **Game Management**
  - Central `Game` class handles gameplay logic, score tracking, and user interaction.

- **Player Interaction**
  - Customizable player names and gameplay choices.
  - Operators (`<`, `>`, `+=`) overloaded for player and card comparisons.

---

## File Descriptions

### Core Classes
1. **`cards.h` & `card.cpp`**
   - Defines the base `Card` class and derived classes (`Tuning`, `Driver`, `Upgrades`).
   - Includes randomization, description setting, and operator overloading.

2. **`tuning.cpp`**
   - Implements the `Tuning` class for minor car adjustments.
   - Supports small changes to attributes like handling and braking.

3. **`driver.cpp`**
   - Implements the `Driver` class for moderate attribute changes.
   - Describes unique driver skills and their effects.

4. **`upgrades.cpp`**
   - Implements the `Upgrades` class for significant car enhancements.
   - Major boosts to performance through advanced car modifications.

5. **`decks.h` & `deck.tpp`**
   - Defines the `Deck` class using a templated doubly linked list.
   - Manages card collections and supports deck-specific operations.

6. **`player.h` & `player.cpp`**
   - Defines the `Player` class, representing individual players with decks and car power.
   - Handles player actions like drawing cards and displaying decks.

7. **`game.cpp`**
   - Implements the `Game` class, orchestrating gameplay, turns, and race results.

8. **`raceduel.cpp`**
   - Entry point of the game. Initializes the game and handles exceptions.

---

## How to Run

1. Clone the repository:
```bash
git clone <repository-url>
```
2. Compile:
```
g++ -o raceduel raceduel.cpp card.cpp tuning.cpp driver.cpp upgrades.cpp player.cpp game.cpp -std=c++11
```
3. Run:
```
./raceduel
```

---

## Author

**Harshiv Mistry**  
Project Date: 10-29-2024