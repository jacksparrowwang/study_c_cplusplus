
// 给出中序和前序遍历，构建一个二叉树

#include <iostream>
#include <vector>
using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
class Solution {
public:
    int Find(vector<int>& vin, int beg, int end, int value)
    {
        for (int i = beg; i < end; ++i)
        {
            if (vin[i] == value)
            {
                return i;
            }
        }
        return -1;
    }
    TreeNode* BuildBinTree(vector<int>& pre, vector<int>& vin, int beg, int end, int* index)
    {
        if (end - beg < 1 || *index > (int)pre.size())
        {
            return NULL;
        }
        TreeNode* root = new TreeNode(pre[*index]);
        int mid = Find(vin, beg, end, pre[*index]);
        if (mid == -1)
        {
            return NULL;
        }
        ++(*index);
        root->left = BuildBinTree(pre, vin, beg, mid, index);
        root->right = BuildBinTree(pre, vin, mid+1, end, index);
        return root;
    }
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if (pre.size() == 0 || vin.size() == 0 || pre.size() != vin.size())
        {
            return NULL;
        }
        int index = 0;
        return BuildBinTree(pre, vin, 0, vin.size(), &index);
    }
};
