#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#ifndef LIST
    #define LIST
    #include "List.hpp"
#endif

/* This is source code for implementation of doubly linked list, 
    utilize the templated class with some member functions */


template <class elemType>
class DlinkList: public List <elemType>
{
    private:
        struct Node
        {
            elemType data;
            Node *prior, *next;
            // init function
            Node(const elemType &x, Node *p=NULL, Node *n=NULL)
                {data = x; next = n; prior = p;}
            Node(void):prior(NULL),next(NULL){}
            ~Node(){}
        }
        Node *head, *tail;
        int currentLength; // essential in dlinklist
        Node *move(int i) const // general operation
        {
            Node *p;
            int j = 0;
            if( 0 <= i < currentLength/2)
            {
                Node *p = head->next;
                for(j=0;j<i;j++)
                    p = p->next;
            }
            else if(currentLength/2 <= i < currentLength)
            {
                Node *p = tail->prior;
                for(j=currentLength-1;j>i;j++)
                    p = p->prior;
            }
            else
            {
                throw OutOfBound();
                return;
            }
            return p;
        }
    public: 
        DlinkList(void);
        ~DlinkList(){clear(); delete head; delete tail;} // delete both head and tail
        void clear(void);
        int length(void) const {return currentLength;}
        void insert(int i, const elemType &x);
        void remove(int i);
        int index(const elemType &x) const;
        elemType visit(int i) const;
        void traverse(void) const;
};

/* Specific member functions of DlinkList*/

template <class elemType>
DlinkList <elemType>:: DlinkList(void)
{
    head = new Node(); // allocate an empty head-linkNode and let head point to it
    currentLength = 0; //counting initialization, head is not included
}

template <class elemType>
int DlinkList <elemType>:: length(void) const
{
    return currentLength;
}

/* for link list, the index also starts from "0" as the 1st linkNode */
template <class elemType>
int DlinkList <elemType>:: index(const elemType &x) const
{
    int count = 0;
    Node *p = head->next; // now p is at 1st Node(if not NULL)
    while(p)
    {
        if(p->data == x) return count;
        p = p->next;
        count++;
    }
    return -1;
}

template <class elemType>
elemType DlinkList <elemType>:: visit(int i) const
{
    Node *p = move(i);
    return p->data;
}

template <class elemType>
void DlinkList <elemType>:: insert(int i, const elemType &x)
{
    if(i> currentLength || i< 0)// check it
    {
        throw OutOfBound();
        return;
    }
    Node *p = move(i);

    Node *tmp = new Node();
    tmp->data = x;
    tmp->next = p->next;
    p->next = tmp;
    //update
    currentLength++;
}

template <class elemType>
void DlinkList <elemType>:: remove(int i)
{
    if(i>= currentLength || i< 0)// check it
    {
        throw OutOfBound();
        return;
    }

    Node *p = move(i);

    Node *tmp = new Node();
    tmp = (p->next)->next;
    delete p->next;
    p->next = tmp;
    //update
    currentLength--;

}

template <class elemType>
void DlinkList <elemType>:: clear(void)
{
    Node *p = head->next;
    Node *tmp;
    head->next = NULL;
    while(p)
    {
        tmp = p;
        p = p->next;
        delete tmp;
    }

}

template <class elemType>
void DlinkList <elemType>:: traverse(void) const
{
    Node *p = head->next;
    cout << "[";
    while(p)
    {
        cout << p->data<< " ";
        p = p->next;
    }
    cout << "]" << endl;
}

