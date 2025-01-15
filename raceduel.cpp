// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file acts as the client program hosting/using the RaceDuel Game.

/* This file acts as the client for the RaceDuel Game Project. The client 
 * responsibilites are not much except to catch the string exceptions throw from
 * within the program, and calling the start game function, which then lets the classes
 * and member functions take over the flow of the program, until the game is ended or 
 * and unexpected situation arises. 
 */

#include "player.h"

int main()
{
	try
	{
		Game new_game;
		new_game.start_game();
	}
	catch(string err)
	{
		cout << "\nError: " << err << endl;
	}
	return 0;
}
