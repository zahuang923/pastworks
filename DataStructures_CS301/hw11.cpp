//  assignment11
//unsorted array-based list implementation of priority queue

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

void enqueue(int list[], int max, int size, int a)
{
    if(max >= size)
        cout << "queue overflow" << endl;
    else
    {
        max++;
        list[max] = a;
    }
}

void dequeue(int list[], int max, int size)
{
    int high;
    high = list[0];
    int i = 1;
    while (i < size)
    {
        if (list[i] > high)
            high = list[i];
        i = i+1;
    }
    
    i = high;
    while (i < size)
    {
        list[i] = list[i+1];
        i = i+1;
    }
    size = size -1;
}




int main()
{
    int MyQueue[4];
    int size = 4;
    int max = -1;
    
    enqueue(MyQueue, max, size, 5);
    enqueue(MyQueue, max, size, 8);
    enqueue(MyQueue, max, size, 3);
    enqueue(MyQueue, max, size, 6);
    
    dequeue(MyQueue, max, size);
    
    return 0;
}
