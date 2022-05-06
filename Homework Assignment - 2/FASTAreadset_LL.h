//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 2
//@sb3292
//*******************
//*******************

#ifndef FASTAreadset_LL_H 
#define FASTAreadset_LL_H

#include <iostream>
#include <fstream>
#include <time.h> 
#include <math.h>
using namespace std;


// FASTAreadset_LL class as described in HW Problem
class FASTAreadset_LL
{
	private:

		//-------------- structure that holds Fasta data ---------
		struct Node
		{
			struct Node* next; // pointer pointing to next node
		};

		// ------------- Declaring variables to use --------------

		// size of the Fasta_readset file
		const int Fasta_Size = 36000000; 

		// reading the file stream
		ifstream FASTA_file;

		//pointer head of LinkedList 
		Node* head;

		// pointer to head of LinkedList for Gen_seq
		Node* genHead;

		// FASTA_file path 
		char* FASTA_file_path;
		
		// no.of FASTA_read_line read
		int read_line;
		
		// pointer for sorted array
		char** Arr_sort;

	public:

		// ------------- Constructor and Destructor Function -------------

		// Default Constructor
		FASTAreadset_LL()
		{
			// initilizing values
			head = NULL;
			genHead = NULL;
		}

		//Custom constructor 
		FASTAreadset_LL(char* path)
		{
			// setting path variables
			FASTA_file_path = path;
			head = NULL;
			genHead = NULL;
		}

		// Destructor
		~FASTAreadset_LL()
		{
			DeleteAllocation();
		}

		// Overloaded Constructor
		void FASTA_read_file(int FASTA_read_line)
		{
			FASTA_read_file(FASTA_file_path, FASTA_read_line);
		}

		//Copy Constructor
		FASTAreadset_LL(const FASTAreadset_LL &obj)
		{
			cout << "deep copy started at:";
			TotalTime();
			
				head = NULL;
				genHead = NULL;
				
				Node* curr;
				int incr = 0;
				Node* temp = obj.head;

				while(temp != NULL)
				{
					 Node* new_node = new Node;

				 for(int i = 0; i < 50; i++)
				 {
					(new_node -> L)[i] = (temp -> L)[i];
				 }

				 (new_node -> L)[50] = '\0';
				 new_node -> next = NULL;
				 
				 if(incr == 0)
				 {
				 	head = new_node;
				 }
				 else
				 {
				 	curr -> next = new_node;
				 }

				 curr = new_node;
				 temp = temp -> next;   	
				 incr++;
			}
			
			incr = 0;
			temp = obj.genHead;
			while(temp != NULL)
			{
					 Node* new_node = new Node;

				 for(int i = 0; i < 50; i++)
				 {
				 	(new_node -> L)[i] = (temp -> L)[i];
				 }

				 (new_node -> L)[50] = '\0';
				 new_node -> next = NULL;
				 new_node -> next = NULL;
				 
				 if(incr == 0)
				 {
				 	genHead = new_node;
				 }
				 else
				 {
				 	curr -> next = new_node;
				 }

				 curr = new_node;
				 temp = temp -> next;   	
				 incr++;
			}
			
			cout << "deep copy completed at:";
			TotalTime();	
		}

		// ------------- Other Helper Function Definitions --------------

		// Initilaizing the array 
		void init()
		{
			cout << "Initialization started at: ";
			TotalTime();
			
			FASTA_read_file(Fasta_Size);
			
			cout << "Successfully initialized with " << Fasta_Size << " val at: ";
			TotalTime(); 
		}

		// Function to read FASTA_file
		void FASTA_read_file(char* FASTA_file_path, int FASTA_read_line)
		{
			read_line = FASTA_read_line;
			
			if(FASTA_file.is_open())
			{
				FASTA_file.close();
			}
			
			FASTA_file.open(FASTA_file_path);
			
			// for each fragment L
			string L; 

			// incrementing count
			int incr = 0; 

			// currrent node
			Node* curr = NULL; 
			
			while(FASTA_read_line > 0)
			{
				// reading header
				getline(FASTA_file, L);
				
				// reading the gen sequence
				getline(FASTA_file, L);
				
				Node* new_node = new Node;

			    for(int i = 0; i < 50; i++)
			    {
				 	(new_node -> L)[i] = (L.c_str())[i];
				}
			    (new_node -> L)[50] = '\0';

			    new_node -> next = NULL;
				
				if(curr != NULL){
					curr -> next = new_node;
				}
				
				curr = new_node;
				
				// if pointer is at first node 
				if(incr == 0)
				{
					head = new_node;
				}
				
				incr++;

				FASTA_read_line--;
				
			}
			
			FASTA_file.close();
		}

		// Searching gen_seq file segments
		void search_gen_seq()
		{
			cout << "Search for genomic sequences started at: ";
			TotalTime();
			
			Node* curr = genHead;

			// initilializing count and total value to 0
			int incr = 0;
			int total = 0;

			// if next nodes are present in Linked List
			while(curr != NULL)
			{
				incr++;
				int index = BinarySearch(curr -> L);
				if(index > -1)
					total++;
				curr = curr -> next;
			}
			
			cout << "Search ended at: ";
			TotalTime();
			
			cout << "Total " << total << " 50 mers sequences match were found" << "\n";
		}

