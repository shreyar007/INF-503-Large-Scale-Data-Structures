//*******************
//*******************
//              INF503-- HOMEWORK ASSIGNMENT 5
//@sb3292
//*******************
//*******************

#ifndef PREFIX_TRIE_H_INCLUDED
#define PREFIX_TRIE_H_INCLUDED

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <fstream>

using namespace std;

// structure holding values for characters [A-T-G-C]
struct Node
{
    Node* A = NULL;
    Node* T = NULL;
    Node* G = NULL;
    Node* C = NULL;
    bool gen_node_there = false;
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
                Q_nodes* node;
                node = new Q_nodes;
                node->ele = t_node;
                node->next_ele = NULL;
                start = node;
                end = node;
                q_len++;
            }
            else
            {
                Q_nodes* node;
                node = new Q_nodes;
                node->ele = t_node;
                node->next_ele = NULL;
                end->next_ele = node;
                q_len++;
            }
        }

        // checks if queue is empty
        bool Q_empty()
        {
            return ((start == NULL) && (end == NULL));
        }

};



// Struct holding each element values of stack
struct Stack_Node
{
    Node* ele = NULL;
    Stack_Node* next_ele = NULL;
};

// class that describes the stack structure
class S_gen
{
    public:

        // ------------- Declaring variables to use --------------

        // top of stack
        Stack_Node* top;

        // size of stack
        unsigned long int s_len;


        // ------------- Constructor and Destructor Function -------------

        // destructor
        ~S_gen()
        {
            // de-allocating stack
            s_len = 0;    
            Stack_Node* temp;
            while(top!=NULL)
            {
                temp = top;        
                top = top->next_ele;
                temp->ele = NULL; 
                temp->next_ele = NULL; 
                delete temp;
            }
        }

        // default constructor
        S_gen()
        {
            // initializing stack
	    s_len = 0;
            top = NULL;
        }

        // ------------- Other Helper Function Definitions --------------
        
        // remove element from top of stack
        void Pop(Node*& pop)
        {
            if(s_len != 0)
            {
                pop = top->ele;
                Stack_Node* temp = top;
                top = top->next_ele;
                temp->ele = NULL;
                temp->next_ele = NULL;
                delete temp;
                s_len--;
            }
        }

        // adds element to top of stack
        void Push(Node* t_node)
        {
            if(top == NULL)
            {
                Stack_Node* node;
                node = new Stack_Node;
                node->ele = t_node;
                node->next_ele = NULL;
                top = node;
                s_len++;
            }
            else
            {
                Stack_Node* node;
                node = new Stack_Node;
                node->ele = t_node;
                node->next_ele = top;
                top = node;
                s_len++;
            }
        }
};


// class describing the prefix trie
class Prefix_Trie
{

    public:

        // ------------- Declaring variables to use --------------

        // no. of header char in genome file
        unsigned int gen_header = 38;
        unsigned int buff_len = 256;
        // len of 36-mers
        unsigned int len_36mers = 36;
        // Root node of Prefix_Trie
        Node* rt; 
        // char array holding the SARS-COV2 genome
        char* sars_cov;
        // len of genome
        unsigned long int len_sars_cov;

        // ------------- Constructor and Destructor Function -------------
        
        // destructor
        ~Prefix_Trie()
        {
            // clearing space
            if(sars_cov != NULL)
            {
                delete[] sars_cov;
                len_sars_cov = 0;
            }

            // dealloacting nodes
            if(rt != NULL)
            {
                Q_gen no_q;
                no_q.enq(rt);
                Node* temp_n;
                while( ! no_q.Q_empty() )
                {
                    no_q.deq(temp_n);

                    if(temp_n!=NULL)
                    {
                        if(temp_n->A != NULL)
                        {
                            no_q.enq(temp_n->A);
                        }
                        if(temp_n->T != NULL)
                        {
                            no_q.enq(temp_n->T);
                        }
                        if(temp_n->G != NULL)
                        {
                            no_q.enq(temp_n->G);
                        }
                        if(temp_n->C != NULL)
                        {
                            no_q.enq(temp_n->C);
                        }
                    }

                    delete temp_n;
                    temp_n = NULL;
                } 
                rt = NULL;
            }
        }


