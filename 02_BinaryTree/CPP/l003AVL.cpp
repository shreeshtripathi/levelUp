#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int data;
    Node *left = NULL;
    Node *right = NULL;

    int ht = 1;
    int bal = 0;

    Node(int data)
    {
        this->data = data;
        this->ht = ht;
        this->bal = bal;
    }
};

void setHeightAndBal(Node *node)
{
    int lh = node->left == NULL ? 0 : node->left->ht;
    int rh = node->right == NULL ? 0 : node->right->ht;

    node->ht = max(lh, rh) + 1;
    node->bal = lh - rh;
}

// ll rotation
Node *ll(Node *A)
{
    Node *B = A->left;
    Node *T3 = B->right;

    B->left = A;
    A->left = T3;

    setHeightAndBal(A);
    setHeightAndBal(B);

    return B;
}

// rr rotation
Node *rr(Node *A)
{
    Node *B = A->right;
    Node *T3 = B->left;

    B->left = A;
    A->right = T3;

    setHeightAndBal(A);
    setHeightAndBal(B);

    return B;
}

// get rotation
Node *getRotation(Node *node)
{
    setHeightAndBal(node);
    if (node->bal == 2) // ll OR lr
    {
        if (node->left->bal == 1) // ll
        {
            return ll(node);
        }
        else if (node->left->bal == -1) // lr
        {
            node->left = rr(node->left);
            return ll(node);
        }
    }
    else if (node->bal == -2) // rr OR rl
    {
        if (node->left->bal == -1) // rr
        {
            return rr(node);
        }
        else if (node->left->bal == 1) // rl
        {
            node->right = ll(node->right);
            return rr(node);
        }
    }
    return node;
}

Node *constructBST(vector<int> &arr, int lo, int hi)
{
    if (lo > hi)
        return NULL;

    int mid = (lo + hi) / 2;
    Node *node = new Node(arr[mid]);
    node->left = constructBST(arr, lo, mid - 1);
    node->right = constructBST(arr, mid + 1, hi);

    setHeightAndBal(node);
    return node;
}

int max(Node *node)
{
    Node *curr = node;

    while (curr->right != NULL)
        curr = curr->right;

    return curr->data;
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

Node* addData(Node* node, int data) {
    if(node == nullptr) {
        return new Node(data);
    }

    if(node->data > data) {
        node->left = addData(node->left, data);
    } else {
        node->right = addData(node->right, data);
    }

    return getRotation(node);
}

Node *removeData(Node *root, int data)
{
    if (root == nullptr)
        return nullptr; // never found data;

    if (data < root->data)
        root->left = removeData(root->left, data);
    else if (data > root->data)
        root->right = removeData(root->right, data);
    else
    { // data found.

        if (root->left == nullptr || root->right == nullptr)
            return root->left != nullptr ? root->left : root->right;

        int maxInleft = max(root->left);
        root->data = maxInleft;
        root->left = removeData(root->left, maxInleft);
    }
    return getRotation(root);
}

void solve()
{
    // vector<int> arr{10, 20, 30, 40, 50, 6, 70, 80, 90, 100, 110};
    // Node *root = constructBST(arr, 0, arr.size() - 1);
    Node *root = nullptr;
    root = addData(root, 10);
    display(root);
    cout << endl;
    root = addData(root, 20);
    display(root);
    root = addData(root, 30);
    cout << endl;
    display(root);
    // root = addData(root, 40);
    // cout << endl;
    // display(root);
}

int main(int argc, char **argv)
{
    solve();
}