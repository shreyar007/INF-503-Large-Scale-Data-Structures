//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 1
//@sb3292
//*******************
//*******************

#ifndef FASTA_readset_H
#define FASTA_readset_H


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;


class FASTA_readset
{

    public:

            // Default Constructor 
            FASTA_readset();

            // Constructor with input filepath to read the entire file
            FASTA_readset(char file_path[], int name_length);

            // Default Destructor
            ~FASTA_readset();

            // Function for sorting the read seq data based on Bubble Sort
            void Bubble_sort();

            // Function that performs Binary Search Operation
            int Binary_search(FASTA_readset*);

            // Function that performs Linear Searching Operation
            int Linear_search(FASTA_readset*);

            // Function for computing and printing all stats
            void Compute_All_Stats();


    private:

            // A 2D [size: 36M-by-50] char array for storing all the seuquences read
            char*** all_genomic_sequence;

            // Number of data sets
            int num_of_data_sets;

            // Length of each sequence
            int total_read_size;

            // Assuming max length of the read header is 1024 Bytes (1KB)
            int max_read_header_length = 1024;

            // Path to the source data file
            char *file;

};
#endif

