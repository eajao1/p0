/*	 
 * Project 0 -- Part 1: AssocList.h (required for everyone) 
 ************************************* 
 *	 
 * Your task is to complete the following AssocList class so that all	
 * methods behave as expected and the class satisfies the IMap interface.	
 * The class is templated so that it may be used for various key (K) and	 
 * value (V) types. The structure stores keys themselves, and pointers 
 * to values. This is so the 'lookup' method may return a null pointer
 * when a key cannot be found. 'remove' returns true if a key-value is
 * found and removed and false if no change was made. 'add' replaces
 * an existing value for the input key or adds a new key-value pair. 
 * The ctor sets up an empty association list, the dtor properly cleans up
 * the datastructure (freeing used memory) and 'size' reports the # of keys.	 
 * (See IMap.h for more details.) There are various correct ways to complete
 * the assignment, ask if you have questions. Search for "TODO" in this file.	 
 *	 
 ************************************	 
 */ 

#pragma once 	 	
#include "IMap.h"	 
#include <iostream>

using namespace std;

/*
 ************************************	 
 * Honor pledge (please write your name.) 	 	
 * 	 	
 * I, Eniola Ajao, have completed this code myself, without
 * unauthorized assistance, and have followed the academic honor code. 
 * 	 	
 * Edit the code below to complete your solution. 
 * 
 *************************************
 */

template <typename K, typename V>	 
class AssocList
: public IMap<K,V>	 
{ 	 	
    // A private struct useful for links of the list	 
    struct Link 	 	
    { 	 	
	K k; //key
	V* v; // Pointer to value	 	
	Link* next; // Pointer to next link

	Link(const K _k, V* const _v, Link* const _next)
	    : k(_k), v(_v), next(_next)	
	{ 	 	
	}
    }; 

    private:
    // A counter for the total number of keys in the association list
    unsigned count = 0; //set count to 0 so I can increment it.

    // A pointer to the root node	 
    Link* root;

    public: 
    AssocList()	 
	: count(0), root(0) { }

    ~AssocList() 
    { 	 	
	while (root) 
	    remove(root->k); 
    }

    // A method for mutably extending the map with a new key-value association 
    void add(const K& key, V* const val)	 
    {
        remove(key);  //remove the key
        root = new Link(key, val, root); // create a new key value pair, add it to the front.
        count++; // increment count
    } 	 	

    // A method for mutably deleting a key (and its value) from the current map
    bool remove(const K& key)	 
    { 	

        if (root)  // if there is a root...
        {
            if (root->k == key) // if you find the key in the root
            {
                Link* old_root = root; // create a pointer to the old root 
                root = root->next;  // point the root to the next
                delete old_root;  // delete the old_root, a pointer to the root.
                count--;
                return true;
            }

            else
            {
                Link* node = root->next;  // create a new node that is a pointer to root's next.
                Link* previous_node = root; // create another new node to represent a previous node

                while (node) //while a node exists...
                {
                    if (node->k == key) //if you find the key..
                    {
                        previous_node->next = node->next;  //set previous node's next to node's next
                        delete node; // delete the node
                        count--; // decrement count
                        return true;  //return true
                    }
                    else
                    {
                        previous_node = node;  // otherwise, set previous_node to node
                        node = node->next;     // set node to it's next so we can keep traversing through
                    }
                }
            }
            return false;
        }
        else
            return false;  // if you don't find it, return false. 
    }

    // A method for looking up the value associated with a given key
    V* lookup(const K& key) const 
    { 
	// Start at the root 	 	
	Link* node = root; 	 	

	// Follow the linked list until reaching null 
	// or a node where the key matches	 
	while (node && node->k != key)
	    node = node->next; 

	// Return the associated value, or null 	 	
	if (node) 
	    return node->v; 	 	
	else
	    return 0; 	 	
    } 	 	

    // A method for reporting the current number of keys in the map 	 	
    unsigned size() const 	 	
    { 	 	
	// TODO: write size method 
        return count; //return count, which has been modified in the above code.

    }
};	 
