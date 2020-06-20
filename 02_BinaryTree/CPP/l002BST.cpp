#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Node
{
public:
    int data;
    Node *left = NULL;
    Node *right = NULL;

    Node(int data)
    {
        this->data = data;
    }
};

Node *constructBST(vector<int> &arr, int lo, int hi)
{
    if (lo > hi)
        return NULL;

    int mid = (lo + hi) / 2;
    Node *node = new Node(arr[mid]);
    node->left = constructBST(arr, lo, mid - 1);
    node->right = constructBST(arr, mid + 1, hi);

    return node;
}

void display(Node *node)
{
    if (node == NULL)
        return;

    string str = "";
    str += node->left == NULL ? ".\t" : to_string(node->left->data) + "\t";
    str += "<- " + to_string(node->data) + " ->";
    str += node->right == NULL ? "\t." : "\t" + to_string(node->right->data);

    cout << str << endl;

    display(node->left);
    display(node->right);
}

// Basic~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int height(Node *node)
{
    if (node == NULL)
        return 0;
    return max(height(node->left), height(node->right)) + 1;
}

int size(Node *node)
{
    if (node == NULL)
        return 0;

    return size(node->left) + size(node->right) + 1;
}

bool find(Node *node, int data)
{
    Node *curr = node;
    while (curr != NULL)
    {
        if (curr->data == data)
            return true;
        else if (curr->data > data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return false;
}

int min(Node *node)
{
    Node *curr = node;

    while (curr->left != NULL)
        curr = curr->left;

    return curr->data;
}

int max(Node *node)
{
    Node *curr = node;

    while (curr->right != NULL)
        curr = curr->right;

    return curr->data;
}

void basic(Node *node)
{
    // display(root);
    cout << "Find (75) : " << find(node, 75) << endl;
}

// return the data in range of a, b
void dataInRange_01(Node *node, int a, int b, vector<int> &ans)
{
    if (node == nullptr)
        return;

    dataInRange_01(node->left, a, b, ans);
    if (node->data >= a && node->data <= b)
    {
    }
    dataInRange_01(node->right, a, b, ans);
}

// oroot = original root
void targetSumPair_1(Node *node, Node *oroot, int target)
{
    if (node == NULL)
        return;

    int val1 = node->data;
    int val2 = target - val1;

    if (val1 > val2 && find(oroot, val2) == true)
        cout << val1 << " + " << val2 << " = " << (val1 + val2) << endl;

    targetSumPair_1(node->left, oroot, target);
    targetSumPair_1(node->right, oroot, target);
}

void targetSumPair_2(Node node, int target)
{
    // make a helper function of INORDER Traversal(In Inorder it is sorted array)
    // make two pointer and implement it for target sum
}

// target sum pair using two stack
void insert_left_most(Node *node, stack<Node *> &st)
{
    while (node != NULL)
    {
        st.push(node);
        node = node->left;
    }
}

void insert_right_most(Node *node, stack<Node *> &st)
{
    while (node != NULL)
    {
        st.push(node);
        node = node->right;
    }
}

void targetSumPair_3(Node *node, int target)
{
    stack<Node *> left;
    stack<Node *> right;

    insert_left_most(node, left);
    insert_right_most(node, right);

    while (left.size() != 0 && right.size() != 0)
    {
        int val1 = left.top()->data;
        int val2 = right.top()->data;

        if (val1 >= val2)
        {
            left.pop();
            right.pop();
        }
        else if (val1 + val2 < target)
        {
            Node *rem = left.top();
            left.pop();
            insert_left_most(rem->right, left);
        }
        else if (val1 + val2 > target)
        {
            Node *rem = right.top();
            right.pop();
            insert_right_most(rem->left, right);
        }
        else
        {
            cout << val1 << " + " << val2 << " = " << val1 + val2 << endl;
            insert_left_most(left.top()->right, left);
            insert_right_most(right.top()->left, right);
            left.pop();
            right.pop();
        }
    }
}

void targetSumPair(Node *node)
{
    int target = 100;
    targetSumPair_1(node, node, target);
    cout << "\n \n";
    targetSumPair_3(node, target);
}

void solve()
{
    vector<int> arr{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
    Node *root = constructBST(arr, 0, arr.size() - 1);
    // basic(root);
    targetSumPair(root);
}

int main(int argc, char **argv)
{
    solve();
    return 0;
}
