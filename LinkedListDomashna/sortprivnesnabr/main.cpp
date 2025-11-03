#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() {
        head = nullptr;
    }

    void insertSorted(int val) {
        Node* newNode = new Node(val);
        if (!head || val < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data < val)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;
    int x;
    cout << "Vnesuvaj broevi (0 za kraj): ";
    while (cin >> x && x != 0) {
        list.insertSorted(x);
        cout << "Sortirana lista: ";
        list.print();
    }
}
