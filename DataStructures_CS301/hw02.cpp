#include <iostream>
#include <vector>
#include <array>

using namespace std;

//Class MyVector uses a linked listed of Contacts.
//Each Contact is a struct that will store a name and a phone number.
class MyVector
{
private:
  struct Contact
    {
        string name;
        string phone;
        Contact *next;
    };

    Contact * head;
    Contact * tail;
    int list_size;
    
public:
    MyVector() //constructor
    {
        head = NULL;
        tail = NULL;
        list_size = 0;
    };
    
    ~MyVector() //destructor
    {
        Contact *p1;
        
        while(head != NULL)
        {
            p1 = head;
            head = p1->next;
            delete p1;
        }
    }
 
    //push_back accepts a name and phone number and adds it to the end of the list.
    void push_back(string name, string phone)
    {
        Contact *temp = new Contact;
        temp->name = name;
        temp->phone= phone;
        temp->next = NULL;
        
        if (tail == NULL)
        {
            head = temp;
        }
        else
        {
            tail->next = temp;
        }
        tail = temp;
        list_size++;
    }
    
    //remove searches the contact list for a matching name or phone number
    //and deletes it from the contact list and decrements the list size.
    void remove(string name, string phone)
    {
        Contact * p1 = head;
        Contact * p2 = NULL;
        
        while(p1 != NULL )
        {
            if (p1->name == name || p1->phone == phone)
            {
                break;
            }
            else
            {
                p2 = p1;
                p1 = p1->next;
            }
        }
        if (p1 == NULL)
            return;
        else if (p2 == NULL)
            head = p1->next;
        else
            p2->next = p1->next;
        delete p1;
        list_size--;
    }
    
    //get() searches the contact list for the the user specified name and returns the phone number of the contact if found, otherwise returns "NOT FOUND"
    string get(string name)
    {
        Contact * p1 = head;
        
        while(p1 != NULL && (p1->name != name))
        {
            p1 = p1->next;
        }
        if (p1 == NULL)
            return "NOT FOUND";
        else
            return p1->phone;
    }
    
    
    //clears the Contacts list by freeing all memory used by the list
    //and resetting head and tail to null and sets list size back to zero.
    void clear()
    {
        Contact *p1;
        
        while(head != NULL)
        {
            p1 = head;
            head = p1->next;
            delete p1;
        }
        head = NULL;
        tail = NULL;
        list_size = 0;
    }
    
    //returns the number of contacts in the list as an integer
    int size()
    {
        return list_size;
    };
};


//The main() function is responsible for interacting with the user.
//Provides the user menu and accepts input for specific actions.
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
