#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node(int val) {
        value = val;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;
    LinkedList() { head = nullptr; }

    // Додавање на крај
    void add(int val) {
        Node* newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    // --- Bubble Sort ---
    void bubbleSort() {
        if (!head) return;

        Node* end = nullptr;
        while (end != head) {
            Node* temp = head;
            while (temp->next != end) {
                if (temp->value > temp->next->value) {
                    int t = temp->value;
                    temp->value = temp->next->value;
                    temp->next->value = t;
                }
                temp = temp->next;
            }
            end = temp;
        }
    }

    // --- Insertion Sort ---
    void insertionSort() {
        Node* sorted = nullptr;
        Node* current = head;

        while (current) {
            Node* next = current->next;
            if (!sorted || current->value < sorted->value) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next && temp->next->value < current->value)
                    temp = temp->next;
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list1;
    list1.add(5);
    list1.add(3);
    list1.add(8);
    list1.add(1);
    list1.add(2);

    cout << "Pocetna lista: ";
    list1.print();

    list1.bubbleSort();
    cout << "Po Bubble Sort: ";
    list1.print();

    LinkedList list2;
    list2.add(9);
    list2.add(4);
    list2.add(7);
    list2.add(1);
    list2.add(5);

    cout << "\nPocetna lista (za Insertion Sort): ";
    list2.print();

    list2.insertionSort();
    cout << "Po Insertion Sort: ";
    list2.print();

    return 0;
}
