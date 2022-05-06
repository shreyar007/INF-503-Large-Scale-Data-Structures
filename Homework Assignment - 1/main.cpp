//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 1
//@sb3292
//*******************
//*******************

#include "FASTA_readset.h"

using namespace std;

int main(int c, char ** argv)
{

	// checking if the correct # of arguments are entered
	if (c != 3)
	{
		cout << "Required number of Command Line Inputs Not Supplied. Run the Program Again." << endl;
	}

	// A char array holding the file path details
	FASTA_readset **ptr = new FASTA_readset*[14];

	for(int i = 0; i < 14; i++)
	{
		// stores the data in the Fasta Dataset
		ptr[i] = new FASTA_readset(argv[2], i+1);
	}

	// iterating through the loop based on the choice entered
	string problem_choice(argv[1]);

	if(problem_choice.compare("A") == 0)
	{

		// ------------------------------- Solve Problem A & Show Results ----------------------------------------------------------------------

		// Getting the First timestamp:
	   	time_t start = time(nullptr);

		for(int i = 0; i < 14; i++)
		{
			ptr[i]->Compute_All_Stats();
		}


        // Getting ending timestamp

		time_t end = time(nullptr);

	   	time_t duration = end-start;

	   	cout<<"Total time taken to execute Part A is = "<<duration<<endl;
	   	cout << endl;

	}
	else if(problem_choice.compare("B") == 0)
	{

		// ------------------------------- Solve Problem B & Show Results ----------------------------------------------------------------------

		// Getting the First timestamp:
	   	time_t start = time(nullptr);

	   	// performing linear search on datsets
	   	int ans = ptr[1]->Linear_search(ptr[0]);

	   	cout << endl << endl;
		cout << "The sequence of fragments in dataset 1 which are also in dataset 2 are: " << ans << endl;
		cout << endl;
		// Getting ending timestamp

		time_t end = time(nullptr);

	   	time_t duration = end-start;

	   	cout<<"Total time taken for searching = "<<duration<<endl;
	   	cout << endl;
	} 

	else if(problem_choice.compare("C") == 0)
	{
	
		// ------------------------------- Solve Problem C & Show Results ----------------------------------------------------------------------

		// Getting starting timestamp
        time_t start = time(nullptr);

		// sort using Bubble Sort 
		ptr[1]->Bubble_sort();

		// performing binary search
		int ans = ptr[1]->Binary_search(ptr[0]);

		cout << endl << endl;
		cout << "The sequence fragments in dataset 1 are also in dataset 2 after performing Bubble Sort is: " << ans << endl;
		cout << endl;

		// Getting ending timestamp
        time_t end = time(nullptr);   

        time_t duration = end-start;

        cout<<"\nTime (in seconds) Required to Sort the Read Sequences Alphabetically = "<<duration<<endl;
        cout << endl;
	} 

	else
	{

		cout<<"Wrong Problem Choice. Try Again."<<endl;
	}
	return 0;
}