		// Function to read Gen Seq Data
		void Gen_sequence_data(char* FASTA_file_path)
		{
			ifstream FASTA_file;
			FASTA_file.open(FASTA_file_path);
			
			cout << "Initializing genome data started at:";
			TotalTime();
			
			char temp[50]; // temporary genomic array
			char c = '\0'; // if we have reached end of line
			int incr = 0; // keeping track of count variables 
			int val = 0; // keeping track of values present in gen_file
			Node* curr;	// pointing to current node
			
			//skipping the first L
			while(c != '\n')
			{
				FASTA_file.get(c);	
			}
			
				while (FASTA_file.get(c))
				{
					if(c == 'A' || c == 'T' || c == 'G' || c == 'C' || c == 'N')
					{
						temp[incr] = c;
						incr++;
						if(incr == 50)
						{
							incr = 49;
							val++;
							
							Node* new_node = new Node;
							for(int i = 0; i < 50; i++)
							{
			    				(new_node -> L)[i] = temp[i];
							}
			    		(new_node -> L)[50] = '\0';

			    		new_node -> next = NULL;
			    		
			    		if(val == 1)
			    		{
			    			genHead = new_node;
						}
						else
						{
							curr -> next = new_node;
						}
						curr = new_node;
					}
					if(genHead != NULL)
					{
						for(int i = 1; i < 50; i++)
						{
							temp[i - 1] = temp[i];
						}
					}
				}  
			}         
			FASTA_file.close();
			
			cout << "Successfully initialized with " << val << " val of 50 mers at:";
			TotalTime();
		}

		//Function to search the homework sequences
		void Gen_seq_searches()
		{
			// keeping track of the location where the gen_seq was found
			int index;

			// storing sequences in character arrays
			char sequence1[] = "CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT";
			char sequence2[] = "GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC";
			char sequence3[] = "CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC";
			char sequence4[] = "CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA";
			char sequence5[] = "ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN";
			
			cout << "BinarySearch for sequence 1: " << sequence1 << endl;
			index = BinarySearch(sequence1);
			if(index > -1)
				cout << "Sequence found at location: " << index + 1 << " in dataset" << endl;
			else
				cout << "Sequence not found in dataset!" << endl;
			
			cout << "BinarySearch for sequence 2: " << sequence1 <<  endl;
			index = BinarySearch(sequence2);
			if(index > -1)
				cout << "Sequence found at location: " << index + 1 << " in dataset" << endl;
			else
				cout << "Sequence not found in dataset!" << endl;
				
			cout << "BinarySearch for sequence 3: " << sequence1 <<  endl;
			index = BinarySearch(sequence3);
			if(index > -1)
				cout << "Sequence found at location: " << index + 1 << " in sorted dataset" << endl;
			else
				cout << "Sequence not found in dataset!" << endl;
				
			cout << "BinarySearch for sequence 4: " << sequence1 << endl;
			index = BinarySearch(sequence4);
			if(index > -1)
				cout << "Sequence found at location: " << index + 1 << " in sorted dataset" << endl;
			else
				cout << "Sequence not found in dataset!" << endl;
				
			cout << "BinarySearch for sequence 5: " << sequence1 <<  endl;
			index = BinarySearch(sequence5);
			if(index > -1)
				cout << "Sequence found at location: " << index + 1 << " in sorted dataset" << endl;
			else
				cout << "Sequence not found in dataset!" << endl;
		}

		// Function for Binary Search
		int BinarySearch(char new_node[])
		{
			int start = 0; 
			int end = read_line - 1;
			int middle = (start + end) / 2; // middle element

			// until we reach the end we iterate
			while(start < end)
			{

				if(Arr_sort[middle] > new_node )
				{
					end = middle - 1;
				}

				else if(Arr_sort[middle] < new_node) 
				{
					start = middle + 1;
				}

				else
				{
					return middle;
				}
			}
			
			// if element not found then return -1
			return -1;
		}

		// Function for sorting the genomic sequence
		void Gen_seq_sort()
		{
			cout << "Sorting started at: ";
			TotalTime();
						
		    Arr_sort = new char*[read_line];
			
			int index = 0;
			Node* curr = head;

			while(curr != NULL)
			{
				Arr_sort[index] = curr -> L;
				index++;
				curr = curr -> next;
			}
			
			// applying quick sort to speed up the searching process
			QuickSort(Arr_sort, 0, read_line - 1);
			
			cout << "Sorted the dataset at: ";
			TotalTime();
		}

		// Function for Sorting the dataset
		void QuickSort(char* v[], int left, int right)
		{
			int last;
			int M = (left + right)/2; // middle element

			if(left >= right)
			{
				return;
			}

			swop(v, left, M);
			last = left;
			
			for(int i = left + 1; i <= right; i++)
			{
				if(v[i] < v[left])
				{
					swop(v, ++last, i);
				}
			}
			swop(v, left, last);

			// a recursive quicksort function
			QuickSort(v, left, last - 1);
			QuickSort(v, last + 1, right);
		}

		// Function for swapping 
		void swop(char *v[], int i, int j)
		{
			char* temp;
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;	
		}

		// to calculate the total time taken for program execution (i/e-- PART A/B)
		void TotalTime()
		{
			time_t rawtime;
			time(&rawtime);
			tm *time = localtime(&rawtime);
			
			cout << time->tm_hour << ":";
			cout << time->tm_min << ":";
			cout << time->tm_sec << "\n";
		}
		
};
#endif
