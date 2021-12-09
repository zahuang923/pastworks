//assignment 12
//sorted array-based list implementation - pseudocode translation
void enqueue(int list[], int max, int size, int p)
{
    int i = 0;
    while (i < size && p < list[i])
    {
        i = i +1;
    }
    int j = size;
    while (j > i)
    {
        list[j] = list[j-1];
        j = j-1;
    }
    list[i] = p;
    size = size+1;
}

void dequeue(int list[], int max, int size)
{
    int j = size;
    if (size > 0)
        j = size - 1;
    while(j>0)
    {
        list[j-1] = list[j];
        j = j-1;
    }
    size = size -1;
}

int main()
{
    return 0;
}
