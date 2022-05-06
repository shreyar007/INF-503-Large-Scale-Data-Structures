//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 1
//@sb3292
//*******************
//*******************

#include "FASTA_readset.h"

using namespace std;

// ******************************************************** Constructors & Destructor Definitions *******************************************************************

// ----------------------- DESTRUCTOR
FASTA_readset::~FASTA_readset()
{

	    //  ------------- RELEASE the KRAKEN(!!!) - the array holding the read seq data -----------------------------

		// Getting starting timestamp
	    time_t start = time(nullptr);

		delete [] all_genomic_sequence;

		// Getting ending timestamp
	    time_t end = time(nullptr);

	    time_t duration = end-start;

	    cout<<"\n\t\tTime (in seconds) Required to Release All Memory = "<<duration<<endl;

	    cout<<"\n\t\t All Dynamically Allocated Memories Have Been Released. Exiting Program Now."<<endl;

}

// ----------------------- CONSTRUCTOR
FASTA_readset::FASTA_readset()
{
		// Setting up initial values

		all_genomic_sequence = NULL; // initializing space to 0 

		num_of_data_sets = 0; // # of data sets
		
		total_read_size = 14; // setting initial size to 14
	
}
	
// Function to Read File
FASTA_readset::FASTA_readset(char file_path[], int name_length)
{

		// initilazing the array 
		num_of_data_sets = name_length;

		// ---------- Memory Allocation --------------

    	try
    	{

			// opening the file and reading the contents stored in it
			fstream fptr;
	    	fptr.open(file_path, ios::in);

			// initilazing dataset count
			const int len_dataset = 14;

			// initilazing the read count
			int dataset_read_count = 0;

			char *temp_read = new char[150];
			
			// setting the length of each read
			int dataset_read; 

			// file reading until EOF 
			while(fptr >> temp_read)
			{

				// find the length of header
				dataset_read = 0;
				
				// navigates until EOF
				int i=0;
				while (temp_read[i] != '\0')
				{
					dataset_read++;
					i++;
				}
				
				// getting the read count for the dataset
				if(int(temp_read[1]) == 82)
				{ 
					if (temp_read[dataset_read - (len_dataset*2) + (2* (num_of_data_sets - 1)) + 1] != 48)
						dataset_read_count++;
				}

			}

			// setting the array size to the read count that we extracted 
			total_read_size = dataset_read_count;

			// dynamically creating character array
			all_genomic_sequence = new char**[dataset_read_count];
			
			for(int i = 0; i < dataset_read_count; i++)
				all_genomic_sequence[i] = new char *[2];

			for(int i = 0; i < dataset_read_count; i++)
				all_genomic_sequence[i][0] = new char[50]; 

			for(int i = 0; i < dataset_read_count; i++)
				all_genomic_sequence[i][1] = new char; 

			int index = 0;

			// clearing file pointer
			fptr.clear();
			
			// pointing the pointer to BOF
			fptr.seekg(0, fptr.beg);    

			// navigating through each instance of the dataset
			while(fptr >> temp_read)
			{

				// performing same process as above
				dataset_read = 0;
		
				int i=0;
				while (temp_read[i] != '\0')
				{
					dataset_read++;
					i++;
				}

				if(int(temp_read[1]) == 82)
				{
					if (temp_read[dataset_read - (len_dataset*2) + (2* (num_of_data_sets - 1)) + 1] != 48)
					{

						char* seq_seg = new char[50];

						fptr >> seq_seg; 

						strcpy(all_genomic_sequence[index][0], seq_seg);

						*all_genomic_sequence[index][1] = temp_read[dataset_read - (len_dataset*2) + (2* (num_of_data_sets - 1)) + 1]; 
						
						index++;
			
					}
				}

			}
			
			// File reading done.
	        // Close the file stream.
	        if (fptr.is_open())
	        {
	            fptr.close();
	        }
	    }

	    catch(bad_alloc& exception)
	    {
	        cout<<"Dynamic Memory Allocation Failed Inside Overloaded Constructor."<<endl;
	        cout<<"\tDetials: "<<exception.what()<<endl;
	        exit(EXIT_FAILURE);
	    }

}



// ********************************************************** Remaining Member Function Definitions ****************************************************************

// Function to carry out Binary Search Operation
int FASTA_readset::Binary_search(FASTA_readset *ptr)
{

		// default value
		int data = 0;
		int find = 0;

		data = ptr->total_read_size;
		char *** sample_set = ptr->all_genomic_sequence;

		for(int i = 0; i < data; i++)
		{
				// setting one index to the begenning and one index to the end
				int left = 0, right = total_read_size - 1;

				// while left < right value we iterate through the loop
				while (left <= right)
				 {

					// finding the middle value
					int middle = (left + (right - left) )/ 2;
			
					// is mid == key ?
					if (all_genomic_sequence[middle][0] == sample_set[i][0])
						return atoi(all_genomic_sequence[middle][1]);
			
					// is mid < key ?
					else if (all_genomic_sequence[middle][0] < sample_set[i][0])
						left = middle + 1;
			
					// is mid > key ?
		        	if ((all_genomic_sequence[middle][0] > sample_set[i][0]))
		            	right = middle - 1;

		            else
		            	find+=0;
		   		}
				// cannot find element then return 0
				return 0;
		}

		// key found
		return find;
}

// Performing the Bubble Sort Operation
void FASTA_readset::Bubble_sort()
{
		// performing bubble sort for the dataset
		for(int i = 0; i < total_read_size; i++)
		{

			// // second inner loop
			for(int j = 0; j < total_read_size - 1; j++)
			{
				// comparing the two datasets 
				if(all_genomic_sequence[j][0] > all_genomic_sequence[j+1][0])
				{

					// to store temporary value 
					char* temp = new char[50];

					strcpy(temp, all_genomic_sequence[j][0]);
					strcpy(all_genomic_sequence[j][0], all_genomic_sequence[j+1][0]);
					strcpy(all_genomic_sequence[j+1][0], temp);
					temp = all_genomic_sequence[j][1];
					all_genomic_sequence[j][1] = all_genomic_sequence[j+1][1];
					all_genomic_sequence[j+1][1] = temp;

				}
			}
		}
}

// Function to print the A part of homework
void FASTA_readset::Compute_All_Stats()
{
		// printing out the stats
		cout << "The # of unique sequence fragments are in each of the 14 datasets are : " <<num_of_data_sets << ": " << total_read_size << endl;

		int copies = 0;

		for(int i = 0; i < total_read_size; i++)
			copies += *all_genomic_sequence[i][1] - 48;

		cout << "The total # of sequence fragments are in each dataset are: " << copies << endl << endl;

}
	
// Function to perform Linear Search on the given Dataset
int FASTA_readset::Linear_search(FASTA_readset *ptr)
{
		// default value
		int data=0;
		int find = 0;

		data = ptr->total_read_size;
		char *** sample_set = ptr->all_genomic_sequence;

		// iterating line by line 
		for(int i = 0; i < data; i++)
		{
			for(int j = 0; j < total_read_size; j++)
			{
				if(all_genomic_sequence[j][0] == sample_set[i][0])
					find += atoi(all_genomic_sequence[j][1]);
			}
		}
		// key found
		return find;		
}

