#include <iostream>
#include <array>
#include <vector>
#include <stdio.h>
#include <math.h>

class heap
{

//helper swap
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void ReHeapUp(int h[], int b)
{
    int c = b;
    int p;
    while (true)
    {
        if (c == 0)
            return;
        p = (c-1)/2;
        if (h[p] > h[c])
            return;
        else
        {
            swap(h[p], h[c]);
            c = p;
        }
    }
}

void Enqueue(int h[], int b, int v, int size)
{
        if (size != h.size())
        {
            b = b+1;
            h[b] = v;
            ReHeapUp(h, b);
        }
}
    
void ReHeapDown(int h[], int t, int b)
{
    int p = t;
    int bc;
    while (true)
    {
        int lc = 2*p+1;
        int rc = 2*p+2;
        if (lc > b)
        {
            return;
        }
        if (rc > b)
        {
            bc = lc;
        }
        else
        {
            if (h[rc] > h [lc])
                bc = rc;
            else
            {
                bc = lc;
            }
        }
        if (h[p] < h[bc])
        {
            swap(h[p], h[bc]);
        }
        else
            return;
        p = bc;
    }
}
    
};

