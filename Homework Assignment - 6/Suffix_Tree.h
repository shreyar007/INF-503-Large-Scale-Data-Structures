//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 6
//@sb3292
//*******************
//*******************

#ifndef SUFFIX_TREE_H_INCLUDED
#define SUFFIX_TREE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>

using namespace std;

// structure holding values for characters [A-T-G-C]
struct Node
{
    int offset;
    int length;
    Node* A = NULL;
    Node* T = NULL;
    Node* G = NULL;
    Node* C = NULL;
    Node* DS = NULL;
};

// Struct holding each element values of queue 
struct Q_nodes
{
    Node* ele = NULL;
    Q_nodes* next_ele = NULL;
};

// class that describes the queue structure
class Q_gen
{
    public:

        // ------------- Declaring variables to use --------------

        // size of queue
        unsigned long int q_len;
        
        // start of queue
        Q_nodes* start;

        // end of queue
        Q_nodes* end;

        // ------------- Constructor and Destructor Function -------------

        // destructor
        ~Q_gen()
        {
            // de-allocating queue
            q_len = 0;    
            Q_nodes* temp;

            while(start!=NULL)
            {
                temp = start;        
                start = start->next_ele;
                temp->ele = NULL; 
                temp->next_ele = NULL; 
                delete temp;
            }
            end = NULL;
        }

        // default constructor
        Q_gen()
        {
            // initializing queue
            q_len = 0;
            start = NULL;
            end = NULL;
        }


        // ------------- Other Helper Function Definitions --------------

        // removing ele from queue
        void deq(Node*& dq)
        {
            if(!Q_empty())
            {
                    dq = start->ele;
                    Q_nodes* temp = start;
                    start = start->next_ele;
                    if(start == NULL)
                    {
                        end = NULL;
                    }
                    temp->ele = NULL;
                    temp->next_ele = NULL;
                    delete temp;
                    q_len--;
            }
        }

        // adds element to queue
        void enq(Node* t_node)
        {
            if(start == NULL && end == NULL)
            {
                Q_nodes* var_n;
                var_n = new Q_nodes;
                var_n->ele = t_node;
                var_n->next_ele = NULL;
                start = var_n;
                end = var_n;
                q_len++;
            }
            else
            {
                Q_nodes* var_n;
                var_n = new Q_nodes;
                var_n->ele = t_node;
                var_n->next_ele = NULL;
                end->next_ele = var_n;
                q_len++;
            }
        }

        // checks if queue is empty
        bool Q_empty()
        {
            return ((start == NULL) && (end == NULL));
        }
};

// class describing the suffix tree
class Suffix_Tree
{

    public:

        // ------------- Declaring variables to use --------------

        // no. of header char in genome file
        unsigned int gen_header = 38;
        unsigned int buff_len = 256;
        // len of 36-mers
        unsigned int len_36mers = 36;
        // Root var_n of the Suffix Tree
        Node* rt;
        // char array holding the SARS-COV2 genome
        char* sars_cov;
        // len of genome
        unsigned long int len_sars_cov;

        

        // ------------- Constructor and Destructor Function -------------

        // destructor
        ~Suffix_Tree()
        {
            // De-allocation
            if(sars_cov != NULL)
            {
                delete[] sars_cov;
                len_sars_cov = 0;
            }
            if(rt != NULL)
            {
                Q_gen no_q;
                no_q.enq(rt);
                Node* nn;
                while( ! no_q.Q_empty() )
                {
                    no_q.deq(nn);

                    if(nn!=NULL)
                    {
                        if(nn->A != NULL)
                        {
                            no_q.enq(nn->A);
                        }
                        if(nn->C != NULL)
                        {
                            no_q.enq(nn->C);
                        }
                        if(nn->G != NULL)
                        {
                            no_q.enq(nn->G);
                        }
                        if(nn->T != NULL)
                        {
                            no_q.enq(nn->T);
                        }
                        if(nn->DS != NULL)
                        {
                            no_q.enq(nn->DS);
                        }
                    }
                    delete nn;
                    nn = NULL;
                }
                rt = NULL;
            }
        }

        // constructor 
        Suffix_Tree()
        {
            // initializing values
            rt = NULL;
            sars_cov = NULL;
            len_sars_cov = 0;
        }
        
        
        // custom constructor
        Suffix_Tree(const char* st_seq,unsigned int st_seq_len)
        {
            rt = NULL;
            len_sars_cov = st_seq_len;
            sars_cov = new char[len_sars_cov];
            unsigned int ind = 0;
            while (ind < len_sars_cov)
            {
                sars_cov[ind] = st_seq[ind];
                ind++;
            }
            sub_seq(sars_cov,len_sars_cov); 
        }


