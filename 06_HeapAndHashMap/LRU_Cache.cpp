#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

// Leetcode 146. LRU Cache
/*
class LRUCache {
   private:
    unordered_map<int, int> map;
    list<int> ll;
    int cap = 0;

   public:
    LRUCache(int capacity) {
        this->cap = capacity;
    }

    int get(int key) {
        if (map.find(key) == map.end())
            return -1;
        else {
            ll.remove(key);
            ll.push_front(key);
            return map[key];
        }
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            ll.remove(key);
            ll.push_front(key);
            map[key] = value;
        } else {
            if(map.size() == cap) {
                map.erase(ll.back());
                ll.pop_back();
            }
            map[key] = value;
            ll.push_front(key); 
        }
    }
}; */

class LRUCache {
   private:
    class LinkedList {
       private:
        class Node {
           public:
            int key;
            int value;
            Node* prev;
            Node* next;

            Node(int key, int value) {
                this->key = key;
                this->value = value;
                this->prev = this->next = nullptr;
            }
        };

        unordered_map<int, Node*> map;
        Node* head = nullptr;
        Node* tail = nullptr;

       public:
        bool isPresent(int key) {
            return map.find(key) != map.end();
        }

        void setFirst(int key) {
            Node* node = map[key];

            // break connection
            node->prev->next = node->next;
            node->next->prev = node->prev;
            // set on head
            node->next = head;
            head->prev = node;
            node->prev = nullptr;
        }

        int getData(int key) {
            return map[key]->value;
        }

        void addFirst(int key, int value) {
            Node* node = new Node(key, value);
            map[key] = node;

            if (head == nullptr)
                head = tail = node;
            else {
                head->prev = node;
                node->next = head;
                head = node;
            }
        }

        void setAndUpdate(int key, int value) {
            setFirst(key);
            map[key]->value = value;
        }

        int size() {
            return map.size();
        }

        void removeLast() {
            map.erase(tail->key);
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;

            delete temp;
        }
    };
    int cap = 0;
    LinkedList li;

   public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if (li.isPresent(key) == false)
            return -1;
        else {
            li.setFirst(key);
            return li.getData(key);
        }
    }

    void put(int key, int value) {
        if (li.isPresent(key) == false) {
            if(li.size() == cap) {
                li.removeLast();
            }
            li.addFirst(key, value);
        } else {
            li.setAndUpdate(key, value);
        }
    }
};

int main(int argc, char** argv) {
}