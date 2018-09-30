#include <iostream>
#include <queue>
#include <unordered_map>
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



    int getBestElem(TreeNode* root){
        unordered_map<int, int> m;
        m[root->val]++;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode* x = q.front();
            q.pop();
            if(x->left != nullptr)
            {
                q.push(x->left);
                m[x->left->val]++;
            }
            if(x->right != nullptr)
            {
                q.push(x->right);
                m[x->right->val]++;
            }
        }
        
        int maxim = -1;
        int num;
        for(size_t i = 0; i <= 1000000; i++)
            if(m[i] > maxim)
            {
                maxim = m[i];
                num = i;
            }
        
                
        return num;
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
    cout << t.getBestElem(t.getRoot());
    return 0;
}
