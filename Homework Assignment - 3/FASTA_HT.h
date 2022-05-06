//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 3
//@sb3292
//*******************
//*******************

#ifndef FASTA_HashTable_H 
#define FASTA_HashTable_H

#include <iostream>
#include <fstream>
#include <time.h> 
#include <math.h>

using namespace std;

// a structure containing node info
struct Node
{
	// radix value for genome string
	unsigned int radix;
	
	// pointer pointing to the next node
	Node* next;
};

// class representing the Hash Functions 
class FASTA_HashTable
{
	// ------------- Declaring variables to use --------------
			
	public:

		// char array size for Genomic Seq
		const int Line_Size = 17;

		// stores the size of hash table
		int hash_table_size;
		
		// pointer to hash table
		Node** hash_table;
		
		// path of file
		char* file_path;
		
		// holds the no of lines present in file
		int no_of_lines;
		
		// keeping track of collisons occured
		int collisions;

		// for file methodologies
		ifstream file;

		// ------------- Constructor and Destructor Function -------------

		//Destructor
		~FASTA_HashTable()
		{
			Del_Alloc();
		}

		//Custom constructor for size initilization
		FASTA_HashTable(int size)
		{		
			collisions = 0;
			hash_table_size = size;	
			no_of_lines = 0;
			
			hash_table = new Node*[hash_table_size];
			int i = 0;
			while (i < hash_table_size)
			{
				hash_table[i] = NULL;
				i++;
			}
		}	

		// ------------- Other Helper Function Definitions --------------

		//Method for deleting memory used by arrays
		void Del_Alloc()
		{
			cout << "De-alloc of data initiated on: ";
			TotalTime();
			
			delete[] hash_table;
						
			cout << "De-alloc done successfully at: ";	
			TotalTime();		
		}

		// to display the no of collisions occured
		void Collision_Occurence()
		{
			cout << "The no.of collisions occured is: " << collisions << endl; 
		}
		
		//Method to find radix for a given string [A=0, C=1, G=2, T=3]
		unsigned int Rad_Cal(char string[])
		{
			// [A,C,G,T]
			int no_of_char = 4; 
			// number corresponding to [A=0, C=1, G=2, T=3]
			int char_equiv; 
			unsigned int val = 0; 
			char curr; 
			//index value
			int i = Line_Size - 1; 
			// the current postiton of char
			int pos = 0; 
			
			while(i > 0)
			{
				curr = string[i - 1];

				if (curr=='A')
				{
					char_equiv = 0;
				}
				else if (curr=='C')
				{
					char_equiv = 1;
				}
				else if (curr=='G')
				{
					char_equiv = 2;
				}
				else if (curr=='T')
				{
					char_equiv = 3;
				}

				val += pow(no_of_char, pos) * char_equiv;
				
				pos++;
				i--;
			}
			
			return val;
		}
		
		
		//Method to read genome data
		void Read_Gen_Data(char* file_path)
		{
			ifstream file;
			file.open(file_path);
			
			cout << "Gen-data Searching initiated on:";
			TotalTime();
			
			char temp[Line_Size - 1];
			char c = '\0';
			int count = 0;
			int rec = 0;
			int found = 0;
			unsigned int radix;
			
			//skipping the first line
			while(c != '\n')
			{
				file.get(c);	
			}
			
  			while (file.get(c))
  			{
  				if(c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'N')
  				{
  					temp[count] = c;
  					count++;
  					if(count == (Line_Size - 1))
  					{
  						count = (Line_Size - 2);
  						rec++;
  						radix = Rad_Cal(temp);
  						if(Hash_Key_Query(radix))
  						{
  							found++;	
						}
			    	}
					int i = 1;
					while (i < (Line_Size - 1))
					{
						temp[i - 1] = temp[i];
						i++;
					}
				}  
			}         
			file.close();
			
			cout << "So, " << rec << " is the total no.of 16 mers queried..." << "\n";
			cout << "So, " << found << " out of 16 mers are found in file..." << "\n";
			cout << "Searching was terminated on: ";
			TotalTime();
		}

		// function the read the contents of file line by line
		void ReadFile(char* file_path)
		{
			cout << "Process started on: ";
			TotalTime();
			
			if(file.is_open()){
				file.close();
			}
			
			file.open(file_path);
			
			// has the no. of lines to read
			string line;
			int count = 0;
			char currentLine[Line_Size]; //keeping track of current node
			bool isHeader = true;
			unsigned int radix;
			
			while(getline(file, line)){
				if(!isHeader){
					for(int k = 0; k < Line_Size - 1; k++){
		    		 	currentLine[k] = (line.c_str())[k];
					}
		    	    currentLine[Line_Size - 1] = '\0';
		    	    
		    	    radix = Rad_Cal(currentLine);
		    	    Hash_IP(radix);
		    	    
					no_of_lines++;
	    		}
	    		isHeader = !isHeader;
			}
			file.close();
			
			cout << "Process ended on: ";
			TotalTime();
		}
		
		// function describing the hash inputs
		void Hash_IP(unsigned int key)
		{
			// keeps track of index in the hash table
			int ind = key % hash_table_size;
			
			//keeping track of the nodes in the hash table
			Node* temp = hash_table[ind];
			Node* new_node = new Node;

			new_node -> radix = key;
			new_node -> next = NULL;
			
			if(temp == NULL)
			{
				hash_table[ind] = new_node;
			}
			else
			{
				collisions++;
				hash_table[ind] = new_node;
				new_node -> next = temp;
			}
		}
		
		// this function describes the hash key 
		bool Hash_Key_Query(unsigned int radix)
		{
			// keeps track of index in the hash table
			int ind = radix % hash_table_size;
			
			// a temporary pointer pointing at the index element
			Node* temp = hash_table[ind];
			
			if(temp == NULL)
			{
				return false;
			}
			else
			{
				while(temp -> next != NULL)
				{
					if(temp -> radix == radix)
					{
						return true;
					}
					temp = temp -> next;
				}
				return false;
			}
		}
		
		//Method to search genome sequences
		void Gen_Seq_Search()
		{
			
			cout << "Searching mechaism for Gen-Seq init on: ";
			TotalTime();
			
			int match_nos = 0;
			
			cout << "earching mechaism for Gen-Seq ended on: ";
			TotalTime();
			
			cout << "So, " << match_nos << " of 16 mers seq matches are found in file.." << "\n";
		}
		
		// total time taken for execution
		void TotalTime()
		{
			time_t time_taken;
  			time(&time_taken);
  			tm *curr_time = localtime(&time_taken);
			
			cout << curr_time->tm_hour << ":";
   			cout << curr_time->tm_min << ":";
   			cout << curr_time->tm_sec << "\n";
		}
};
#endif
