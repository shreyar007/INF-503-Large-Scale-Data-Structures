//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 4
//@sb3292
//*******************
//*******************

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "Hash_Table.h"

using namespace std;

// structure defining the nodes
struct Gen_Place
{
	// ------------- Declaring structure variables to use --------------

	// gettin the next node
	Gen_Place* next;
	// variable that stores the word_loc
	int g_place;

	// ------------- Constructor and Destructor Function -------------

	// default constructor
	Gen_Place()
	{
		this->g_place = -1;
		this->next = NULL;
	}
};

// class defining the node points
class Gen_list
{
	public:

		// ------------- Declaring variables to use --------------
		
		// varibale holding the fragment_len
		int fragment_len;
		// pointer pointing to the start 
		Gen_Place* fr_start;
		// pointer pointing to the end
		Gen_Place* fr_end;

		// ------------- Constructor and Destructor Function -------------

		// default constructor
		Gen_list()
		{
			this->fr_start = NULL;
			this->fr_end = NULL;
			this->fragment_len = 0;
		}

		// ------------- Other Helper Function Definitions --------------

		// function to return nodes
		int Gen_retrive_ele()
		{
			Gen_Place ret;

			// checking if empty or not
			if (this->fr_start == NULL)
			{
				return -1;
			}

			// getting a temporary pointer
			Gen_Place* fr_var = this->fr_start;

			this->fr_start = this->fr_start->next;

			ret.g_place = fr_var->g_place;

			// deleting temporary allocation
			delete fr_var;

			// decrementing fragment_len value
			this->fragment_len--;

			return ret.g_place;	
		}

		// function to set nodes
		void Gen_insert_ele(int gen_var_loc)
		{
			// pointer pointing to a new node
			Gen_Place* newNode = new Gen_Place;
			// getting word_loc of the node
			newNode->g_place = gen_var_loc;
			// setting the neighboring node to null
			newNode->next = NULL;

			// checking if empty or not
			if (this->fr_start == NULL)
			{
				this->fr_start = newNode;
				this->fr_end = this->fr_start;
			}
			else
			{
		        this->fr_end->next = newNode;
		        this->fr_end = this->fr_end->next;
			}

			// returning the fragment_len
			this->fragment_len++;
		}
};

// class that facilitates seed-based searching
class Blast_DB
{
	public:

		// ------------- Declaring variables to use --------------

		// setting match score
		int match = 2;
		// setting mismatch penalty
		int mismatch = -1;
		// setting gap peanlty
		int gap = -1;

		// for mapping
		int map[50+1][50+1];
		// character pointer that stores the gen blast_file
		char* gen_file_contents;
		// pointer to the hash table
		FASTAreadset_HT* hash_table;
		// fragment_len of gen blast_file
		int gen_file_size;

		// ------------- Constructor and Destructor Function -------------

		// destructor
		~Blast_DB()
		{
			// clearing out contents in hash table
			hash_table->~FASTAreadset_HT();
			// deleting table
			delete hash_table;
			// deleting gen blast_file
			this->gen_file_size = 0;
			delete [] this->gen_file_contents;
		}

		// default constructor
		Blast_DB()
		{
			// setting table of hash table
			this->hash_table = new FASTAreadset_HT;
			// initilizing the fragment_len
			this->gen_file_size = 0;
			// initilazation of gen blast_file
			this->gen_file_contents = NULL;
		}

		// ------------- Other Helper Function Definitions --------------

		void Without_error_rate(int no_of_fragments, bool show)
		{
			// variable holding loc of the searched fragmnent
			int word_loc=0;
			int size = 0;
			// pointer to fasta fragmnets
			char* fasta_word = new char[50];

			int m = 0;
			while (m<50)
			{
				fasta_word[m] = ' ';
				m++;
			}

			int n = 0;
			while (n<no_of_fragments)
			{
				word_loc = rand()%(gen_file_size-50);
				int k = 0;
				while (k<50)
				{
					fasta_word[k] = gen_file_contents[word_loc + k];
					k++;
				}

				size = size + Blast_best_hit(fasta_word, show);
				n++;
			}

			cout << "The no.of fragments found is: " << size << endl;
		}

		void With_error_rate(int no_of_fragments, bool show)
		{
			// variable that holds the size
			int size = 0;
			// array contaning the sequence
			char seq[] = "ATGC";
			// pointer pointing to fasta array
			char* fasta_word = new char[50];
			// variable holding loc of the array		
			int word_loc=0;			

			int i = 0;
			while(i<50)
			{
				fasta_word[i] = ' ';
				i++;
			}

			int m = 0;
			while (m<no_of_fragments)
			{
				word_loc = rand()%(gen_file_size-50);

				int k = 0;
				while (k<50)
				{
					if (rand()%100<5)
						fasta_word[k] = seq[(rand()%100)%4];
					else
						fasta_word[k] = gen_file_contents[word_loc + k];
				}

				size = size + Blast_best_hit(fasta_word, show);
				m++;
			}

			cout << "The no.of fragments found is: " << size << endl;
		}

