#include <iostream>
#include <vector>

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
void dataInRange_01(Node* node, int a, int b, vector<int>& ans) {
    if(node == nullptr) return;

    dataInRange_01(node->left, a, b, ans);
    if(node->data >= a && node->data <= b) {

    }
    dataInRange_01(node->right, a, b, ans);
}


void solve()
{
    vector<int> arr{10, 20, 30, 40, 50, 6, 70, 80, 90, 100, 110};
    Node *root = constructBST(arr, 0, arr.size() - 1);
    basic(root);
}

int main(int argc, char **argv)
{
    solve();
    return 0;
}
