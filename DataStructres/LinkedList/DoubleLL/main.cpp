#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node* prev;
    Node(int v) : val(v), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head=nullptr;
        tail=nullptr;
    }

    void add(int value, int pos = -1) {
        Node* newNode = new Node(value);

        if (!head) {
            head = tail = newNode;
            return;
        }

        if (pos == -1) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            Node* temp = head;
            int idx = 0;
            while (temp && idx < pos) {
                temp = temp->next;
                idx++;
            }
            if (!temp) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            } else if (temp == head) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            } else {
                Node* prevNode = temp->prev;
                prevNode->next = newNode;
                newNode->prev = prevNode;
                newNode->next = temp;
                temp->prev = newNode;
            }
        }
    }

    void remove(int value) {
        Node* temp = head;
        while (temp) {
            if (temp->val == value) {
                if (temp->prev)
                    temp->prev->next = temp->next;
                else
                    head = temp->next;

                if (temp->next)
                    temp->next->prev = temp->prev;
                else
                    tail = temp->prev;

                delete temp;
                return;
            }
            temp = temp->next;
        }
    }

    Node* search(int value) {
        Node* temp = head;
        while (temp) {
            if (temp->val == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }


    ~DoublyLinkedList() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    DoublyLinkedList dll;

    dll.add(1);
    dll.add(2);
    dll.add(3);
    dll.add(10, 1);

    cout << "Lista: ";
    dll.print();

    dll.remove(10);
    cout << "Lista posle remove(10): ";
    dll.print();
    Node* found = dll.search(2);
    if (found) cout << "Element 2 e najden." << endl;
    else cout << "Ne e najden." << endl;

    return 0;
}
