#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *father;
    TreeNode() {
        left = NULL;
        right = NULL;
        father = NULL;
    }
};

class Tree {
private:
    TreeNode* root = NULL;

public:
    void add(TreeNode* node) {
        if (root == NULL) {
            root = node;
        }
        else {
            TreeNode* aux = root;
            while (aux != NULL) {
                if (aux->val > node->val) {
                    if (aux->right != NULL) {
                        aux = aux->right;
                    }
                    else {
                        node -> father = aux;
                        aux->right = node;
                        break;
                    }
                }
                else {
                    if (aux->left != NULL) {
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

    TreeNode* getRoot() {
        return root;
    }

    
   int height(TreeNode* root) {
        // Write your code here.
       if(root == nullptr)
           return 0;
       
       return max(height(root->left), height(root->right)) + 1;
    }
    

    int treeDiameter(TreeNode* root){
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
        TreeNode* aux = new TreeNode;
        aux -> val = x;
        t.add(aux);
    }
    cout << t.treeDiameter(t.getRoot());
    return 0;
}