        // ------------- Other Helper Function Definitions --------------


        // adding element into suffix tree
        void Push_ST(const char* t_seq,unsigned int gen_seq_len)
        {
            if(rt != NULL) 
            {
                unsigned int ind = 0;
                Node* curr_n = rt;
                char curr_ind;
                while (ind < gen_seq_len)
                {
                    curr_ind = t_seq[ind];
                    if(curr_ind == 'A')
                    {
                            if(curr_n->A == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->A = nn;
                                curr_n = curr_n->A;
                            } 
                            else
                            {
                                curr_n = curr_n->A;
                            }                  

                    }
                    else if(curr_ind == 'T')
                    {
                            if(curr_n->T == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->T = nn;
                                curr_n = curr_n->T;
                            }
                            else
                            {
                                curr_n = curr_n->T;
                            }
                    }
                    else if(curr_ind == 'G')
                    {
                            if(curr_n->G == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->G = nn;
                                curr_n = curr_n->G;
                            }
                            else
                            {
                                curr_n = curr_n->G;
                            }
                    }
                    else if(curr_ind == 'C')
                    {
                            if(curr_n->C == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->C = nn;
                                curr_n = curr_n->C;
                            }
                            else
                            {
                                curr_n = curr_n->C;
                            }
                    }
                    else if(curr_ind == '$')
                    {
                            if(curr_n->DS == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->DS = nn;
                            }
                    } 
                    ind++;               
                } 
                curr_n = NULL;           
            }
            else 
            {
                char curr_ind;
                Node* curr_n;
                curr_n = rt;
                unsigned int ind = 0;
                Node* var_n;
                var_n = new Node;
                rt = var_n;  
                while (ind < gen_seq_len)
                {
                    curr_ind = t_seq[ind];
                    if(curr_ind == 'A')
                    {
                            if(curr_n->A == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->A = nn;
                                curr_n = curr_n->A;
                            }
                            else
                            {
                                curr_n = curr_n->A;
                            }                   
                    }
                    else if(curr_ind == 'T')
                    {
                            if(curr_n->T == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->T = nn;
                                curr_n = curr_n->T;
                            }
                            else
                            {
                                curr_n = curr_n->T;
                            }
                    }
                    else if(curr_ind == 'G')
                    {
                            if(curr_n->G == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->G = nn;
                                curr_n = curr_n->G;
                            }
                            else
                            {
                                curr_n = curr_n->G;
                            }
                    }
                    else if(curr_ind == 'C')
                    {
                            if(curr_n->C == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->C = nn;
                                curr_n = curr_n->C;
                            }
                            else
                            {
                                curr_n = curr_n->C;
                            }
                    }
                    else if(curr_ind == '$')
                    {
                            if(curr_n->DS == NULL)
                            {
                                Node* nn;
                                nn = new Node;
                                curr_n->DS = nn;
                            }
                    }  
                    ind++;              
                } 
                curr_n = NULL;
            }
        }

        // len of the suffix tree
        unsigned long int cnt_gen_node(const Node* var_n)
        {
            if(var_n != NULL)
            {
                return 1 + cnt_gen_node(var_n->A) + cnt_gen_node(var_n->C) + cnt_gen_node(var_n->G) + cnt_gen_node(var_n->T) + cnt_gen_node(var_n->DS);
            }
            
            else
            {
                return 0;
            }
            
        }

        // searching for 36-mers
        unsigned int search_36mer(unsigned int num)
        {
            
            char* g;
            int c = 0;
            unsigned int n_gen = num;
            bool res;
            int ind;
            unsigned int catches = 0;
            while(c < n_gen)
            {
                ind = (unsigned int) rand() % len_sars_cov;
                if(ind+(len_36mers-1) < len_sars_cov)
                {
                    int i=0;
                    c++;
                    g = new char[len_36mers]; 
                    while (i< len_36mers)
                    {
                        g[i] = sars_cov[ind+i];
                        i++;
                    }
                    res = tree_seq_search(g,len_36mers);
                    if(res == true)
                    {
                        catches++;
                    }
                    delete[] g;
                    g = NULL;
                }
            } 
            return catches;   
        }

