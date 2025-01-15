// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation of the Node and Deck class that is essentially the DLL of cards 
/*
 * This file implements the `Node` and `Deck` classes, which together form a doubly linked list (DLL) structure 
 * to manage a deck of cards for a card game.
 *
 * `Node` Class:
 * - Represents an individual element in the DLL, storing data and pointers to previous and next nodes.
 * - Includes methods to access and modify its data and pointers, and a display function to output its content.
 *
 * `Deck` Class:
 * - Manages a DLL of `Node` objects, providing functions to build, display, and pick cards from the deck.
 * - Supports picking cards from the top or bottom and recursive methods for insertion, display, and cleanup.
 * - Implements deep copying through a copy constructor, assignment operator, and helper `copy` function.
 * - Uses string-based exception handling to manage empty or invalid states.
 *
 * Together, these classes enable dynamic management of a card deck with efficient memory handling and 
 * error-checking mechanisms.
 */


#ifndef DECK_TPP
#define DECK_TPP


/********** Node Class Implementatiuon *******************/
//default constructor
	template <typename T>
Node<T>::Node(): previous(nullptr), next(nullptr)
{}

//copy constructor
	template <typename T>
Node<T>::Node(const Node<T> & source):data(source.data), previous(nullptr), next(nullptr)
{}


//returns previous
	template <typename T>
Node<T> *& Node<T>::get_previous()
{
	return previous;
}

//returns next
	template <typename T>
Node<T> *& Node<T>::get_next()
{
	return next;
}

//sets class next to passed in next
	template <typename T>
void Node<T>::set_next(Node<T> * next)
{
	this->next = next;
}

//sets class previous to passed in previous
	template <typename T>
void Node<T>::set_previous(Node<T> * previous)
{
	this->previous = previous;
}

//just returns the data.
	template <typename T>
T& Node<T>::get_data()
{
	return data;
}

//calls the cout << data to display the data
//assumption is that cout << operator has been overloaded to work. 
	template <typename T>
void Node<T>::display()
{
	cout << "======================\n" << data << "\n======================\n";
}


/******* Deck Class implementation *************/
//default constructor
	template <typename T>
Deck<T>::Deck(): head(nullptr), tail(nullptr), deck_size(0)
{}

//copy constructor with exception handling. 
	template <typename T>
Deck<T>::Deck(const Deck & source): head(nullptr), tail(nullptr), deck_size(source.deck_size)
{
	if (!source.head)
		throw "Empty Source List";
	copy(source.head, head);
}

//destructor
	template <typename T>
Deck<T>::~Deck()
{
	//just calls the remove all function.	
	remove_all();
}

//removes all items in the DLL -- wrapper function
	template <typename T>
void Deck<T>::remove_all()
{
	if (!head) return;
	remove_all(head);
}

//removes all items in the DLL -- recursive function to get it done.
	template <typename T>
void Deck<T>::remove_all(Node<T> *& head)
{
	if (!head) return;	//basecase
	Node<T> * hold = head->get_next();	//hold on to head's next ptr
	delete head;
	head = hold;
	if (head)
		head->set_previous(nullptr);
	remove_all(head);
}

//builds the DLL of the passed in size.
	template <typename T>
int Deck<T>::build_deck(int size) 
{
	if (!size) 	//when built enough nodes.
		return 0;
	int num = insert(head);
	return num + build_deck(size-1);	//size basically works at index or counter.
}

//inserts a new node in the beginning of the DLLs.
	template <typename T>
int Deck<T>::insert(Node<T> *& head)
{
	if (!head) //empty list add the first node.
	{
		head = new Node<T>;
		head->get_data().build();	//sets all the info in the card.
									//head->get_data() = 1;
		head->set_next(nullptr);	//set next to null
		head->set_previous(nullptr);	//set prev to null
		this->tail = head;	//only one node so both points to the same node.
		++deck_size;
		return 1;
	}
	if (!head->get_next())	//staying one node before to set the previous ptr.
	{
		Node<T> * temp = new Node<T>;
		temp->get_data().build();
		//temp->get_data() = 2;
		temp->set_next(nullptr);
		temp->set_previous(head);	//prev points to head as head is one node before last
		head->set_next(temp);
		this->tail = head->get_next();
		++deck_size;
		return 1;
	}
	return insert(head->get_next());
}

//displays all items in the DLL.
template <typename T>
int Deck<T>::display_all() const
{
	if (!head) 
		throw "Empty Deck";
	int num = display_all(head);	
	cout << "\nDisplayed " << num << " items!\n";
	return num;
}

//displays all items in the DLL -- recursive to get it done.
template <typename T>
int Deck<T>::display_all(Node<T> * head) const
{
	if (!head) return 0;
	head->display();
	return 1 + display_all(head->get_next());
}

//copies the first card over to the passed in card, and
//removes the card from the deck.
	template <typename T>
int Deck<T>::pick_card_top(T & picked_card)
{
	if (!head) 
		throw "Empty Deck";
	picked_card = head->get_data();	//copies the values
	Node<T> * hold = head->get_next();
	delete head;
	head = hold;
	head->set_previous(nullptr);
	return 1;
}

//copies the last card over to the passed in card, and
//removes the card from the deck.
	template <typename T>
int Deck<T>::pick_card_bottom(T & picked_card)
{
	if (!tail) 
		throw "Empty Deck";
	picked_card = tail->get_data();	//copies the values
	Node<T> * hold = tail->get_previous();
	delete tail;
	tail = hold;
	tail->set_next(nullptr);
	return 1;
}

//make a complete copy of the passed in source.
	template <typename T>
void Deck<T>::copy(Node<T> * src, Node<T> *& dest)
{
	if (!src) return;	//end of list.
	Node<T> * temp = new Node<T>;
	temp->get_data() = src->get_data();	//copy the data.
	temp->set_next(nullptr);	//handle next
	if (!dest)
	{
		temp->set_previous(nullptr);
		dest = temp;
		this->tail = dest;
	}
	else
	{
		temp->set_previous(dest);	//handle previous
		dest->set_next(temp);
		this->tail = dest->get_next();	//update the tail
	}
	copy(src->get_next(), dest->get_next());
}

//this function shuffles the deck. 
 	template <typename T>
int Deck<T>::shuffle()
{
	remove_all();
	build_deck(50);
	return 1;
}
//overloaded assignment operator to handle deep copy.
	template <typename T>
Deck<T> & Deck<T>::operator =(const Deck & source)
{
	if (this != &source)
	{
		if (head)
			remove_all();
		if (!source.head)
			throw "Empty Source List";
		copy(source.head, head);
		deck_size = source.deck_size;
	}
	return *this;
}

#endif
