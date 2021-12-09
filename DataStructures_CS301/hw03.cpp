#include <iostream>
#include <stack>
#include <array>
#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <cstring>

using namespace std;

//MyStack class uses a static array based implementation of stack ADT.
class MyStack
{
private:
    int max_size;
    int top;       //top holds the size of the array
    int * list;
    
public:
    MyStack() //constructor
    {
        max_size = 100;
        top = -1;
        list = new int[max_size];
    };
    
    ~MyStack() //destructor
    {
        delete [] list;
    }
    
    //clear() empties the stack by setting the list size variable, top, to -1.
    void clear()
    {
        top = -1;
    }
    
    //pop() removes and returns the top value on the stack if it is not empty.
    //throws an exception if the stack is empty when trying to pop.
    int pop()
    {
        int value;
        if (top >= 0)
        {
            value = list[top];
            top--;
            return value;
        }
        else // empty stack
            throw 10;
    }
    
    //push(int v) accepts an integer as only argument and pushes it onto the stack
    //if there is enough memory
    void push(int v)
    {
        top++;
        if (top < max_size)
        {
            list[top] = v;
        }
        else
        {
            int *newlist = new int[max_size*2];
            for(int i = 0; i < max_size; i++)
                newlist[i] = list[i];
            delete [] list;
            list = newlist;
            max_size = max_size*2;
            list[top] = v;
        }
    }
    
    //size() returns the size of the stack as an integer.
    int size()
    {
        return top+1;
    }
    
    //toString() returns a string representation of the stack.
    string toString()
    {
        int topcopy = top;
        ostringstream oss;
        oss <<"[";
        while(topcopy>=0)
        {
            if(topcopy != 0)
                oss << list[topcopy] << ", ";
            else
                oss << list[topcopy];
            topcopy--;
        }
        oss << "]";
        
        return oss.str();
    }
};


//calculator supports +,-,*,/,% operations. ? prints values of stack, ^ pops top element off stack
//! quits the calculator.
int main()
{
    char str [100]; //define a character array of size 100 to store user inputs
    MyStack stack;
    char *token; //define pointer variable token
    int n1, n2, result; //declare intermediate variables for stack operations
    
    cout << "My Calculator: ";
    
    while(cin >> str) //continuously read user input
    {
        token = strtok(str, " "); //tokenize the user input in string with space delimiter " "
        
        if(*token == '!')
            break;
        try {
                switch(*token)
                {
                    case '+':
                    {
                        n1 = stack.pop();
                        n2 = stack.pop();
                        result = n1+n2;
                        stack.push(result);
                        break;
                    }
                    case '-':
                    {
                        n1 = stack.pop();
                        n2 = stack.pop();
                        result = n1-n2;
                        stack.push(result);
                        break;
                    }
                    case '*':
                    {
                        n1 = stack.pop();
                        n2 = stack.pop();
                        result = n1*n2;
                        stack.push(result);
                        break;
                    }
                    case '/':
                    {
                        n1 = stack.pop();
                        n2 = stack.pop();
                        result = n1/n2;
                        stack.push(result);
                        break;
                    }
                    case '%':
                    {
                        n1 = stack.pop();
                        n2 = stack.pop();
                        result = n1%n2;
                        stack.push(result);
                        break;
                    }
                    case '?':
                    {
                        cout << stack.toString() << endl;
                        break;
                    }
                    case '^':
                    {
                        cout << stack.pop() << endl;
                        break;
                    }
                    default:
                    {
                        std::istringstream iss(token);
                        
                        iss >> result;
                        
                        if(iss.fail())
                            cout << "#Invalid input." << endl;
                        else
                            stack.push(result);
                        break;
                    }
                }
        }  catch (int e)
        {cout << "#Not enough arguments." << endl; }
    }
    return 0;
}
