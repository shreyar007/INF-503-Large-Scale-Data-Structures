//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 5
//@sb3292
//*******************
//*******************

#include "Prefix_Trie.h"
#include <cstring>

// Main function that solves the HW problems    
int main(int c,char** argv)
{

    // taking in command line arguments and iterating
   if((c<4) || (c>5))
   {
       cout<<"--- Wrong no. of command line inputs. Try Again!! ---"<<endl;
   }

   else
   {        

        // taking input from command line
        string ch;
        string no_seq;
        string fp_cov;
        fp_cov.assign(argv[1]);  
        ch.assign(argv[2]);
        no_seq.assign(argv[3]);
        char* fp; 
        int s_len = fp_cov.length();
        fp = new char[s_len++];
        strcpy(fp,fp_cov.c_str());
        char* arr_36mer;
        int gen_len = no_seq.length();
        arr_36mer = new char[gen_len++];
        strcpy(arr_36mer,no_seq.c_str());
        int no_seq_int = atoi(arr_36mer);

        // if HW choice is 1A
        if(ch.compare("A")==0)
        {
            int find=0;
            int catches=0;
            Prefix_Trie p_t;
            p_t.sars_cov_f(fp,s_len);
            // generating random 36-mers (with no error)
            p_t.no_error_36mers(no_seq_int);
            p_t.search_36mer(find,catches);
            unsigned long int pt_len = p_t.trie_len();

            cout<<"\nNo. of Nodes in Prefix Trie: "<<pt_len<<endl;
            cout<<"No. of 36mers Searched: "<<find<<endl;
            cout<<"No. of 36mers Found: "<<catches<<endl;         
        }

        // if HW choice is 1B
        else if(ch.compare("B")==0)
        {
            int find=0;
            int catches=0;
            Prefix_Trie p_t;
            p_t.sars_cov_f(fp,s_len);
            // generating random 36-mers (with 5% error)
            p_t.error_36mers(no_seq_int);
            p_t.search_36mer(find,catches);
            unsigned long int pt_len = p_t.trie_len();

            cout<<"\nNo. of Nodes in Prefix Trie: "<<pt_len<<endl;
            cout<<"No. of 36mers Searched: "<<find<<endl;
            cout<<"No. of 36mers Found: "<<catches<<endl;            
        }  

        // if wrong HW choice is put    
        else
        {
            cout<<"--- Try Again with a valid option!! ---"<<endl;
        }
   }
    return 0;
}

