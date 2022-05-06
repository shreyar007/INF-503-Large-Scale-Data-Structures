//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 3
//@sb3292
//*******************
//*******************

#include "FASTA_HT.h"

// Main function that solves the HW problems		
int main(int c, char* argv[]) 
{
	// taking in command line arguments and iterating

	if((c<4) || (c>5))
    {
        cout<<"--- Wrong no. of command line inputs. Try Again!! ---"<<endl;        
    }

    char* choice = argv[4];	// argument 4 in command line
    char* Genomic_1mil_File  = argv[3]; // argument 3 in command line
    char* Genomic_Seq_File  = argv[2]; // argument 2 in command line
	char* Rand_Gen_Seq_File  = argv[1]; // argument 1 in command line
	
	// if HW choice is 1A
	if(choice[0] == 'A')
	{
		// Hash size
		FASTA_HashTable fh(10000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		// Finding Collisions
		fh.Collision_Occurence();
	}

	// if HW choice is 1B
	else if(choice[0] == 'B')
	{
		// Hash size
		FASTA_HashTable fh(100000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		// Finding Collisions
		fh.Collision_Occurence();
	}

	// if HW choice is 1C
	else if(choice[0] == 'C')
	{
		// Hash size
		FASTA_HashTable fh(1000000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		// Finding Collisions
		fh.Collision_Occurence();
	}

	// if HW choice is 1D
	else if(choice[0] == 'D')
	{
		// Hash size
		FASTA_HashTable fh(10000000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		// Finding Collisions
		fh.Collision_Occurence();
	}

	// if HW choice is 2A
	else if(choice[0] == 'E')
	{
		// Hash size
		FASTA_HashTable fh(10000000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		fh.Read_Gen_Data(Genomic_Seq_File);
	}

	// if HW choice is 2B
	else if(choice[0] == 'F')
	{
		// Hash size
		FASTA_HashTable fh(10000000);

		// to read only 1million chat from genomic data
		// char b[1000000] = "";
		// ifstream f(Genomic_Seq_File);

		// f.read(b, sizeof(b) - 1); // Read one less that sizeof(b) to ensure null
		// cout << b;

		// ofstream myfile;
		// myfile.open ("1milgen.txt");
		// myfile << b;
		// myfile.close();
		// return 0;
		
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_1mil_File);
		fh.Read_Gen_Data(Genomic_1mil_File);
	}

	// if HW choice is 2C
	else if(choice[0] == 'G')
	{
		// Hash size
		FASTA_HashTable fh(10000000);
		// Reading B. anthracis genome File
		fh.ReadFile(Rand_Gen_Seq_File);
		fh.Read_Gen_Data(Rand_Gen_Seq_File);
	}

	// if HW choice is 3A
	else if(choice[0] == 'H')
	{
		// Hash size
		FASTA_HashTable fh(10000000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		fh.Read_Gen_Data(Genomic_Seq_File);
	}

	// if HW choice is 3B
	else if(choice[0] == 'I')
	{
		// Hash size
		FASTA_HashTable fh(10000000);
		// Reading B. anthracis genome File
		fh.ReadFile(Genomic_Seq_File);
		fh.Read_Gen_Data(Genomic_Seq_File);
	}

	// if wrong HW choice is put
	else
	{
		cout << "--- Try Again with a valid option!! ---" << "\n";
	}

	return 0;
}