        // overloaded constructor
        Prefix_Trie(const char** ch_qr,int no_of_qr,int len_qr)
        {
            // initializing values
            char* temp_query;
            unsigned int r = 0;
            rt = NULL; 
            len_sars_cov = 0;   
            sars_cov = NULL;

            while (r < no_of_qr)
            {
                unsigned int ind = 0;
                temp_query = new char[len_qr];
                while (ind < len_qr)
                {
                    temp_query[ind] = ch_qr[r][ind];
                    ind++;
                }

                // adding ele
                Push_PT(temp_query,len_qr);
                delete[] temp_query;
                r++;
            }

        }

        // constructor     
        Prefix_Trie()
        {
            // initializing values
            len_sars_cov = 0;
            rt = NULL;
            sars_cov = NULL;
        }

        // copy constructor
        Prefix_Trie(const Prefix_Trie& o_t)
        {
            // initializing values
            Node* temp;
            temp = o_t.rt;
            this->rt = NULL;
            this->sars_cov = NULL;
            this->len_sars_cov = 0;
            if(temp==NULL)
            {
                this->rt = NULL;
            }
            else
            {
                Node* node;
                node = new Node;
                this->rt = node;
                Q_gen o_tq;
                Q_gen n_tq;
                Node* temp1; 
                Node* temp2; 
                n_tq.enq(this->rt);
                o_tq.enq(temp);
                while ( !o_tq.Q_empty() )
                {
                    o_tq.deq(temp1);
                    n_tq.deq(temp2);
                    if(temp1!=NULL && temp2!= NULL)
                    {
                        if(temp1->A != NULL)
                        {
                            // inserting nodes using queue for A
                            Node* nnt;
                            nnt = new Node;
                            temp2->A = nnt;
                            o_tq.enq(temp1->A);
                            n_tq.enq(nnt);
                        }
                        if(temp1->T != NULL)
                        {
                            // inserting nodes using queue for T
                            Node* nnt;
                            nnt = new Node;
                            temp2->T = nnt;
                            o_tq.enq(temp1->T);
                            n_tq.enq(nnt);
                        }
                        if(temp1->G != NULL)
                        {
                            // inserting nodes using queue for G
                            Node* nnt;
                            nnt = new Node;
                            temp2->G = nnt;
                            o_tq.enq(temp1->G);
                            n_tq.enq(nnt);
                        }
                        if(temp1->C != NULL)
                        {
                            // inserting nodes using queue for C
                            Node* nnt;
                            nnt = new Node;
                            temp2->C = nnt;
                            o_tq.enq(temp1->C);
                            n_tq.enq(nnt);
                        }
                    }
                }

                if(o_t.sars_cov != NULL && o_t.len_sars_cov != 0)
                {
                    unsigned int ind = 0;
                    this->sars_cov = new char[o_t.len_sars_cov];
                    this->len_sars_cov = o_t.len_sars_cov;
                    while (ind < o_t.len_sars_cov)
                    {
                        this->sars_cov[ind] = o_t.sars_cov[ind];
                        ind++;
                    }
                }        
            }
        }


        // ------------- Other Helper Function Definitions --------------


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

        // checks if prefix trie is empty or not
        bool t_emp()
        {
            return (rt == NULL);
        }

        // searches sibling sub tries
        bool search_sib_ST(const char* gen_seq,int gen_seq_len,Node* gen_seq_node)
        {
            if(gen_seq_node != NULL)
            {
                unsigned int i=0;
                Node* curr_n;
                curr_n = gen_seq_node;
                while (i< gen_seq_len)
                {
                    if(gen_seq[i] == 'A')
                    {
                        if(curr_n->A != NULL)
                        {
                            curr_n = curr_n->A;
                        }
                        else 
                        {
                            curr_n = NULL;
                            gen_seq_node = NULL;
                            return false;
                        }
                    }
                    else if(gen_seq[i] == 'T')
                    {
                        if(curr_n->T != NULL)
                        {
                            curr_n = curr_n->T;
                        }
                        else 
                        {
                            curr_n = NULL;
                            gen_seq_node = NULL;
                            return false;
                        }
                    }
                    else if(gen_seq[i] == 'G')
                    {
                        if(curr_n->G != NULL)
                        {
                            curr_n = curr_n->G;
                        }
                        else 
                        {
                            curr_n = NULL;
                            gen_seq_node = NULL;
                            return false;
                        }
                    }
                    else if(gen_seq[i] == 'C')
                    {
                        if(curr_n->C != NULL)
                        {
                            curr_n = curr_n->C;
                        }
                        else 
                        {
                            curr_n = NULL;
                            gen_seq_node = NULL;
                            return false;
                        }
                    }
                    i++;
                } 
                return true;
            }
            else
            {
                return false;
            }
        }

