#include <iostream>
#include <vector>
#include <array>

using namespace std;

class MyVector
{
private:
    struct Contact
    {
        string name;
        string phone;
    };
    
    Contact * list;
    
    int max_size;
    int list_size;
    
public:
    MyVector()
    {
        max_size = 10;
        list_size = -1;
        list = new Contact[10];
    };
    
    ~MyVector()
    {
        delete [] list;  //frees the dynamically allocated memory
    };

    
    /* Takes a name and phone number and adds a new contact to the list if there is enough room. If there is not enough room, then creates a new contacts array that is twice as big, copies the existing contacts array to the new larger array and deletes the original contacts raray then adds the new contact to the end of the new larger array */
    
    void push_back( string n, string p)
    {
        list_size++;
            if(list_size < max_size)
            {
                list[list_size].name = n;
                list[list_size].phone = p;
            }
            else
            {
                Contact * newlist = new Contact[max_size*2];    //create new contact array twice as big
                for(int i = 0; i < (max_size); i++)             //copy existing contact s array to the new array.
                    newlist[i] = list[i];
                delete [] list;                                 //delete the old list
                list = newlist;
                max_size = max_size*2;
                list[list_size].name = n;                       //add new contact to end of new array.
                list[list_size].phone = p;
            }
    }

/*  This method searches the Contacts array for a matching name or phone number.  If found, the matching Contact is "removed" from the list by overwriting the matching element with the last element of the list and then decrementing the list size. Given that all names and numbers are unique. */
    
    void remove( string n, string p)
    {
        for(int i = 0; i <= list_size; i++)
        {
            if(list[i].phone == p || list[i].name == n)         //check if matching phone number or matching name or both
            {
                list[i].name = list[list_size].name;            //swap matching contact with last contact
                list[i].phone = list[list_size].phone;
                list_size--;
            }
        }
    }
    
    /* Takes a contact name as input and searches the Contacts array for a match.  If it finds one, it returns the phone number for that contact as a string, otherwise, it returns the string  "NOT FOUND". */
    
    string get(string name)
    {
        string phone = "NOT FOUND";
        for(int i = 0; i<= list_size; i++)                      //linear search of list for contact name
        {
            if(list[i].name == name)
            {
                phone = list[i].phone;
            }
        }
        return phone;
    }
    
    /* This public method clears the Contacts list by setting list_size back to -1. */
    
    void clear()
    {
        list_size = -1;
    }
};

/* The main() function is responsible for interacting with the user. Provides the user menu and accepts inputs for specific actions.*/

int main()
{
    char user_input;
    MyVector V;
    string inputname;
    string inputphone;
    
    do
    {
        cout << endl;
        cout << "(A)dd Contact" << endl;
        cout << "(C)lear Contact" << endl;
        cout << "(F)ind Contact" << endl;
        cout << "(Q)uit" << endl;
        cout << "(R)emove Contact" << endl;
        cout << endl;
        cout << "[ACFQR]: ";
        cin >> user_input;
        
        switch(toupper(user_input))
        {
            case 'A':
                cout << "Enter Name: ";
                cin >> inputname;
                cout << "Enter Phone: ";
                cin >> inputphone;
                cout << endl;
                V.push_back(inputname, inputphone);
                break;
            case 'C':
                V.clear();
                break;
            case 'F':
                cout << "Enter Name: ";
                cin >> inputname;
                cout << V.get(inputname) << endl << endl;
                break;
            case 'R':
                cout << "Enter the name or number of a contact to remove: ";
                cin >> inputname;
                V.remove(inputname, inputname);
                break;
        }
    } while (toupper(user_input) != 'Q');
    return 0;
}
