#include <iostream>
#include <vector>
#include <string.h> // memcpy

using namespace std;

template <typename T>
class BinaryTree
{
private:
    BinaryTree<T> *branchLeft;
    BinaryTree<T> *branchRight;

    T *value;

public:

  BinaryTree(): branchLeft(NULL), branchRight(NULL), value(NULL) {}

  BinaryTree(T data): branchLeft(NULL), branchRight(NULL) {
    setData(data);
  }

  ~BinaryTree() {
    if (value)
      delete value;

    if (branchLeft)
      delete branchLeft;

    if (branchRight)
      delete branchRight;
  }

  // Insert data recursively randomly where it is possible. TODO 1.3
  void setData(T data) {
    value = (T *)new char[sizeof(T)];
    memcpy(value, &data, sizeof(data));
  }

  BinaryTree<T>*& getLeft() {
    return branchLeft;
  }

  BinaryTree<T>*& getRight() {
    return branchRight;
  }

  void preOrder() {
    // TODO: complete the preorder method
      if(value != nullptr)
      cout << *value << ' ';
      if(branchLeft != nullptr)
      branchLeft->preOrder();
      if(branchRight != nullptr)
      branchRight->preOrder();
  }

  void inOrder() {
    // TODO: complete the inorder method
      if(branchLeft != nullptr)
      branchLeft->inOrder();
      if(value != nullptr)
      cout << *value << ' ';
      if(branchRight != nullptr)
      branchRight->inOrder();
  }

  void printLvl(int lvl) {
    // TODO: complete the print level method
      if(lvl == 1){
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

void buildTree(BinaryTree<int>* &bt, vector<int> &v, int idx) {
  if (!(idx < v.size()) || v[idx] == -1) {
    bt = NULL;
    return;
  }
  
  bt = new BinaryTree<int>(v[idx]);
  buildTree(bt->getLeft(), v, idx * 2 + 1);
  buildTree(bt->getRight(), v, idx * 2 + 2);
}

int main() {
  BinaryTree<int>* bt = NULL;

  int n;
  cin >> n;

  vector<int> vct(n);
  for(int i = 0; i < n; i++) {
    cin >> vct[i];
  }

  buildTree(bt, vct, 0);

  int testCase = -1;
  cin >> testCase;
  
  switch(testCase) {
   	case 1:
      bt->preOrder();
      cout << endl;
      break;
    case 2:
      bt->inOrder();
      cout << endl;
      break;
    case 3:
      for (int i = 1; i <= 5; i++) {
        bt->printLvl(i);
        cout << endl;
      }
     break;
    default:
      return -1;
  }
  
  return 0;
}
