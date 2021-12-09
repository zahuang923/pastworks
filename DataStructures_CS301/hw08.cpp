#include<iostream>
using namespace std;

class Tree
{
private:
    struct Node
    {
        int i, j;
        string word;
        Node *left, *right;
    };
    
    Node *root;
    
    void insert(Node*&, int, int , string);
    void remove(Node*&, int);
    bool find(Node*, int) const;
    void print(Node*) const;
    void clear(Node*&);
    
public:
    Tree();
    ~Tree();
    void insert(int, int, string);
    void remove(int);
    bool find(int) const;
    void print() const;
    void clear();
};

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    clear(root);
}

void Tree::insert(int i, int j, string k)
{
    insert(root, i, j, k);
}


//compare first integer value
void Tree::insert(Node*& r, int i, int j, string k)
{
    if(r == nullptr)
        r = new Node { i , j, k };
    else if(i < r->i)
        insert(r->left, i, j, k);
    else
        insert(r->right, i, j, k);
}

void Tree::remove(int i)
{
    remove(root, i);
}

void Tree::remove(Node*& r, int i)
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

bool Tree::find(int i) const
{
    return find(root, i);
}

bool Tree::find(Node* r, int i) const
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

void Tree::print() const
{
    print(root);
}

void Tree::print(Node* r) const
{
    if(r != nullptr)
    {
        print(r->left);
        cout << r->word << "\t";
        print(r->right);
    }
}

void Tree::clear()
{
    clear(root);
    root = nullptr;
}

void Tree::clear(Node*& r)
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
    Tree t;
    t.insert(0, 1, "abc");
    t.insert(-1, 22, "def");
    t.insert(2, 33, "ghi");
    t.insert(6, 2, "jkl");
    t.insert(-4, 23, "mno");
    
    t.print();
    cout << "\n" << "\n";
    
    
    return 0;
}
