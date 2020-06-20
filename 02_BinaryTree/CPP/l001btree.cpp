#include <iostream>
#include <vector>
#include <list>

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

void preOrder(Node *node)
{
    if (node == NULL)
        return;

    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void postOrder(Node *node)
{
    if (node == NULL)
        return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

void inOrder(Node *node)
{
    if (node == NULL)
        return;

    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

vector<Node *> *nodeToRootPath(Node *node, int val)
{
    if (node == NULL)
        return NULL;

    if (node->data == val)
    {
        vector<Node *> *base = new vector<Node *>();
        base->push_back(node);
        return base;
    }

    vector<Node *> *lres = nodeToRootPath(node->left, val);
    if (lres != NULL)
    {
        lres->push_back(node);
        return lres;
    }
    vector<Node *> *rres = nodeToRootPath(node->right, val);
    if (rres != NULL)
    {
        rres->push_back(node);
        return rres;
    }
    return NULL;
}

int lca(Node *node, int val1, int val2)
{
    vector<Node *> *path1 = nodeToRootPath(node, val1);
    vector<Node *> *path2 = nodeToRootPath(node, val2);

    int lca = -1;

    int i = path1->size() - 1;
    int j = path2->size() - 1;

    while (i >= 0 && j >= 0 && (*path1)[i] == (*path2)[j])
    {
        lca = (*path1)[i]->data;
        i--;
        j--;
    }
    return lca;
}

Node *lcaNode = NULL;

bool lca2(Node *node, int data1, int data2)
{
    if (node == NULL)
        return false;

    bool selfdone = false;
    if (node->data == data1 || node->data == data2)
        selfdone = true;

    bool leftdone = lca2(node->left, data1, data2);
    if (lcaNode != NULL)
        return true;

    bool rightdone = lca2(node->right, data1, data2);
    if (lcaNode != NULL)
        return true;

    if ((selfdone && leftdone) || (selfdone && rightdone) || (leftdone && rightdone))
    {
        lcaNode = node;
    }

    return leftdone || rightdone || selfdone;
}

// diameter~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// o(n ^ 2) approach for diamter
int diameter1(Node *node)
{
    if (node == NULL)
        return 0;

    int lh = height(node->left);
    int rh = height(node->right);

    int ld = diameter1(node->left);
    int rd = diameter1(node->right);

    return max(lh + rh, max(ld, rd));
}

// O(n) approach for diamter using class pair
class diaPair
{
public:
    int ht;
    int dia;

    diaPair(int ht, int dia)
    {
        this->ht = ht;
        this->dia = dia;
    }

    diaPair()
    {
    }
};

diaPair *diameter2(Node *node)
{
    if (node == NULL)
        return new diaPair(0, 0);

    diaPair *lpair = diameter2(node->left);
    diaPair *rpair = diameter2(node->right);

    diaPair *mpair = new diaPair();
    mpair->ht = max(lpair->ht, rpair->ht) + 1;
    mpair->dia = max(lpair->ht + rpair->ht, max(lpair->dia, rpair->dia));

    delete lpair;
    delete rpair;
    return mpair;
}

// O(n) approach for diameter without using pair class
int dia = 0;

int diameter3(Node *node)
{
    if (node == NULL)
        return 0;

    int lh = diameter3(node->left);
    int rh = diameter3(node->right);

    dia = max(dia, lh + rh);

    return max(lh, rh) + 1;
}

// levelOrder traversal~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void levelOrder01(Node *node)
{
    // Implement parent queue and child queue - addlast, removeFirst
    list<Node *> queue;

    queue.push_back(node);

    while (queue.size() != 0)
    {
        // remove and get
        Node *rem = queue.front();
        queue.pop_front();
        cout << rem->data << " ";

        // push in child queue
        if (rem->left != NULL)
            queue.push_back(rem->left);
        if (rem->right != NULL)
            queue.push_back(rem->right);
    }
}

// levelorder linewise using two queueus
void levelOrder02(Node *node)
{
    // Implement parent queue and child queue - addlast, removeFirst
    list<Node *> parent;
    list<Node *> child;

    parent.push_back(node);
    int level = 0;

    cout << "level " << level << " -> ";
    while (parent.size() != 0)
    {
        // remove and get
        Node *rem = parent.front();
        parent.pop_front();
        cout << rem->data << " ";

        // push in child queue
        if (rem->left != NULL)
            child.push_back(rem->left);
        if (rem->right != NULL)
            child.push_back(rem->right);

        if (parent.size() == 0)
        {
            cout << endl;
            level++;
            if (child.size() != 0)
                cout << "level " << level << " -> ";

            // swap parent and child
            list<Node *> temp;
            temp = parent;
            parent = child;
            child = temp;
        }
    }
}

// levelorder linewise using single queue (NULL concept)
void levelOrder03(Node *node)
{
    list<Node *> queue;
    queue.push_back(node);
    queue.push_back(NULL);

    int level = 0;
    cout << "level : " << level << " -> ";

    while (queue.size() != 1)
    {
        Node *rem = queue.front();
        queue.pop_front();
        cout << rem->data << " ";
        if (rem->left != NULL)
            queue.push_back(rem->left);
        if (rem->right != NULL)
            queue.push_back(rem->right);

        if (queue.front() == NULL)
        {
            queue.pop_front();
            queue.push_back(NULL);
            level++;
            if (queue.size() != 1)
                cout << "\nlevel : " << level << " -> ";
        }
    }
}

// levelorder linewise without even using NULL
void levelOrder04(Node *node)
{
    list<Node *> queue;

    queue.push_back(node);
    int level = 0;
    while (queue.size() != 0)
    {
        cout << "level : " << level << " -> ";
        level++;
        int size = queue.size();

        while (size-- > 0)
        {
            Node *rem = queue.front();
            queue.pop_front();
            cout << rem->data << " ";
            if (rem->left != NULL)
                queue.push_back(rem->left);
            if (rem->right != NULL)
                queue.push_back(rem->right);
        }
        cout << endl;
    }
}

void levelOrder(Node *node)
{
    // levelOrder01(node);
    // levelOrder02(node);
    // levelOrder03(node);
    // levelOrder04(node);
}

// view~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void leftView(Node *node)
{
    list<Node *> queue;

    queue.push_back(node);

    while (queue.size() != 0)
    {
        int size = queue.size();
        cout << queue.front()->data << " ";
        while (size-- > 0)
        {
            Node *rem = queue.front();
            queue.pop_front();
            if (rem->left != NULL)
                queue.push_back(rem->left);
            if (rem->right != NULL)
                queue.push_back(rem->right);
        }
    }
}

void rightView(Node *node)
{
    list<Node *> queue;

    queue.push_back(node);

    while (queue.size() != 0)
    {
        int size = queue.size();
        Node *prev = NULL;
        while (size-- > 0)
        {
            Node *rem = queue.front();
            queue.pop_front();
            prev = rem;
            if (rem->left != NULL)
                queue.push_back(rem->left);
            if (rem->right != NULL)
                queue.push_back(rem->right);
        }
        cout << prev->data << " ";
    }
}




void solve()
{
    // vector<int> arr{10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    // int idx = 0;
    // Node *root = construct(arr, idx);
    // display(root);
    // cout << "Minimum : " << myMin(root) << endl;
    // cout << "Maximum : " << myMax(root) << endl;
    // cout << "Size : " << size(root) << endl;
    // cout << "Height : " << height(root) << endl;
}

int main(int argc, char **argv)
{
    solve();
    return 0;
}
