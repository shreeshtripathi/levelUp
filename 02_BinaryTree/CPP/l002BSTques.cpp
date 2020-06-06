#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    int data;
    Node *left = NULL;
    Node *right = NULL;
};

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
};

// Leetcode 235 - LCA of BST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TreeNode *lowestCommonAncestor_(TreeNode *root, int small, int big)
{
    TreeNode *curr = root;
    while (curr != NULL)
    {
        if (curr->val >= small && curr->val <= big)
            return curr;
        else if (curr->val > big)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return NULL;
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (p->val > q->val)
        return lowestCommonAncestor_(root, q->val, p->val);
    else
        return lowestCommonAncestor_(root, p->val, q->val);
}

// Leetcode 98 - isBST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

long long prev_ = -1e12;

bool isValidBST(TreeNode *root)
{
    if (root == nullptr)
        return true;

    if (!isValidBST(root->left))
        return false;
    if (root->val > prev_)
    {
        prev_ = root->val;
    }
    else
    {
        return false;
    }

    return isValidBST(root->right);
}

// Leetcode : 99. Recover Binary Search Tree~~~~~~~~~~~~~~~~~~~~~~~~~`
TreeNode *a = nullptr, *b = nullptr, *c = nullptr;
bool recoverTree_(TreeNode *node)
{
    if (node == nullptr)
        return false;

    if (recoverTree_(node->left))
        return true;

    if (c != nullptr && c->val > node->val)
    {
        b = node;
        if (a == nullptr)
            a = c;
        else
            return true;
    }
    c = node;
    return recoverTree_(node->right);
}

void recoverTree(TreeNode *root)
{
    recoverTree_(root);
    if (a != nullptr)
    {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}


int main(int argc, char **argv)
{
}