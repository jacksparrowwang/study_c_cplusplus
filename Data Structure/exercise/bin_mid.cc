#include <iostream>
using namespace std;

void BinMid(Node* root)
{
    stack<Node*> s;
    Node* cur = root;
    while(1)
    {
        while (cur != NULL)
        {
            s.push(cur);
            cur = cur->left;
        }
        if (s.size() == 0)
        {
            break;
        }
        printf("%d", s.top()->data);
        cur = s.top();
        s.pop();
        cur = cur->right;
    }
}

void LevelOrder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* cur = root;
    while (q.size() != 0)
    {
        printf("%d ", q.top()->data);
        cur = q.top();
        q.pop();
        if (cur->left != NULL)
        {
            q.push(cur->left);
        }
        if (cur->right != NULL)
        {
            q.push(cur->right);
        }
    }
}
