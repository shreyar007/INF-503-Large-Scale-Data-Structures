//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 4
//@sb3292
//*******************
//*******************

#pragma once

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <iostream>
#include <cstring>
#include "math.h"

using namespace std;

// structure for genomic seq data
struct Gen_seq_pt
{
	// ------------- Declaring variables to use --------------

	// genome fragments stored in char array 
	char Gen_seq_fr[11];

	// location of the stored genome fragments
	int Gen_seq_place;

	//pointer pointing to next location
	Gen_seq_pt* next;

	// ------------- Other Helper Function Definitions --------------
	
	// checking the genome fragmnet with location 
	void Find_loc(char* hw_fragment, int g_place)
	{
		int i = 0;
		// looping through all genome fragments
		while(i<11)
		{
			Gen_seq_fr[i] = hw_fragment[i];
			i++;
		}
		Gen_seq_place = g_place;
		next = NULL;
	}
};

// class describing the hash hash_table chaining
class Chain_collision
{
	public:

		// ------------- Declaring variables to use --------------

		// pointer pointing to the g_begin 
		Gen_seq_pt* g_begin;

		// ------------- Constructor and Destructor Function -------------

		// default constructor
		Chain_collision()
		{
			// setting g_begin to null
			this->g_begin = NULL;
		}

		// ------------- Other Helper Function Definitions --------------

		// getting the fragment 
		Gen_seq_pt* Get_place(char* hw_fragment)
		{
			// making a curr pointer
			Gen_seq_pt* curr = g_begin;

			// while curr has nodes
			while (curr != NULL)
			{
				// comparing the genome fragment
				if (strncmp(curr->Gen_seq_fr, hw_fragment, 11) == 0)
				{
					return curr;
				}
				curr = curr->next;
			}
			return NULL;
		}

		// fragment in location
		void Chain_next(char* hw_fragment, int g_place)
		{
			// new pointer
			Gen_seq_pt* c_next = new Gen_seq_pt;

			c_next->Find_loc(hw_fragment, g_place);

			// checking if list is empty
			if (g_begin == NULL)
			{
				g_begin = c_next;
			}
			// if nodes are present in list
			else
			{
				Gen_seq_pt* curr = g_begin;
				while (curr->next != NULL)
				{
					curr = curr->next;
				}

				curr->next = c_next;
			}
		}
};

// class that reads the fasta file onto the Hash Table
class FASTAreadset_HT
{

	// ------------- Declaring variables to use --------------

	// pointer for the hash hash_table
	Chain_collision* hash_table;

	// setting varibale for fragment_len
	int len;

	public:

		// ------------- Constructor and Destructor Function -------------

		// default constructor
		FASTAreadset_HT()
		{
			// getting fragment_len of hash hash_table
			this->len = 10000000;
			// getting hash hash_table
			this->hash_table = new Chain_collision[len];
		}

		// ------------- Other Helper Function Definitions --------------

		// pointer getting the fragment 
		Gen_seq_pt* Get_f(char* hw_fragment)
		{	
			// setting value to 0 		
			unsigned int val = 0;
		    int i = 0;

		    // looping through all genome fragments
		    while(i<11)
		    {	
		    	int re = (int(hw_fragment[i]) * pow(3, i));
		    	val = val + (unsigned int)(re) % len;
		    	i++;
		    }

		    // returning the value
		    unsigned int Res = val%len;

			return this->hash_table[Res].Get_place(hw_fragment);

		}

		// inserting fragment in hash_table
		void Put_f(char* hw_fragment, int g_place)
		{
			// setting value to 0 		
			unsigned int val = 0;
		    int i = 0;

		    // looping through all genome fragments
		    while(i<11)
		    {	
		    	int re = (int(hw_fragment[i]) * pow(3, i));
		    	val = val + (unsigned int)(re) % len;
		    	i++;
		    }

		    // returning the value
		    unsigned int Res = val%len;

			return this->hash_table[Res].Chain_next(hw_fragment, g_place);
		}
};
#endif
