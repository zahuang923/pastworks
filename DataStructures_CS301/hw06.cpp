#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class ERHeap
{
private:
    struct Node
    {
        int priority;
        string name;
        string description;
    };
    
    Node* heap;
    int capacity;
    int bottom;
    
public:
    ERHeap(int s) // constructor
    {
        heap = new Node[s];
        capacity = s;
        bottom = -1;
    }
    
    ~ERHeap() //destructor
    {
        delete [] heap;
    }
    
    void enqueue(string name, string desc, int pri)
    {
        int i, j;
        if (bottom+1 < capacity)
        {
            i = 0;
            while(i < bottom+1 && pri < heap[i].priority)
            {
                i = i+1;
            }
            j = bottom+1;
            while(j>i)
            {
                heap[j] = heap[j-1];
                j = j-1;
            }
            heap[i].name = name;
            heap[i].description = desc;
            heap[i].priority = pri;
            bottom = bottom + 1;
        }
        ReHeapUp();
    }
    
    void dequeue(string &name)
    {
        int j;
        if (bottom < 0)
        {
            cout << "no patients" <<endl;
            return;
        }
        
        name = heap[0].name;
        for(j = 0; j < bottom; j++)
        {
            heap[j] = heap[j+1];
        }
        bottom = bottom -1;
        ReHeapDown();
    }
  
    void ReHeapUp()
    {
        int p;
        
        int i = bottom;
        while(i != 0)
        {
            p = (i-1)/2;
            if(heap[i].priority > heap[p].priority)
                swap(heap[p], heap[i]);
            i = p;
        }
    }
    
    void ReHeapDown()
    {
        int p = 0;
        int biggestc;
        while(p<bottom)
        {
            int leftc = 2*p+1;
            int rightc = 2*p+2;
            if(leftc <= bottom)
            {
                if(leftc == bottom)
                    biggestc = leftc;
                else
                    if(heap[leftc].priority > heap[rightc].priority)
                        biggestc = leftc;
                    else
                        biggestc = rightc;
            }
            else
                return;
            if(heap[p].priority < heap[biggestc].priority)
            {
                swap(heap[p], heap[biggestc]);
                p = biggestc;
            }
            else
                return;
        }
    }
};

int main() {

    ERHeap ER = ERHeap(50);
    char UserInput;
    string Pname;
    string Pdesc;
    int priority;
    
    do
    {
        cout << endl << endl;
        cout << "(A)dd Patient" << endl;
        cout << "(N)ext Patient" << endl;
        cout << "(Q)uit" << endl;
        cout << ":] ";
        cin >> UserInput;
        
        switch (toupper(UserInput)) {
            case 'A':
                cout << "Enter patient's name: ";
                cin >> Pname;
                cin.ignore();
                cout << "Enter complaint: ";
                getline(cin, Pdesc);
                cout << "Enter priority: ";
                cin >> priority;
                ER.enqueue(Pname, Pdesc, priority);
                break;
            case 'N':
                Pname = "";
                ER.dequeue(Pname);
                cout << "Next Patient: " << Pname;
                break;
            case 'Q':
                break;
        }
    }while(toupper(UserInput) != 'Q');
    
    return 0;
}
