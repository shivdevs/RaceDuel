// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the Game class implementation that makes the entire project come together.

/*
 * This file contains the implementation of the Game class, which orchestrates the flow of the entire racing card game.
 * The Game class manages the setup, rules, and progression of a two-player game, where each player builds and modifies
 * their car's power level by drawing from different decks of cards. Key phases include displaying instructions,
 * the "Build Car" phase where players initially enhance their cars by drawing cards, and the main gameplay loop
 * where players take turns drawing cards and racing. The game continues until one player achieves 5 race wins,
 * at which point the winner is declared. The Game class includes functions for handling player input, displaying
 * scores, and conducting races, with error handling for invalid inputs.
 */

#include "player.h"

//default constructor
Game::Game(): score_first(0), score_second(0)
{}

//destructor
Game::~Game()
{
	score_first = 0;
	score_second = 0;
}

//prints out the instructions and "how to play the game"
//stuff. 
int Game::instructions()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";	//clear screen
	cout << "\t\t\t\tWelcome to Race Duel!!\n\n"
		 << "   OVERVIEW:\n"
		 << "\t * This is a two player game. Both players have thier own basic car.\n"
		 << "\t * Cards have what's called a 'Car Power' which indicates to the capabilities of the car.\n"
		 << "\t * Both players start with the same car level.\n"
		 << "\t * In the 'Build Car' phase of the game, players get to pick 5 cards from any deck they prefer\n"
		 << "\t * There are three different Deck of Cards in this game.\n"
		 << "\t\t (1) Tuning Deck   -- this type of card helps you make MINOR changes to your car.\n"
		 << "\t\t (2) Driver Deck   -- this type of card helps you make MODERATE changes to you car.\n"
		 << "\t\t (3) Upgrades Deck -- this type of card helps you make MAJOR changes to you car.\n\n"
		 << "\t * With any of these three types of cards, they can be both POSITIVE CHANGE or NEGATIVE CHANGE.\n"
		 << "\t   This means they can either add to your car's power level or reduce your car's power level.\n"
		 << "\n\n\n"
		 << "  HOW TO PLAY:\n"
		 << "\t (1) At the start of the game, both player's have the chance to enter their nickname.\n"
		 << "\t (2) Then, the player's start the build car phase in which player's get to draw 5 different cards.\n"
		 << "\t (3) After the build car phase, they start their first race. The player with higher car power wins.\n"
		 << "\t (4) Then, after each race, player's get to draw one more card of thier choice.\n"
		 << "\t (5) After each draw, they race again.\n"
		 << "\t (6) This continues until either of the players wins 5 total races.\n"
		 << "\n*****************************************************************************************************\n\n\n"
		 << "\tWhen ready, input anything and press enter.\n";
	string cont(""); 	//just a place holder to keep the program waiting until the user is ready to begin.
	cin >> cont;
	cin.ignore(10000, '\n');
	return 1;
}

int Game::build_car_phase()
{
	cout << "\nBUILD CAR PHASE" << first << endl;
	for (int i = 0; i < 5; ++i)
		first.draw_card();
	cout << "\n\n\n\nBUILD CAR PHASE" << second << endl;
	for (int i = 0; i < 5; ++i)
		second.draw_card();
	cout << "\nAfter the building phase, " << first << endl << second << endl;
	cout << "Ready to Race? Input anything and press enter!\n";
	string cont("");
	cin >> cont;
	cin.ignore(1000, '\n');
	race();
	return 1;
}

int Game::start_game()
{
	//builds the decks for both players.
	first.build_all_decks(50);
	second.build_all_decks(50);
	first.build_car(1000);
	second.build_car(1000);
	
	//instructions time
	instructions();
	//reads in player's names.
	cout << "\n\nPlease enter Player 1's name: ";
	cin >> first;
	cout << "\n\nPlease enter Player 2's name: ";
	cin >> second;
	cout << "\nYour Names are:\n" << first << endl << second << endl;
	cout << "\n\t When ready to start the Build Car Phase, input anything and press enter\n";
	string cont("");
	cin >> cont;
	cin.ignore(1000, '\n');

	//start build car phase.
	cout << "\n\n\n\n\n\n\n\n\n";
	build_car_phase();
	while (score_first < 5 && score_second < 5)
	{
		cout << first << endl << "Pick a Card!! \n";
		first.draw_card();
		cout << second << endl << "Pick a Card!! \n";
		second.draw_card();
		cont = "";
		cout << "\n\nWhen ready to RACE, input anything, press enter\n";
		cin >> cont;
		cin.ignore(1000, '\n');
		race();
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen
	//declare the winner.
	if (score_first == 5)	//player one won the game.
		cout << first << "\n\nWON THE GAME!!!\n";
	else if (score_second == 5)
		cout << second << "\n\nWON THE GAME!!!\n"; //second player won the game.
	
	//ending message.
	cout << "\n\nThank you for playing RaceDuel!!\n\n\t\t\tGood Bye:))\n\n\n\n\n\n\n";
	return 1;
}

//gets and returns input with error checking within the given range.
int Game::input(int min, int max)
{
	int user_input{0};	//stores user's input
	int valid{0};	//flag used for error checking incorrect input.
	do
	{
		cin >> user_input;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid Input! Please enter an Interger\n";
		}
		else if (user_input < min || user_input > max)
		{
			cout << "\nInvalid Choice!\nTry again!!\n";
		}
		else
			valid = 1;
	}while (!valid || (user_input < min || user_input > max));
	return user_input;
}

//lets the two players race against each other.
int Game::race()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n"
		<< "Alright, ready to RACE!!!!!\n"
		<< "\n\nOn your MARKS...\n\nGet set...\n\nGOOOOOOOOOO!!!!\n"
		<< "\n...\n....\n.....\n......\n.......\n";
	if (first > second)	//player one wins
	{
		cout << first << "\nWINS THE RACE!!!\nCongrats!\n";
		++score_first;
	}
	else if (second > first)	//player two wins
	{
		cout << second << "\nWINS THE RACE!!!\nCongrats!\n";
		++score_second;
	}
	else
	{
		cout << "\nYOU GUYS ARE GOOD....\nThe Race is a TIE!\n";
	}
	cout << "\nUpdated Score are:\n";
	show_score();
	return 1;
}

//displays the scores of the two players
int Game::show_score()
{
	cout << first << "\nWins: " << score_first << endl;
	cout << second << "\nWins: " << score_second << endl;
	return 1;
}