        // reads genome data
        void sars_cov_f(const char* fp,int len_fp)
        {
            unsigned long int seq_h = 0;
            unsigned long int seq_oh = 0;
            string s1;
            char* buff_1;
            buff_1 = new char[buff_len];
            ifstream ff;
            ff.open(fp);
            while(!ff.eof())
            {   
                cls_buff(buff_1);
                ff>>buff_1;
                s1.clear();
                s1.assign(buff_1);
                seq_h += (unsigned long int) s1.length();

            }
            ff.close();

            unsigned int t_s_len = 0;
            unsigned int arr_ind = 0;
            unsigned int init_arr = 0;
            seq_oh = seq_h - (unsigned long int)gen_header;        
            char initial_array[seq_h];
            sars_cov = new char[seq_oh];          
            len_sars_cov = seq_oh;

            ifstream ff2;
            ff2.open(fp);
            while((!ff2.eof()) && (init_arr < seq_h))
            {
                cls_buff(buff_1);
                ff2>>buff_1;
                s1.clear();
                s1.assign(buff_1);
                t_s_len = s1.length();

                for(unsigned int ind = 0; ind < t_s_len; ind++,init_arr++)
                {
                    initial_array[init_arr] = s1.at(ind);
                }

            }
            ff2.close();
            unsigned int ind = 0;
            while (ind < len_sars_cov)
            {
                sars_cov[ind] = initial_array[ind+gen_header];
                ind++;
            }
            sub_seq(sars_cov,len_sars_cov);
            delete[] buff_1;        
        }

        // clears any buffer array
        void cls_buff(char* &buff)
        {
            unsigned int i=0;
            while (i<buff_len)
            {
                buff[i] = '\0';
                i++;
            }
        }

        // searches found in suffix tree
        bool tree_seq_search(const char* st_seq, unsigned int st_seq_len)
        {
            char curr_ind;
            unsigned int ind = 0;
            Node* curr_n;
            curr_n = rt;
            bool is_found = false;
            while (ind < st_seq_len)
            {
                curr_ind = st_seq[ind];
                if(ind == st_seq_len-1) 
                {
                    if(curr_ind == 'A')
                    {
                        if(curr_n->A != NULL) 
                        {
                            is_found = true;
                        }  
                    }
                    else if(curr_ind == 'T')
                    {
                        if(curr_n->T != NULL) 
                        {
                            is_found = true;
                        }
                    }
                    else if(curr_ind == 'G')
                    {
                        if(curr_n->G != NULL) 
                        {
                            is_found = true;
                        }   
                    }
                    else if(curr_ind == 'C')
                    {
                        if(curr_n->C != NULL) 
                        {
                           is_found = true;
                        }
                    }
                }
                else
                {
                    if(curr_ind == 'A')
                    {
                        if(curr_n->A != NULL) 
                        {
                            curr_n = curr_n->A;
                        }
                        else 
                        {
                            break;
                        }
                    }
                    else if(curr_ind == 'T')
                    {
                        if(curr_n->T != NULL) 
                        {
                            curr_n = curr_n->T;
                        }
                        else
                        {
                            break;
                        }
                    } 
                    else if(curr_ind == 'G')
                    {
                        if(curr_n->G != NULL) 
                        {
                            curr_n = curr_n->G;
                        }
                        else 
                        {
                            break;
                        }
                    }
                    else if(curr_ind == 'C')
                    {
                        if(curr_n->C != NULL) 
                        {
                            curr_n = curr_n->C;
                        }
                        else
                        {
                            break;
                        }
                    }             
                }
                ind++;  
            } 
            curr_n = NULL;
            return is_found;
        }

        // adding element into suffix tree 
        void sub_seq(const char* st_seq, unsigned int st_seq_len)
        {
            unsigned int i = 0;
            unsigned int tsq_len;
            char* tsq;
            tsq = NULL;
            while (i < st_seq_len)
            {        
                unsigned int ind = 0;
                tsq_len = (st_seq_len - i)+1; 
                tsq = new char[tsq_len];
                while (ind < tsq_len)
                {
                    if(ind == tsq_len-1)
                    {
                        tsq[ind] = '$';
                    }

                    else
                    {
                        tsq[ind] = st_seq[i+ind];
                    }
                    ind++;
                }
                Push_ST(tsq,tsq_len);
                if(tsq != NULL)
                {
                    delete[] tsq;
                    tsq = NULL;
                    tsq_len = 0;
                }  
                i++;          
            } 
            tsq_len = 1;
            tsq = new char[tsq_len];
            tsq[0] = '$';
            Push_ST(tsq,tsq_len);
            delete[] tsq;
            tsq = NULL;
            tsq_len = 0;
        }

        // no. of nodes in suffix tree
        unsigned long int tree_len()
        {
            Node* temp;
            temp = rt;
            unsigned long int ts = cnt_gen_node(rt);
            temp = NULL;
            return ts;
        }

};
#endif