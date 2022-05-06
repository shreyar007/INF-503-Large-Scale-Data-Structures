//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 2
//@sb3292
//*******************
//*******************

#include "FASTAreadset_LL.h"

// Main function that solves the HW problems
int main(int c, char* argv[]) 
{
	// taking in command line arguments and iterating

	if((c<3) || (c>4))
    {
        cout<<"--- Wrong no. of command line inputs. Try Again!! ---"<<endl;        
    }

	char* choice = argv[3]; // argument 3 in command line 

	char* Genomic_Seq_File = argv[2]; // argument 2 in command line

	char* FASTA_f = argv[1]; // argument 1 in command line
	
	FASTAreadset_LL fr(FASTA_f);
	
	// if HW choice is A
	if(choice[0] == 'A')
	{
		// Initilaizing the array 
		fr.init();

		// Function for sorting
		fr.Gen_seq_sort();

		//Function to search the homework sequences
		fr.Gen_seq_searches();
	}

	// if HW choice is B
	else if(choice[0] == 'B')
	{
		// Initilaizing the array 
		fr.init();

		// Function for sorting
		fr.Gen_seq_sort();

		// Function to read Gen Seq Data
		fr.Gen_sequence_data(Genomic_Seq_File);

		// Searching gen_seq file segments
		fr.search_gen_seq();
	}

	// if wrong HW choice is put
	else
	{
		cout << "--- Try Again with a valid option!! ---" << endl;
	}
	return 0;
}
