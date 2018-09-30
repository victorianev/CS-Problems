#include <iostream>
#include <queue>
#include <cstring>
#include <memory>

using namespace std;

struct TreeNode {
    int val;
    // TreeNode *left;
    shared_ptr<TreeNode> left, right, father;
    // TreeNode *right;
    // TreeNode *father;
    /*TreeNode() {

        left = nullptr;
        right = nullptr;
        father = nullptr;
    }*/
};

class Tree {
private:
    // TreeNode* root = NULL;
    shared_ptr<TreeNode> root;
public:
    void add(shared_ptr<TreeNode> node) {
        if (root == nullptr) {
            root = node;
        }
        else {
            shared_ptr<TreeNode> aux = root;
            while (aux != nullptr) {
                if (aux->val > node->val) {
                    if (aux->right != nullptr) {
                        aux = aux->right;
                    }
                    else {
                        node -> father = aux;
                        aux->right = node;
                        break;
                    }
                }
                else {
                    if (aux->left != nullptr) {
                        aux = aux->left;
                    }
                    else {
                        node -> father = aux;
                        aux->left = node;
                        break;
                    }
                }
            }
        }
    }

    shared_ptr<TreeNode> getRoot() {
        return root;
    }


   int height(shared_ptr<TreeNode> root) {
        // Write your code here.
       if(root == nullptr)
           return 0;

       return max(height(root->left), height(root->right)) + 1;
    }


    int treeDiameter(shared_ptr<TreeNode> root){
        if(root == nullptr)
            return 0;

        int hleft = 0, hright = 0;
        hleft = height(root->left);
        hright = height(root->right);

        int dleft = treeDiameter(root->left);
        int dright = treeDiameter(root->right);

        return max(hleft + hright + 1, max(dleft, dright)) - 1;
    }
};

int main()
{
    int n, x;
    cin >> n;
    Tree t;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        // TreeNode* aux = new TreeNode;
        shared_ptr<TreeNode> aux = make_shared<TreeNode>();
        aux -> val = x;
        t.add(aux);
    }
    cout << t.treeDiameter(t.getRoot());
    return 0;
}