        // adding element into prefix trie
        void Push_PT(const char* t_seq,unsigned int gen_seq_len)
        {   
            if (rt != NULL)
            {
                unsigned int i=0;
                Node* curr_n = rt;  
                while (i<gen_seq_len)
                {
                    if(t_seq[i] == 'A')
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

                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        }  
                    }
                    else if(t_seq[i] == 'T')
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
                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        }   
                    }
                    else if(t_seq[i] == 'G')
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
                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        }   
                    }
                    else if(t_seq[i] == 'C')
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
                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        }               
                    }
                    i++;
                } 
                curr_n = NULL;
            }
            else 
            {
                unsigned int i=0;
                Node* node;
                node = new Node;
                rt = node;
                Node* curr_n = rt;   
                while (i<gen_seq_len)
                {
                    if(t_seq[i] == 'A')
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

                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        } 
                    }
                    else if(t_seq[i] == 'T')
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
                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        }
                    }
                    else if(t_seq[i] == 'G')
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
                        if(i==(gen_seq_len-1)) 
                        {
                            curr_n->gen_node_there = true;
                        }
                    }
                    else if(t_seq[i] == 'C')
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

                        if(i==(gen_seq_len-1))
                        {
                            curr_n->gen_node_there = true;
                        }               
                    }
                    i++;
                } 
                curr_n = NULL;
            } 
        }

        // making prefix trie with 36-mers (with 5%)
        void error_36mers(unsigned int num_36mers)
        {
            int c = 0;
            char* r;
            char cb;
            int prob;
            int ind;
            int ch;
            while(c < num_36mers)
            {
                ind = (unsigned long int)rand()%len_sars_cov;
                if(ind+(len_36mers-1) < len_sars_cov)
                {
                    c++;
                    r = new char[len_36mers];
                    for(int i=0; i< len_36mers; i++)
                    {
                        cb = sars_cov[ind+i];
                        prob = rand() % 100;
                        if(prob>=0 && prob <= 4) // we mutate this char
                        {                    
                            if(cb == 'A')
                            {
                                ch = rand()%3;
                                if(ch == 0)
                                {
                                    cb = 'C';
                                }
                                else if(ch == 1)
                                {
                                    cb = 'G';
                                }
                                else
                                {
                                    cb = 'T';
                                }
                            }
                            else if(cb == 'T')
                            {
                                ch = rand()%3;
                                if(ch == 0)
                                {
                                    cb = 'A';
                                }
                                else if(ch == 1)
                                {
                                    cb = 'C';
                                }
                                else
                                {
                                    cb = 'G';
                                }
                            }
                            else if(cb == 'C')
                            {
                                ch = rand()%3;

                                if(ch == 0)
                                {
                                    cb = 'A';
                                }
                                else if(ch == 1)
                                {
                                    cb = 'G';
                                }
                                else
                                {
                                    cb = 'T';
                                }
                            }
                            else if(cb == 'G')
                            {
                                ch = rand()%3;

                                if(ch == 0)
                                {
                                    cb = 'A';
                                }
                                else if(ch == 1)
                                {
                                    cb = 'C';
                                }
                                else
                                {
                                    cb = 'T';
                                }
                            }
                        }
                        r[i] = cb;
                    }
                    Push_PT(r,len_36mers);
                    delete[] r;
                    r = NULL;
                }
            }
        }

        // searches for all 36-mers
        void search_36mer(int& no_mer,int& no_catch)
        {
            // Initializing
            unsigned int i=0;
            no_mer = 0;
            char* g;
            no_catch = 0;
            while (i+(len_36mers-1) < len_sars_cov)
            {
                unsigned int ind = 0;
                g = new char[len_36mers];
                while (ind < len_36mers)
                {
                    g[ind] = sars_cov[ind+i];
                    ind++;
                }
                bool fnd = false;
                trie_seq_search(g,len_36mers,1,fnd);
                no_mer++;
                if(fnd == true)
                {
                    no_catch++;
                }
                delete[] g;
                i++;
            }   
        }

        // reads genome data
        void sars_cov_f(const char* fp,int len_fp)
        {
            // initializing
            unsigned long int seq_h = 0;
            unsigned long int seq_oh = 0;
            string s1;
            ifstream ff;
            ff.open(fp);
            char* buff_1;
            buff_1 = new char[buff_len];
            while(!ff.eof())
            {   
                cls_buff(buff_1);
                ff>>buff_1;
                s1.clear();
                s1.assign(buff_1);
                seq_h = seq_h + (unsigned long int) s1.length();

            }
            ff.close();

            seq_oh = seq_h - (unsigned long int)gen_header;        
            unsigned int t_s_len = 0;
            char initial_array[seq_h];
            sars_cov = new char[seq_oh];
            unsigned int init_arr = 0;
            ifstream ff2;
            ff2.open(fp);
            unsigned int arr_ind = 0;
            len_sars_cov = seq_oh;
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
            delete[] buff_1;        
        }


        // len of the prefix trie
        unsigned long int cnt_gen_node(const Node* node)
        {
            if(node != NULL)
            {
                return 1 + cnt_gen_node(node->A) + cnt_gen_node(node->C) + cnt_gen_node(node->G) + cnt_gen_node(node->T);
            }
            
            else
            {
                return 0;
            }
        }

        // searching seq in prefix trie
        void trie_seq_search(const char* tt_seq,int tt_len,int tt_error,bool& fnd)
        {
            if(rt != NULL) 
            {
                // initializing
                unsigned int ind = 0;
                Node* curr_n;
                Node* temp_root;
                temp_root = rt;
                int fnd_len = 0;
                S_gen ns;
                ns.Push(temp_root);
                while (ind< tt_len)
                {
                    ns.Pop(curr_n);
                    if (ind < (tt_len-1)) 
                    {
                        if(tt_seq[ind] == 'A')
                        {
                            if(curr_n->A != NULL) 
                            {
                                ns.Push(curr_n->A);
                            }
                            else 
                            {
                                if(fnd_len>=tt_error) 
                                {
                                    fnd = false;
                                    break;
                                }
                                else
                                {
                                    fnd_len++;
                                    int rtt_len = tt_len - ind;
                                    char* rtt;
                                    rtt = new char[rtt_len];
                                    int i=0;
                                    while (i<rtt_len)
                                    {
                                        rtt[i] = tt_seq[i];
                                        i++;
                                    }
                                    bool sb_t = search_sib_ST(rtt,rtt_len,curr_n->T);
                                    bool sb_c = search_sib_ST(rtt,rtt_len,curr_n->C);
                                    bool sb_g = search_sib_ST(rtt,rtt_len,curr_n->G);
                                    if (sb_c || sb_g || sb_t) 
                                    {
                                        fnd = true;
                                        break;
                                    }
                                    else
                                    {
                                        fnd = false;
                                        break;
                                    }
                                    delete[] rtt;
                                }
                            }
                        } 
                        else if(tt_seq[ind] == 'T')
                        {
                            if(curr_n->T != NULL) 
                            {
                                ns.Push(curr_n->T);
                            }
                            else 
                            {
                                if(fnd_len>=tt_error) 
                                {
                                    fnd = false;
                                    break;
                                }
                                else 
                                {
                                    
                                    fnd_len++;
                                    int rtt_len = tt_len - ind;
                                    char* rtt;
                                    rtt = new char[rtt_len];
                                    int i=0;
                                    while (i<rtt_len)
                                    {
                                        rtt[i] = tt_seq[i];
                                        i++;
                                    }
                                    bool sb_c = search_sib_ST(rtt,rtt_len,curr_n->C);
                                    bool sb_a = search_sib_ST(rtt,rtt_len,curr_n->A);
                                    bool sb_g = search_sib_ST(rtt,rtt_len,curr_n->G);
                                    if (sb_a || sb_c || sb_g) 
                                    {
                                        fnd = true;
                                        break;
                                    }
                                    else
                                    {
                                        fnd = false;
                                        break;
                                    }
                                    delete[] rtt;
                                }
                            }
                        } 
                        else if(tt_seq[ind] == 'G')
                        {
                            if(curr_n->G != NULL) 
                            {
                                ns.Push(curr_n->G);
                            }
                            else
                            {
                                if(fnd_len>=tt_error) 
                                {
                                    fnd = false;
                                    break;
                                }
                                else 
                                {
                                    fnd_len++;
                                    int rtt_len = tt_len - ind;
                                    char* rtt;
                                    rtt = new char[rtt_len];
                                    
                                    int i=0;
                                    while (i<rtt_len)
                                    {
                                        rtt[i] = tt_seq[i];
                                        i++;
                                    }
                                    bool sb_c = search_sib_ST(rtt,rtt_len,curr_n->C);
                                    bool sb_a = search_sib_ST(rtt,rtt_len,curr_n->A);
                                    bool sb_t = search_sib_ST(rtt,rtt_len,curr_n->T);
                                    if (sb_a || sb_c || sb_t) 
                                    {
                                        fnd = true;
                                        break;
                                    }
                                    else
                                    {
                                        fnd = false;
                                        break;
                                    }
                                    delete[] rtt;
                                }
                            }
                        } 
                        else if(tt_seq[ind] == 'C')
                        {
                            if(curr_n->C != NULL) 
                            {
                                ns.Push(curr_n->C);
                            }
                            else 
                            {
                                if(fnd_len>=tt_error) 
                                {
                                    fnd = false;
                                    break;
                                }
                                else 
                                {
                                    fnd_len++;
                                    int rtt_len = tt_len - ind;
                                    char* rtt;
                                    rtt = new char[rtt_len];
                                    int i=0;
                                    while (i<rtt_len)
                                    {
                                        rtt[i] = tt_seq[i];
                                        i++;
                                    }
                                    bool sb_g = search_sib_ST(rtt,rtt_len,curr_n->G);
                                    bool sb_a = search_sib_ST(rtt,rtt_len,curr_n->A);
                                    bool sb_t = search_sib_ST(rtt,rtt_len,curr_n->T);
                                    if (sb_a || sb_g || sb_t) 
                                    {
                                        fnd = true;
                                        break;
                                    }
                                    else
                                    {
                                        fnd = false;
                                        break;
                                    }
                                    delete[] rtt;
                                }
                            }
                        } 
                    } 
                    
                    else 
                    {
                        if(tt_seq[ind] == 'A')
                        {
                            if(curr_n->A != NULL)
                            {
                                fnd = true;
                                break;
                            }
                            else 
                            {
                                if( curr_n->C!= NULL || curr_n->G != NULL || curr_n->T != NULL ) 
                                {
                                    fnd = true;
                                    break;
                                }
                                else
                                {
                                    fnd = false;
                                    break;
                                }
                            }
                        } 
                        else if(tt_seq[ind] == 'T')
                        {
                            if(curr_n->T != NULL)
                            {
                                fnd = true;
                                break;
                            }

                            else 
                            {
                                if( curr_n->A!= NULL || curr_n->C != NULL || curr_n->G != NULL ) 
                                {
                                    fnd = true;
                                    break;
                                }
                                else
                                {
                                    fnd = false;
                                    break;
                                }
                            }
                        }
                        else if(tt_seq[ind] == 'G')
                        {
                            if(curr_n->G != NULL)
                            {
                                fnd = true;
                                break;
                            }

                            else 
                            {
                                if( curr_n->A!= NULL || curr_n->C != NULL || curr_n->T != NULL ) 
                                {
                                    fnd = true;
                                    break;
                                }
                                else
                                {
                                    fnd = false;
                                    break;
                                }
                            }
                        } 
                        else if(tt_seq[ind] == 'C')
                        {
                            if(curr_n->C != NULL)
                            {
                                fnd = true;
                                break;
                            }

                            else 
                            {
                                if( curr_n->A!= NULL || curr_n->G != NULL || curr_n->T != NULL ) 
                                {
                                    fnd = true;
                                    break;
                                }
                                else
                                {
                                    fnd = false;
                                    break;
                                }
                            }
                        }  
                    } 
                    ind++;
                } 
            }
            else
            {
                fnd = false;
            }
        }


        // making prefix trie with 36-mers (non-mutated)
        void no_error_36mers(unsigned int num_36mers)
        {
            // initializing
            int ind;
            int c = 0;
            char* r;
            while(c < num_36mers)
            {
                ind = (unsigned long int)rand()%len_sars_cov;
                if(ind+(len_36mers-1) < len_sars_cov)
                {
                    c++;
                    r = new char[len_36mers];
                    for(int i=0; i< len_36mers; i++)
                    {
                        r[i] = sars_cov[ind+i];
                    }
                    Push_PT(r,len_36mers);
                    delete[] r;
                    r = NULL;
                }
            }   
        }

        // no. of nodes in prefix trie
        unsigned long int trie_len()
        {
            Node* temp;
            temp = rt;
            unsigned long int ts = cnt_gen_node(rt);
            temp = NULL;
            return ts;
        }

};
#endif