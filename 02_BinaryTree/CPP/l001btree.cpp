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

Node *construct(vector<int> &arr, int &idx)
{
    if (idx >= arr.size() || arr[idx] == -1)
    {
        idx++;
        return NULL;
    }

    Node *node = new Node(arr[idx++]);
    node->left = construct(arr, idx);
    node->right = construct(arr, idx);

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

int myMax(Node *node)
{
    if (node == NULL)
        return (int)10e-8;

    return max(node->data, max(myMax(node->left), myMax(node->right)));
}

int myMin(Node *node)
{
    if (node == NULL)
        return (int)10e8;

    return min(node->data, min(myMin(node->left), myMin(node->right)));
}

bool find(Node *node, int data)
{
    if (node == NULL)
        return false;

    if (node->data == data)
        return true;

    return find(node->left, data) || find(node->right, data);
}

//~~~~~~~~~~~~~~~~~~~~~~~TRAVERSAL~~~~~~~~~~~~~~~~~~~~~~~~

void solve()
{
    vector<int> arr{10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    int idx = 0;
    Node *root = construct(arr, idx);
    display(root);
    cout << "Minimum : " << myMin(root) << endl;
    cout << "Maximum : " << myMax(root) << endl;
    cout << "Size : " << size(root) << endl;
    cout << "Height : " << height(root) << endl;
}

int main(int argc, char **argv)
{
    solve();
    return 0;
}
