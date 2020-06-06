#include <iostream>
using namespace std;

// Let we have class of node

class node
{
public:
    int data;
    node *next;

    //Default Constructor :
    node(int d)
    {
        data = d;
        next = NULL;
    }
};

void addAtfront(node *&head, int data)
{

    if (head == NULL)
    {
        head = new node(data);
        return;
    }

    node *n = new node(data);
    n->next = head;
    head = n;
    return;
}

void addAtMiddle(node *&head, int p, int data)
{
    if (p == 0)
    {
        addAtfront(head, data);
    }
    else
    {
        node *ptr = head;
        for (int i = 0; i < p - 1; i++)
            ptr = ptr->next;

        node *n = new node(data);
        n->next = ptr->next;
        ptr->next = n;
    }
}

void input(node *&head)
{
    int data;
    cin >> data;

    while (data != -1)
    {
        addAtfront(head, data);
        cin >> data;
    }
}

void print(node *head)
{
    while (head != NULL)
    {
        cout << head->data << " => ";
        head = head->next;
    }
}

istream &operator>>(istream &is, node *&head)
{
    input(head);
    return is;
}

ostream &operator<<(ostream &os, node *head)
{
    print(head);
    return os;
}

int length(node *head)
{
    int l = 0;
    for (node *temp = head; temp != NULL; temp = temp->next)
    {
        l++;
    }
    return l;
}

void addAtend(node *&head, int data)
{

    addAtMiddle(head, length(head), data);
}

void deleteAtfront(node *&head)
{

    node *temp = head;
    head = head->next;

    delete temp;
}

void deleteAtMiddle(node *&head, int p)
{
    node *temp = head;
    if (p == 0)
    {
        deleteAtfront(head);
    }
    else
    {
        for (int i = 1; i <= p - 2; i++)
        {
            temp = temp->next;
        }
        node *temp2 = temp->next;
        temp->next = temp->next->next;
        delete temp2;
    }
}

int searchRecursively(node *head, int key, int i)
{
    if (head->next == NULL)
    {
        return -1;
    }

    if (head->data == key)
    {
        return i;
    }

    return searchRecursively(head->next, key, i + 1);
}

int middplePoint(node *head)
{
    int n = length(head) / 2;
    for (int i = 1; i <= n; i++)
    {
        head = head->next;
    }
    return head->data;
}

int findMid(node *head)
{
    node *f = head->next;
    node *s = head;

    while (f != NULL && f->next != NULL)
    {
        f = f->next->next;
        s = s->next;
    }
    return s->data;
}

// void merge(node *a, node *b)
// {
//     // Bese Case if any one of them is null return the other
//     if (a == NULL)
//     {
//         return b;
//     }
//     if (b == NULL)
//     {
//         return a;
//     }

//     node *c;
// }

int main()
{

    node *head = NULL;

    //Taking Input :
    //input(head);

    //Print the list
    //  print(head);

    // Now overlead << (input operator)
    cin >> head;
    //cout << head << endl << head2;
    cout << head << endl;
    // cout << "length is : " << length(head) << endl;

    //  cout << "Enter the data and position in which want to add " << endl;
    //int p,d;
    //cin >> d >> p;

    // addAtMiddle(head,p,d);
    ///cout << head;

    //Using insert at middle we can also insert at end :
    //  addAtend(head,27);
    //cout << head;

    // Deletion
    // delete at front
    //  deleteAtfront(head);
    // cout << head;

    //delete at middle
    int p = 3;

    deleteAtMiddle(head, p);
    cout << head;

    //Search Recursively :
    //  int key;
    // cin >> key;

    // cout << "Index is " <<  searchRecursively(head,key,1);

    //finding the middple point of the linked lists : // loop chal nhi rha
    //cout << middplePoint(head);

    // cout << findMid(head);

    //how to merge two linked lists in sorted order :

    return 0;
}