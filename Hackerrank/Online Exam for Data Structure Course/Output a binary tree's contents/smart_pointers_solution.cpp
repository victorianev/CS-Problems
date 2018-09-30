#include <iostream>
#include <vector>
//#include <string.h> // memcpy
#include <memory>

using namespace std;

template <typename T>
class BinaryTree
{
private:
    shared_ptr< BinaryTree<T> > branchLeft;
    // BinaryTree<T> *branchLeft;
    shared_ptr< BinaryTree<T> > branchRight;
    // BinaryTree<T> *branchRight;

    shared_ptr<T> value;
    // T *value;

public:

    BinaryTree() //: branchLeft(nullptr), branchRight(nullptr), value(nullptr)
    {}

    BinaryTree(T data) //: branchLeft(nullptr), branchRight(nullptr)
    {
        setData(data);
    }

    /*
    ~BinaryTree() {
      if (value)
        delete value;

      if (branchLeft)
        delete branchLeft;

      if (branchRight)
        delete branchRight;
    }
    */

    // Insert data recursively randomly where it is possible. TODO 1.3
    void setData(T data)
    {
        // value = (T *)new char[sizeof(T)];
        // memcpy(value, &data, sizeof(data));
        value = make_shared<T>(data);
    }

    void setLeft(shared_ptr< BinaryTree<T> > newLeft)
    {
        branchLeft = newLeft;
    }

    shared_ptr< BinaryTree<T> > getLeft()
    {
        return branchLeft;
    }

    void setRight(shared_ptr< BinaryTree<T> > newRight)
    {
        branchRight = newRight;
    }

    shared_ptr< BinaryTree<T> > getRight()
    {
        return branchRight;
    }

    void preOrder()
    {
        // TODO: complete the preorder method
        if(value != nullptr)
            cout << *value << ' ';
        if(branchLeft != nullptr)
            branchLeft->preOrder();
        if(branchRight != nullptr)
            branchRight->preOrder();
    }

    void inOrder()
    {
        // TODO: complete the inorder method
        if(branchLeft != nullptr)
            branchLeft->inOrder();
        if(value != nullptr)
            cout << *value << ' ';
        if(branchRight != nullptr)
            branchRight->inOrder();
    }

    void printLvl(int lvl)
    {
        // TODO: complete the print level method
        if(lvl == 1)
        {
            if(value != nullptr)
                cout << *value << ' ';
        }
        else
        {
            if(branchLeft != nullptr)
                branchLeft->printLvl(lvl - 1);
            if(branchRight != nullptr)
                branchRight->printLvl(lvl - 1);
        }
    }
};

shared_ptr< BinaryTree<int> > buildTree(vector<int> &v, int idx)
{
    if (!(idx < v.size()) || v[idx] == -1)
    {
        return nullptr;
    }

    shared_ptr< BinaryTree<int> > bt = make_shared< BinaryTree<int> > (v[idx]);
    bt->setLeft(buildTree(v, idx * 2 + 1));
    bt->setRight(buildTree(v, idx * 2 + 2));
    return bt;
}

int main()
{
    shared_ptr< BinaryTree<int> > bt;

    int n;
    cin >> n;

    vector<int> vct(n);
    for(int i = 0; i < n; i++)
    {
        cin >> vct[i];
    }

    bt = buildTree(vct, 0);

    int testCase = -1;
    cin >> testCase;

    switch(testCase)
    {
    case 1:
        bt->preOrder();
        cout << endl;
        break;
    case 2:
        bt->inOrder();
        cout << endl;
        break;
    case 3:
        for (int i = 1; i <= 5; i++)
        {
            bt->printLvl(i);
            cout << endl;
        }
        break;
    default:
        return -1;
    }

    return 0;
}

