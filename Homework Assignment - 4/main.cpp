//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 4
//@sb3292
//*******************
//*******************

#include <fstream>
#include <time.h>
#include <bits/stdc++.h>
#include <iostream>
#include "Blast_DB.h"

using namespace std;

// Main function that solves the HW problems
int main(int c, char* argv[])
{				
	// taking in command line arguments and iterating
	if((c<4) || (c>5))
    {
        cout<<"--- Wrong no. of command line inputs. Try Again!! ---"<<endl;        
    }

    // getting starting and ending timestamps
	time_t start, end;

	// setting value
	bool ch = true;
	// creating instance of Blast_DB class
	Blast_DB blast_func;
	// getting file input
	blast_func.Blast_file_inp(argv[1]);	
	// getting values from hash table			
	blast_func.Set_hash_table();
	// choice of HW problem
	char* choice = argv[3]; 
	// size of query to search
	int search_req = atoi(argv[4]);
	// char pointer holding array of gen seq fragments
	char* hw_fragment = new char[11];		
	// storing unique fragmnet
	char seq[] = "ATGC";
    // pointer pointing to file 
	char* read_file;						
	// variable holding the size of the file
	int file_place = 0;					
				

	// adding fragmnents as word size
	int k = 0;
	while (k<11)
	{
		hw_fragment[k] = ' ';
		k++;
	}
		
	// if HW choice is 1A
	if (choice[0] == 'A')
	{			
		// Getting starting timestamp
    	time_t start = time(nullptr);							

    	cout << "The alignment in accordance to Needleman-Wunsch is as follows... " << endl;

    	cout << endl;

    	// carrying out problem 1
		blast_func.Without_error_rate(search_req, ch);

		// Getting ending timestamp
        time_t end = time(nullptr);            
        time_t duration = end-start;

        cout << endl;
		cout << "Total time taken to search the fragments: " << duration << " seconds... " << endl;
	}

	// if HW choice is 1B
	else if (choice[0] == 'B')
	{				
    	// Getting starting timestamp
    	time_t start = time(nullptr);

		cout << "The alignment in accordance to Needleman-Wunsch is as follows... " << endl;

		cout << endl;

    	// carrying out problem 2
		blast_func.With_error_rate(search_req, ch);

		// Getting ending timestamp
        time_t end = time(nullptr);            
        time_t duration = end-start;

        cout << endl;
		cout << "Total time taken to search the fragments: " << duration << " seconds... " << endl;
	}

	// if HW choice is 1C
	else if (choice[0] == 'C')
	{				
    	// Getting starting timestamp
    	time_t start = time(nullptr);

    	cout << "The alignment in accordance to Needleman-Wunsch is as follows... " << endl;

    	cout << endl;

    	// carrying out problem 3
		blast_func.With_fasta(search_req, argv[2], ch);

		// Getting ending timestamp
        time_t end = time(nullptr);            
        time_t duration = end-start;

        cout << endl;
		cout << "Total time taken to search the fragments: " << duration << " seconds... " << endl;
	}

	// any other option provided
	else
	{			
		cout << "--- Try Again with a valid option!! ---" << "\n";
	}

	return 0;
}
