// Harshiv Mistry, 10-29-2024, CS302 Fall 2024, Program #2
// FileName: player.h
// // This file contains the class definition for the players that will be playing the game as well as a Game class.

/*
 *  ---OVERVIEW---
 *
 *  This file defines the main player and game management classes for the RaceDuel Game, establishing the framework 
 *  for player interactions, game flow, and race outcomes. The `Player` class represents each individual player, who 
 *  has a unique car with a power level and three types of card decks (`TuningDeck`, `DriverDeck`, and `UpgradesDeck`). 
 *  These decks allow players to draw cards that modify their car's attributes, impacting performance in the race.
 *
 *  - `Player` class includes functionalities for building each deck, drawing cards, and displaying deck contents. 
 *    It also supports operator overloads for comparing players based on car power and displaying player information.
 *  - `Game` class is the central managing class that orchestrates the gameplay between two players. It includes methods 
 *    for game instructions, menu interactions, and starting races. The class handles player interactions, score tracking, 
 *    and determining the winner of each race, with a future option for supporting additional players.
 *
 *  Together, these classes create the foundation for managing players and the overall game, enabling players to compete 
 *  in head-to-head races by strategically utilizing their decks and modifying car attributes.
 */


#include "harshiv_mistry_decks.h"	//<-- Decks defined there


/* The Player class represents a single player in the RaceDuel Game in which
 * each player will have thier own car and their car power, as well as 
 * three decks (1) Tuning Deck (2) Driver Deck (3) Upgrades Deck
 */
class Player
{
	public:
		Player();
		~Player();
		int build_all_decks(int size);	//calls the build function for all decks
		int draw_card();		//lets the user draw cards from the decks
		int build_car(int power);		//starts the game.
		int display_tuning();	//diplays the tuning deck
		int display_driver();	//displays the driver deck
		int display_upgrades();	//displays the upgrades deck

		/*overloaded operator --  <;>; <=; >=; ==; !=; <<; >>*/
		bool operator <(const Player & other) const;
		bool operator >(const Player & other) const;
		bool operator <=(const Player & other) const;
		bool operator >=(const Player & other) const;

		bool operator ==(const Player & other) const;
		bool operator !=(const Player & other) const;
	
		friend ostream & operator <<(ostream &, const Player &);	//displays name and car power.
		friend istream & operator >>(istream &, Player &);		//reads in player's name

	private:
		string name;	//name of the player
		int car_power;	//the total power of the user's car.
		//one of each decks for the player
		Deck<Tuning> tuning_deck;
		Deck<Driver> driver_deck;
		Deck<Upgrades> upgrades_deck;
};

/* This class is the Game class which will be the all managing class
 * running the game and bringing everything together. The current
 * functionality will only support 2 players dueling each other but more
 * player support can be added for future.
 */
class Game
{
	public:
		Game();
		~Game();
		int instructions();		//simple function for instructions on the game. 
		int build_car_phase();		//lets players pick 5 cards to start the game.
		int start_game();		//starts the actual game playing. 
		int input(int min, int max);	//input function with error checking.
		int race();				//lets players race and returns the winner.	
		int show_score();		//displays the current score for both players.
	private:
		//two players in the game.
		Player first;
		Player second;
		int score_first;	//number of races won for first player.
		int score_second;	//number of races won for second player. 	
};
