// Harshiv Mistry, 10-29-2024, CS302 Fall 2024, Program #2
// FileName: decks.h
//
// This file contains the implementation of the Node and Deck class that is essentially the DLL of cards 
// used by the RaceDuel Game.

/*
 * This header file defines the core structure of a doubly linked list (DLL) implementation for a card deck,
 * specifically tailored for a card game. It contains two templated classes: `Node` and `Deck`.
 *
 * The `Node` class:
 * - Represents a single node in the doubly linked list, storing a data element of a generic type `T`.
 * - Contains pointers to both the previous and next nodes in the list, allowing bidirectional traversal.
 * - Provides accessor and mutator methods for the node’s data and pointers, along with a display function.
 * - Includes a copy constructor to create a new node from an existing one.
 *
 * The `Deck` class: * - Implements the doubly linked list structure to manage a collection of `Node` objects, representing a deck of cards.
 * - Provides methods to build the deck, display all cards, and allow players to pick cards from the top or bottom of the deck.
 * - Overloads the assignment operator to handle deep copies, ensuring proper memory management.
 * - Contains recursive helper functions for operations such as removing all nodes, displaying nodes, and deep copying the deck.
 * - Uses pointers to `head` and `tail` nodes to manage the list boundaries, along with a `deck_size` variable to track the number of cards.
 *
 * Together, these classes form the foundation for managing a dynamic deck of cards with efficient insertion, deletion, and traversal,
 * supporting essential operations needed in a card game context.
 */


#ifndef HARSHIV_MISTRY_DECKS_H
#define HARSHIV_MISTRY_DECKS_H
#include "harshiv_mistry_cards.h" 	// <-- Core Hierarchy defined there.

/* The `Node` class is a templated node structure designed for a doubly linked list.
 * It stores a data element of a generic type `T` and maintains pointers to both the
 * previous and next nodes in the list.
 */
template <typename T>
class Node
{
	public:
		Node();		//default constructor
		Node(const Node<T> & source);	//copy constructor 
		Node<T> *& get_previous();	//returns previous
		Node<T> *& get_next();		//returns next
		void set_next(Node<T> * next);	//sets next to passed in next
		void set_previous(Node<T> * previous);	//sets the previous to passed in previous
		T& get_data();		//returns the data 
		void display();			//calls the cout << data. 
	private:
		T data;	
		Node<T> * previous;	
		Node<T> * next;
};

/* The `Deck` class is a templated doubly linked list (DLL) structure that represents a deck of cards.
 * It manages nodes of type `Node<T>`, allowing players to build, display, and pick cards from either
 * the top or bottom of the deck. The class provides standard list management functionalities as well
 * as specific operations for a card game context.
 */
template <typename T>
class Deck
{
	public:
		Deck();			//default constructor
		Deck(const Deck &);		//copy constructor
		~Deck();			//destructor
		int display_all() const;		//displays all the cards in the deck 
		int build_deck(int size);	//builds a deck of tuning cards of the given size.
		int pick_card_top(T & picked_card);		//lets the player pick a card from top of the deck.
		int pick_card_bottom(T & picked_card);		//lets the player pick a card from bottom of the deck.
		int shuffle();				//shuffle the deck.
		void remove_all();			//removes the entire deck with proper memory deallocation.

		/*operators overloaded -- =*/
		Deck<T> & operator =(const Deck&);		//overloaded assignment operator
	private:
		Node<T> * head;
		Node<T> * tail;
		int deck_size;		//holds the size of the deck.

		/**recursive private functions**/
		void remove_all(Node<T> *& head);	//removes all nodes in the current DLL.
		int insert(Node<T> *& head);	//inserts a node at the beginning of the DLL.
		int display_all(Node<T> * head) const;	//recursive for display all.
		void copy(Node<T> * src, Node<T> *& dest);	//makes a deep copy of the src.
};

#include "harshiv_mistry_deck.tpp"
#endif 
