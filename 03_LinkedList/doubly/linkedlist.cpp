#include <iostream>
#include <vector>

using namespace std;

class linkedlist {
   private:
    class Node {
       public:
        int data;
        Node* next;
        Node* prev;

        Node(int data) {
            this->data = data;
            this->next = this->prev = nullptr;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    int size = 0;

    Node* getNodeAt(int pos) {
        Node* temp = head;
        while (pos--)
            temp = temp->next;

        return temp;
    }

   public:
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " <--> ";
            temp = temp->next;
        }
        cout << endl;
    }

    int mysize() {
        return this->size;
    }

    bool isEmpty() {
        return this->size == 0;
    }

    void addFirst(int data) {
        Node* node = new Node(data);
        if (this->size == 0) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        this->size++;
    }

    void addLast(int data) {
        Node* node = new Node(data);
        if (this->size == 0) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        this->size++;
    }

    void addAt(int data, int pos) {
        if (pos < 0 || pos > this->size) {
            cout << "Invalid Index" << endl;
            return;
        } else if (pos == 0) {
            addFirst(data);
        } else if (pos == this->size) {
            addLast(data);
        } else {
            Node* node = new Node(data);

            Node* nthNode = getNodeAt(pos);

            nthNode->prev->next = node;
            node->prev = nthNode->prev;
            node->next = nthNode;
            nthNode->prev = node;

            this->size++;
        }
    }

    int getFirst() {
        if (this->size == 0)
            return -1;

        return head->data;
    }

    int getLast() {
        if (this->size == 0)
            return -1;

        return tail->data;
    }

    int getAt(int pos) {
        if (pos < 0 || pos >= this->size) {
            return -1;
        }

        return getNodeAt(pos)->data;
    }

    void removeFirst() {
        if (this->size == 0) {
            cout << "Invalid" << endl;
            return;
        } else if (this->size == 1) {
            Node* temp = head;
            head = tail = nullptr;
            delete temp;
        } else {
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        this->size--;
    }

    void removeLast() {
        if (this->size == 0) {
            cout << "Invalid" << endl;
            return;
        } else if (this->size == 1) {
            Node* temp = head;
            head = tail = nullptr;
            delete temp;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        this->size--;
    }

    void removeAt(int pos) {
        if (pos < 0 || pos >= this->size) {
            cout << "Invalid Index" << endl;
            return;
        } else if (pos == 0) {
            removeFirst();
        } else if (pos == this->size - 1) {
            removeLast();
        } else {
            Node* nthNode = getNodeAt(pos);
            nthNode->prev->next = nthNode->next;
            nthNode->next->prev = nthNode->prev;
            delete nthNode;
            this->size--;
        }
    }
};

void solve() {
    linkedlist ll;

    ll.addFirst(1);
    ll.addFirst(2);
    ll.addLast(3);
    ll.addLast(4);
    ll.display();
    ll.removeLast();
    ll.addAt(5, 2);
    ll.display();
    cout << "size : " << ll.mysize() << endl;
    ll.removeFirst();
    ll.removeLast();
    ll.display();
    cout << "size : " << ll.mysize() << endl;
    ll.removeAt(2);
    ll.display();
}
int main(int argc, char** argv) {
    solve();
}