		void With_fasta(int no_of_fragments, string inp, bool show)
		{
			// variable that holds the size		
			int size = 0;
			// array contaning the sequence
			char seq[] = "ATGC";	
			// variable for fasta variable		
			int f_var=0;
			string f = " ";	
			// pointer pointing to fasta array	
			char* fasta_word = new char[50];

			// reading file 
			fstream blast_file;
		    blast_file.open(inp, ios::in);

			int i = 0;
			while(i<50)
			{
				fasta_word[i] = ' ';
				i++;
			}

			while (blast_file.peek() != EOF)
			{

		        getline(blast_file, f, '\n');

				if (f[0] == '=' )
					break;

				if (f[0] != '>')
				{
					int k = 0;
					while (k<50)
					{
						fasta_word[k] = f[k];
						k++;
					}
					
					size = size + Blast_best_hit(fasta_word, show);
				}
				
				f_var++;

				if (f_var == no_of_fragments)
				{
					break;
				}
				
			}

			cout << "The no.of perfect hits found is: " << size << endl;
		}

		// getting fragments into hash table
		void Set_hash_table()
		{
			int j=0;
			// pointer pointing to gen seq fragments 
			char* gen_word = new char[11];		

			int m=0;
			while (m<11)
			{
				gen_word[m] = ' ';
				m++;
			}

			// putting gen seq fragments into hash table
			int n=0;
			while (n < gen_file_size)
			{
				j=0;
				while (j<11)
				{
					gen_word[j] = gen_file_contents[n+j];
					j++;
				}
				hash_table->Put_f(gen_word, n);	
				n++;	
			}
		}

		// seed searching done using Needleman Wunsch Algorithm
		int Needleman_Wunsch_Algorithm(char* s1, char* s2, bool show)
		{	
			// setting sequence length
			char Seq1[50];
			char Seq2[50];
			char Show[50];
			// setting variables to use
			int var_1=0;
			int var_2=0;
			int var_3=0;
			
			// mapping the variables
			memset(map, -(50+1), sizeof(map));	

			int i = 0;
			while (i<51)
			{
				map[i][0] = map[0][i] = i * gap;
				i++;
			}

			for (int m = 1; m < 51; m++)
			{

				for (int n = 1; n < 51; n++)
				{
					
					var_1 = (map[m-1][n]+gap);

					if (s1[m-1] == s2[n-1])
						var_2 = (map[m-1][n-1]+match);
					else
						var_2 = (map[m-1][n-1]+mismatch);

					var_3 = (map[m][n-1]+gap);

					if(var_1 > var_2 && var_1 > var_3)
					{
					    map[m][n] = var_1;
					}
					else if (var_2 > var_3)
					{
					    map[m][n] = var_2;
					}
					else
					{
					    map[m][n] = var_3;
					}

					Seq1[m-1] = s1[m-1];

					if (map[m][n] == var_1)
					{
						Show[n-1] = ' ';
						Seq2[n-1] = '-';
					}
					if (map[m][n] == var_2)
					{
						if (s1[m-1] == s2[n-1])
							Show[n-1] = '|';
						else
							Show[n-1] = 'X';
						
						Seq2[n-1] = s2[n-1];
					}
					
				}
			}

			if (show == true)
			{
				int a = 0;
				while (a < 50)
				{
					cout << Seq1[a];
					a++;
				}	
				cout << endl;
				
				int b = 0;
				while (b < 50)
				{
					cout << Show[b];
					b++;
				}
				cout << endl;

				int c = 0;
				while (c < 50)
				{
					cout << Seq2[c];
					c++;
				}
				cout << endl;
			}
			return map[51-1][51-1];
		}

		// takin in the blast_file input
		void Blast_file_inp(string inp)
		{
			// creating a string variable
			string str;
			char g_char = ' ';

			// reading input file
			ifstream in(inp);
			getline(in, str, '\n');

			while (in.peek() != EOF)
			{
				in >> g_char;
				gen_file_size++;
			}

			gen_file_size--;
			in.close();

			// reading gen blast_file data
			gen_file_contents = new char[gen_file_size];
			in.open(inp);

			getline(in, str, '\n');
			gen_file_size=-1;

			while (in.peek() != EOF)
			{		
				in >> g_char;
				gen_file_size++;
				gen_file_contents[gen_file_size] = g_char;
			}
			in.close();
		}

		// functions that gets the score of best hit
		int Blast_best_hit(char* no_fragments, bool show)
		{
			// list of contents
			Gen_list li;
			// variable that holds the word_loc of the pointer
			int g_place=0;
			// char pointer to the gen blast_file fragments
			char* gen_word = new char[11];
			// char array for the fasta fragmnets
			char* fasta_word = new char[50];
			int ans = -1;

			int i = 0;
			while (i < 50)
			{
				if (i<11)
				{
					gen_word[i] = ' ';
				}
				fasta_word[i] = ' ';
				i++;
			}

			for (int i = 0; i < 40; i++)
			{
				
				for (int j = 0; j < 11; j++)
					gen_word[j] = no_fragments[i+j];
				
				Gen_seq_pt* point = hash_table->Get_f(gen_word);

				while (point)
				{

					li.Gen_insert_ele(point->Gen_seq_place);
					point = point->next;
				}
			}

			int m = 0;
			while (m<40)
			{
				int n = 0;
				while (n<11)
				{
					gen_word[n] = no_fragments[m+n];
					n++;
				}
				Gen_seq_pt* point = hash_table->Get_f(gen_word);

				while (point)
				{
					li.Gen_insert_ele(point->Gen_seq_place);
					point = point->next;
				}
				m++;
			}

			// if gap isn't present
			while (g_place != ans)
			{
				int k = 0;
				g_place = li.Gen_retrive_ele();

				while (k<50)
				{
					fasta_word[k] = gen_file_contents[g_place+k];
					k++;
				}
				if (Needleman_Wunsch_Algorithm(no_fragments, fasta_word, show) == 100)
				{
					return true;
				}
			}
			return 0;
		}			
};
