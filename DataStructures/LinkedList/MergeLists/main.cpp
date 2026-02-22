#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) {
        val=v;
        next=nullptr;
    }
};

void addToEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

Node* merge(Node* head1, Node* head2) {
    if (!head1) return head2;
    Node* temp = head1;
    while (temp->next)
        temp = temp->next;
    temp->next = head2;
    return head1;
}

Node* sortList(Node* head) {
    if (!head || !head->next) return head;
    Node* sorted = nullptr;

    Node* current = head;
    while (current) {
        Node* next = current->next;
        if (!sorted || current->val < sorted->val) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next && temp->next->val < current->val)
                temp = temp->next;
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

void removeDuplicates(Node* head) {
    Node* current = head;
    while (current && current->next) {
        if (current->val == current->next->val) {
            Node* dup = current->next;
            current->next = current->next->next;
            delete dup;
        } else {
            current = current->next;
        }
    }
}

void printList(Node* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* list1 = nullptr;
    Node* list2 = nullptr;

    addToEnd(list1, 3);
    addToEnd(list1, 1);
    addToEnd(list1, 4);

    addToEnd(list2, 4);
    addToEnd(list2, 2);
    addToEnd(list2, 5);

    Node* merged = merge(list1, list2);
    merged=sortList(merged);
    removeDuplicates(merged);

    printList(merged);
    return 0;
}
