#include <iostream>
#include <cstring>

using namespace std;

class linkedlist
{
private:
    class Node
    {
    public:
        int data;
        Node *next = nullptr;

        Node(int data)
        {
            this->data = data;
            this->next = nullptr;
        }

        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };

public:
    Node *head = nullptr;
    Node *tail = nullptr;
    int size = 0;

    int mysize()
    {
        return this->size;
    }

    bool isEmpty()
    {
        return this->size == 0;
    }

    Node *getNodeAt(int pos)
    {
        Node *curr = this->head;

        while (pos-- > 0)
            curr = curr->next;

        return curr;
    }

    friend ostream &operator<<(ostream &os, const Node *temp);

    void display()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
    }

    // Add_Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void addFirstNode(Node *node)
    {
        if (this->size == 0)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->next = this->head;
            this->head = node;
        }
        this->size++;
    }

    void addFirst(int data)
    {
        Node *node = new Node(data);
        addFirstNode(node);
    }

    void addLastNode(Node *node)
    {
        if (this->size == 0)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            this->tail->next = node;
            this->tail = node;
        }
        this->size++;
    }

    void addLast(int data)
    {
        Node *node = new Node(data);
        addLastNode(node);
    }

    void addAtNode(Node *node, int index)
    {
        if (index < size || index > size)
        {
            cout << "nullptrPointerException" << endl;
        }
        else if (index == 0)
        {
            addFirstNode(node);
        }
        else if (index == this->size)
        {
            addLastNode(node);
        }
        else
        {
            Node *nodeIm1 = getNodeAt(index - 1);
            node->next = nodeIm1->next;
            nodeIm1->next = node;
            this->size++;
        }
    }

    void addAt(int data, int index)
    {
        Node *node = new Node(data);
        addAtNode(node, index);
    }

    // Remove_Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int removeFirst()
    {
        if (this->size == 0)
        {
            cout << "Empty List!" << endl;
            return -1;
        }

        Node *rNode = this->head;

        if (this->size == 1)
        {
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            this->head = this->head->next;
            rNode->next = nullptr;
        }
        this->size--;
        return rNode->data;
    }

    int removeLast()
    {
        if (this->size == 0)
        {
            cout << "Empty List!" << endl;
            return -1;
        }

        Node *rNode = this->tail;

        if (this->size == 1)
        {
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            Node *secondLast = getNodeAt(this->size - 2);
            secondLast->next = nullptr;
            this->tail = secondLast;
        }
        this->size--;
        return rNode->data;
    }

    int removeAt(int index)
    {
        if (index < size || index >= size)
        {
            cout << "nullptrPointerException" << endl;
            return -1;
        }
        else if (index == 0)
        {
            return removeFirst();
        }
        else if (index == this->size - 1)
        {
            return removeLast();
        }
        else
        {
            Node *nodeAtI = getNodeAt(index - 1);
            Node *rNode = nodeAtI->next;

            nodeAtI->next = rNode->next;
            rNode->next = nullptr;
            this->size--;
            return rNode->data;
        }
    }

    // Get_Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getFirst()
    {
        if (this->size == 0)
        {
            cout << "Empty List!" << endl;
            return -1;
        }
        else
        {
            return this->head->data;
        }
    }

    int getLast()
    {
        if (this->size == 0)
        {
            cout << "Empty List!" << endl;
            return -1;
        }
        else
        {
            return this->tail->data;
        }
    }

    int getAt(int index)
    {
        if (index < size || index > size)
        {
            cout << "nullptrPointerException" << endl;
            return -1;
        }
        else if (index == 0)
        {
            return getFirst();
        }
        else if (index == this->size - 1)
        {
            return getLast();
        }
        else
        {
            return getNodeAt(index)->data;
        }
    }
};

ostream &operator<<(ostream &os, linkedlist &list)
{
    list.display();
    return os;
}

int main(int aregc, char **argv)
{
    linkedlist ll;

    for (int i = 1; i <= 10; i++)
    {
        ll.addLast(10 * i);
    }

    cout << ll << endl;
}
