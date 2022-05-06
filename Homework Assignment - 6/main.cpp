//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 6
//@sb3292
//*******************
//*******************

#include "Suffix_Tree.h"

// Main function that solves the HW problems    
int main(int c,char** argv)
{

    // taking in command line arguments and iterating
   if((c<3) || (c>4))
   {
       cout<<"--- Wrong no. of command line inputs. Try Again!! ---"<<endl;
   }

   else
   {     
        // getting input from command line
        string ch;
        string fp_cov;
        string no_seq;
        fp_cov.assign(argv[1]);
        ch.assign(argv[2]);  
        no_seq.assign(argv[3]);
        char* fp; 
        fp = new char[fp_cov.length()+1];
        strcpy(fp,fp_cov.c_str());
        int s_len = fp_cov.length();
        char* arr_36mer;
        arr_36mer = new char[no_seq.length()+1];
        strcpy(arr_36mer,no_seq.c_str());
        int no_seq_int = atoi(arr_36mer); 
    
        // if HW choice is A
        if(ch.compare("A")==0)
        {

           Suffix_Tree tree;
           tree.sars_cov_f(fp,s_len);
           time_t prgm_st = time(nullptr);
           unsigned int catches = tree.search_36mer(no_seq_int);
           time_t prgm_nd = time(nullptr);
           time_t total_t = prgm_nd - prgm_st;
           unsigned long int trie_size = tree.tree_len();

           cout<<"\nNo. of nodes in Suffix Tree is: "<<trie_size<<endl;
           cout<<"\nNo. of 36mers found is: "<<catches<<endl;
           cout<<"\nTotal time for execution is: "<<total_t<<endl;

        }    

        // if wrong HW choice is put 
        else
        {
            cout<<"--- Try Again with a valid option!! ---"<<endl;
        }
   }
    return 0;
}
