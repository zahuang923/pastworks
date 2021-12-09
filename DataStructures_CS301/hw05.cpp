#include<iostream>
#include<stdio.h>
#include<sstream>
#include<string>

using namespace std;

//AVL Tree class
class AVLTree
{
private:
    struct Node
    {
        int partnum;
        string description;
        int qty;
        double price;
        Node *left, *right;
    };
    Node *root;
    
    void append(Node*&, int num, int qty, double price, string desc);
    bool find(Node*, int) const;
    void clear(Node*&);
    int height(Node*);
    int difference(Node*);
    void rotateRight(Node*&);
    void rotateLeft(Node*&);
    void rotateLeftRight(Node*&);
    void rotateRightLeft(Node*&);
    void balance(Node*&);
    void remove(Node*&, int num);
    string getOutOfStock(Node*);
    string getPart(Node*, int num);
    
public:
    AVLTree();
    ~AVLTree();
    void clear();
    void append(int num, int qty, double price, string desc);
    void remove(int num);
    string getOutOfStock();
    string getPart(int num);
};

//balance called during append and remove, uses appropriate rotations to keep tree well-formed
void AVLTree::balance(Node*&r)
{
    if (difference(r) == -2)
    {
        if (difference(r->right) <= -1)
            rotateLeft(r);
        else
            rotateRightLeft(r);
    }
    else if (difference(r) == 2)
    {
        if (difference(r->left) >= 1)
            rotateRight(r);
        else
            rotateLeftRight(r);
    }
}


void AVLTree::rotateRightLeft(Node*&r)
{
    rotateRight(r->right);
    rotateLeft(r);
}


void AVLTree::rotateLeftRight(Node*&r)
{
    rotateLeft(r->left);
    rotateRight(r);
}


void AVLTree::rotateRight(Node*&r)
{
    Node *p;
    p = r->left;
    r->left = p->right;
    p->right = r;
    r = p;
}


void AVLTree::rotateLeft(Node*&r)
{
    Node *p;
    p = r->right;
    r->right = p->left;
    p->left = r;
    r = p;
}

//checks difference in heights between left and right subtrees
int AVLTree::difference(Node*r)
{
    int diff;
    if (r == nullptr)
        return 0;
    diff = height(r->left) - height(r->right);
    return diff;
}

//Height method returns height of subtrees
int AVLTree::height(Node*r)
{
    int LH, RH;
    if (r == nullptr)
    {
        return 0;
    }
    LH = height(r->left);
    RH = height(r->right);
    if (LH > RH)
        return (1+LH);
    else
        return (1+RH);
}

//constructor
AVLTree::AVLTree()
{
    root = nullptr;
}

//destructor
AVLTree::~AVLTree()
{
    clear(root);
}

void AVLTree::clear()
{
    clear(root);
    root = nullptr;
}

//clears tree and sets root back to null
void AVLTree::clear(Node*& r)
{
    if(r != nullptr)
    {
        clear(r->left);
        clear(r->right);
        delete r;
    }
}

void AVLTree::append(int num, int qty, double price, string desc)
{
    append(root, num, qty, price, desc);
}


//appends new leafs to tree with sorting based on unique partnum integer values
void AVLTree::append(Node*& r, int num, int qty, double price, string desc)
{
    if(r == nullptr)
    {
        r = new Node;
        r->partnum = num;
        r->qty = qty;
        r->price = price;
        r->description = desc;
        r->left = nullptr;
        r->right = nullptr;
    }
    else if(num < r->partnum)
        append(r->left, num, qty, price, desc);
    else
        append(r->right, num, qty, price, desc);
    balance(r);
}

void AVLTree::remove(int num)
{
    remove(root, num);
}

void AVLTree::remove(Node*& r, int num)
{
    if(r == nullptr)
        return;
    else if(num < r->partnum)
        remove(r->left, num);
    else if(num > r->partnum)
        remove(r->right, num);
    else
    {
        Node* p;
        if(r->left == nullptr && r->right == nullptr)        // no child nodes
        {
            delete r;
            r = nullptr;
        }
        else if(r->left != nullptr && r->right == nullptr)    // left child node
        {
            p = r;
            r = r->left;
            delete p;
        }
        else if(r->left == nullptr && r->right != nullptr)    // right child node
        {
            p = r;
            r = r->right;
            delete p;
        }
        else                                                // two child nodes
        {
            p = r->right;
            
            while(p->left)
                p = p->left;
            p->left = r->left;
            p = r;
            r = r->right;
            delete p;
        }
    }
    balance(r);
}

string AVLTree::getPart(int num)
{
   return getPart(root, num);
};

//searches tree for part
string AVLTree::getPart(Node*r, int num)
{
    char  temp[100];
    
    if(r == nullptr)
    {
        sprintf(temp, "%s \n", "No part with that number.");
        return temp;
    }
    else if(r->partnum == num)
    {
        sprintf(temp, " %d \n %s \n %g \n %i \n", r->partnum, r->description.c_str(), r->price, r->qty);
        return temp;
    }
    else if(num < r->partnum)
        return getPart(r->left, num);
    else
        return getPart(r->right, num);
}

string AVLTree:: getOutOfStock()
{
    string str = getOutOfStock(root);
    if (str.empty())
        str = "no parts\n";
    return str;
}

//traverses tree and collects data for all parts that has quantity of zero into a char block.
string AVLTree::getOutOfStock(Node*r)
{
    //stringstream ss;
    char  temp[50];
    char block[1000] = "";
    string str;
    
    if (r != nullptr)
    {
        str = getOutOfStock(r->left);
        strcat(block, str.c_str());
        
        if (r->qty == 0)
        {
            sprintf(temp, " %d %s %g %i \n", r->partnum, r->description.c_str(), r->price, r->qty);
            strcat(block, temp);
        }
    
        str = getOutOfStock(r->right);
        strcat(block, str.c_str());
    }
    return block;
}


int main()
{
    AVLTree partsDB;
    char UserInput;
    int partnum, qty;
    string desc;
    double price;

    //user menu interface
    do
    {
        cout << "MENU" << endl;
        cout << "  (A)dd a Part" << endl;
        cout << "  (R)emove a Part" << endl;
        cout << "  (S)earch for a Part" << endl;
        cout << "  (O)ut of Stock" << endl;
        cout << "  (Q)uit" << endl;
        cout << "[Enter your choice] >> ";
        cin >> UserInput;
        
        switch(toupper(UserInput))
        {
            case 'A':
                cout << "Enter part description: ";
                cin.ignore();
                getline(cin, desc, '\n');
                cout << "Enter the price: ";
                cin >> price;
                cout << "Enter the part number: ";
                cin >> partnum;
                cout << "Enter the quantity on hand: ";
                cin >> qty;
                partsDB.append(partnum, qty, price, desc);
                break;
            case 'R':
                cout << "Enter part number for part to remove: ";
                cin >> partnum;
                partsDB.remove(partnum);
                break;
            case 'S':
                cout << "Enter part number to search for: ";
                cin >> partnum;
                cout << partsDB.getPart(partnum) << endl;;
                break;
            case 'O':
                cout << "The folowing items are out of stock: " << endl;
                cout << partsDB.getOutOfStock();
                break;
            case 'Q':
                UserInput = 'Q';
                break;
            default:
                break;
        }
    }while(toupper(UserInput)!= 'Q');
    
    cout << "\n" << "\n";
    
    return 0;
}
