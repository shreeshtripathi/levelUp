#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <stack>

using namespace std;

class Node
{
public:
    int data;
    vector<Node *> *children = NULL;

    Node(int data)
    {
        this->data = data;
    }

    Node()
    {
    }
};

Node *createGtree(vector<int> &dlist)
{
    stack<Node *> st;
    for (int i = 0; i < dlist.size() - 1; i++)
    {
        if (dlist[i] != -1)
        {
            Node *node = new Node(dlist[i]);
            st.push(node);
        }
        else
        {
            Node *node = st.top();
            st.pop();
            st.top()->children->push_back(node);
        }
    }
    return st.top();
}

int main(int argc, char **argv)
{
}