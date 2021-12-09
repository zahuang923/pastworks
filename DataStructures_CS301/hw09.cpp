#include<iostream>
using namespace std;

class AVLTree
{
private:
    struct Node
    {
        int i, j;
        string word;
        Node *left, *right;
    } *root;
    
    void insert(Node*&, int, int , string);
    void remove(Node*&, int);
    bool find(Node*, int) const;
    void print(Node*) const;
    void clear(Node*&);
    int height(Node*);
    int difference(Node*);
    void rotateright(Node*&);
    void rotateleft(Node*&);
    void rotateleftright(Node*&);
    void rotaterightleft(Node*&);
    void balance(Node*&);
    void remove(Node*&);
    
public:
    AVLTree();
    ~AVLTree();
    void insert(int, int, string);
    void remove(int, int, string);
    void remove(int);
    bool find(int) const;
    void print() const;
    void clear();
};

void AVLTree::balance(Node*&r)
{
    if (difference(r) == -2)
    {
        if (difference(r->right) == -1)
            rotateleft(r);
        else
            rotaterightleft(r);
    }
    else if (difference(r) == 2)
    {
        if (difference(r->left) ==1)
            rotateright(r);
        else
            rotateleftright(r);
    }
}


void AVLTree::rotaterightleft(Node*&r)
{
    rotateright(r->right);
    rotateleft(r);
}


void AVLTree::rotateleftright(Node*&r)
{
    rotateleft(r->left);
    rotateright(r);
}


void AVLTree::rotateright(Node*&r)
{
    Node *p;
    p = r->left;
    r->left = p->right;
    p->right = r;
    r = p;
}


void AVLTree::rotateleft(Node*&r)
{
    Node *p;
    p = r->right;
    r->right = p->left;
    p->left = r;
    r = p;
}


int AVLTree::difference(Node*r)
{
    int diff;
    if (r == nullptr)
        return 0;
    diff = height(r->left) - height(r->right);
    return diff;
}


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


AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    clear(root);
}

void AVLTree::insert(int i, int j, string k)
{
    insert(root, i, j, k);
}


//compare first integer value
void AVLTree::insert(Node*& r, int i, int j, string k)
{
    if(r == nullptr)
    {
        r = new Node { i , j, k };
        r->left = nullptr;
        r->right = nullptr;
    }
    else if(i < r->i)
        insert(r->left, i, j, k);
    else
        insert(r->right, i, j, k);
    balance(r);
}

void AVLTree::remove(int i)
{
    remove(root, i);
}

void AVLTree::remove(Node*& r, int i)
{
    if(r == nullptr)
        return;
    else if(i < r->i)
        remove(r->left, i);
    else if(i > r->i)
        remove(r->right, i);
    else
    {
        Node* p;
        
        if(r->left == nullptr && r->right == nullptr)        // no kids
        {
            delete r;
            r = nullptr;
        }
        else if(r->left != nullptr && r->right == nullptr)    // left kid
        {
            p = r;
            r = r->left;
            delete p;
        }
        else if(r->left == nullptr && r->right != nullptr)    // right kid
        {
            p = r;
            r = r->right;
            delete p;
        }
        else                                                // two kids
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
}

bool AVLTree::find(int i) const
{
    return find(root, i);
}

bool AVLTree::find(Node* r, int i) const
{
    if(r == nullptr)
        return false;
    else if(r->i == i)
        return true;
    else if(i < r->i)
        return find(r->left, i);
    else
        return find(r->right, i);
}

void AVLTree::print() const
{
    print(root);
}

void AVLTree::print(Node* r) const
{
    if(r != nullptr)
    {
        print(r->left);
        cout << r->i << "\t";
        print(r->right);
    }
}

void AVLTree::clear()
{
    clear(root);
    root = nullptr;
}

void AVLTree::clear(Node*& r)
{
    if(r != nullptr)
    {
        clear(r->left);
        clear(r->right);
        delete r;
    }
}

int main()
{
    //instanstiate a tree object t
    AVLTree t;
    /*insert nodes based on comparing first integer key in the order: 0, -1, 2, 6, -4, 5
    //so as to create an unbalanced tree
    //balance is called at each insert, and the rotations, height and difference are all called recursively within
    //the balance call
    //in this example case, upon the insertion of the node containing first int key 5
    //the balance method is called and then detects an imbalance using height and difference methods
    //which then triggers a call to a rotaterightleft  methods which relies upon rotateright and rotateleft methods
    //thus main() successfully runs height, difference, rotateright, rotateleft, rotaterightleft, and balance methods*/
    t.insert(0, 1, "abc");
    t.insert(-1, 22, "def");
    t.insert(2, 33, "ghi");
    t.insert(6, 2, "jkl");
    t.insert(-4, 23, "mno");
    t.insert(5, 9, "pqr");
    
    //print out each of the tree nodes first integer keys using in-order processing (left child, parent, right child)
    t.print();
    cout << "\n" << "\n";
    
    return 0;
}
