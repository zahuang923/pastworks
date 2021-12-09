//Assignment 7 lab
//Doubly Linked List class with struct that holds integer and string
//and with append, insert, remove, find, and clear methods

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DoublyLinkedList
{
private:
    struct Node
    {
        int number;
        string word;
        Node *next, *prev;
    };
    Node *head, *tail;
    
public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }
    
    ~DoublyLinkedList()
    {
        if(head == nullptr)
            return;
        Node * p = head;
        Node* q;
        do
        {
            q = p;
            p = p->next;
            delete q;
        }while(p != tail);
        head = nullptr;
        tail = nullptr;
    }
    
    void append(int num, string word)
    {
        Node*p;
        Node * n = new Node;
        n->number = num;
        n->word  = word;
        n->next = nullptr;
        n->prev = nullptr;
        
        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = n;
            n->prev = p;
            tail = n;
        }
    }
    //assume ascending order sorted data
    void insert(int num, string word)
    {
        Node *p, *q;
        Node *n = new Node;
        n->number = num;
        n->word = word;
        n->next = nullptr;
        n->prev = nullptr;
            
        if(head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            p = head;
            q = nullptr;
            while(p!=nullptr && num > p->number )
            {
                q = p;
                p = p->next;
            }
            if (q == nullptr)
                head = n;
            else
                q->next = n;
            
            if (p == nullptr)
                tail = n;
            else
                p->prev = n;
            
            n->prev = q;
            n->next = p;
        }
    }
        
    void remove(int key)
    {
        Node*p = head;
        Node*q = nullptr;
        
        while(p != nullptr && p->number != key)
        {
            q = p;
            p = p->next;
        }
        if (p == nullptr)
            return;
        
        if (q == nullptr)
            head = p->next;
        else
            q->next = p->next;
        
        if(p->next == nullptr)
            tail = q;
        else
            p->next->prev = q;
        
        delete p;
    }
    
    bool find(int key)
    {
        Node *p = tail;
        while(p != nullptr)
        {
            if (p->number == key)
                return true;
            p = p->prev;
        }
        return false;
    }
    
    void clear()
    {
        Node *p;
        while(tail != nullptr)
        {
            p = tail;
            tail = p->prev;
            delete p;
        }
        head = nullptr;
    }
};


int main()
{
    DoublyLinkedList Dlist;
    
    Dlist.append(0, "abc");
    Dlist.append(1, "def");
    Dlist.append(2, "ghi");
    Dlist.append(3, "jkl");
    
    Dlist.clear();
    
    return 0;
}
