#include <iostream>
using namespace std;

// =============================
// Node for BT / BST
// =============================
struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) : val(v), left(NULL), right(NULL) {}
};

// =============================
// Insert BST
// =============================
Node* insertBST(Node* root, int v) {
    if (!root) return new Node(v);

    if (v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);

    return root;
}

// =============================
// FIND
// =============================
bool find(Node* root, int x) {
    if (!root) return false;
    if (root->val == x) return true;
    if (x < root->val) return find(root->left, x);
    return find(root->right, x);
}

// =============================
// DFS RECURSIVE
// =============================
void preorder(Node* r) {
    if (!r) return;
    cout << r->val << " ";
    preorder(r->left);
    preorder(r->right);
}

void inorder(Node* r) {
    if (!r) return;
    inorder(r->left);
    cout << r->val << " ";
    inorder(r->right);
}

void postorder(Node* r) {
    if (!r) return;
    postorder(r->left);
    postorder(r->right);
    cout << r->val << " ";
}

// =============================
// STACK implemented ONLY with pointers
// =============================
struct StackNode {
    Node* treeNode;
    StackNode* next;
    StackNode(Node* t) : treeNode(t), next(NULL) {}
};

void push(StackNode*& top, Node* t) {
    StackNode* s = new StackNode(t);
    s->next = top;
    top = s;
}

Node* pop(StackNode*& top) {
    if (!top) return NULL;
    Node* t = top->treeNode;
    StackNode* old = top;
    top = top->next;
    delete old;
    return t;
}

bool emptyStack(StackNode* top) {
    return top == NULL;
}

// =============================
// QUEUE implemented ONLY with pointers
// =============================
struct QNode {
    Node* treeNode;
    QNode* next;
    QNode(Node* t) : treeNode(t), next(NULL) {}
};

struct Queue {
    QNode* front = NULL;
    QNode* back = NULL;

    void push(Node* t) {
        QNode* q = new QNode(t);
        if (!back) {
            front = back = q;
        } else {
            back->next = q;
            back = q;
        }
    }

    Node* pop() {
        if (!front) return NULL;
        Node* t = front->treeNode;
        QNode* old = front;
        front = front->next;
        if (!front) back = NULL;
        delete old;
        return t;
    }

    bool empty() {
        return front == NULL;
    }
};

// =============================
// DFS WITHOUT RECURSION
// =============================
void preorderNR(Node* root) {
    if (!root) return;

    StackNode* st = NULL;
    push(st, root);

    while (!emptyStack(st)) {
        Node* n = pop(st);
        cout << n->val << " ";

        if (n->right) push(st, n->right);
        if (n->left)  push(st, n->left);
    }
}

void inorderNR(Node* root) {
    StackNode* st = NULL;
    Node* cur = root;

    while (cur || !emptyStack(st)) {
        while (cur) {
            push(st, cur);
            cur = cur->left;
        }

        cur = pop(st);
        cout << cur->val << " ";
        cur = cur->right;
    }
}

void postorderNR(Node* root) {
    if (!root) return;

    StackNode *st1 = NULL, *st2 = NULL;

    push(st1, root);

    while (!emptyStack(st1)) {
        Node* n = pop(st1);
        push(st2, n);

        if (n->left) push(st1, n->left);
        if (n->right) push(st1, n->right);
    }

    while (!emptyStack(st2)) {
        cout << pop(st2)->val << " ";
    }
}

// =============================
// BFS WITHOUT RECURSION
// =============================
void BFS(Node* root) {
    if (!root) return;

    Queue q;
    q.push(root);

    while (!q.empty()) {
        Node* n = q.pop();
        cout << n->val << " ";

        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

// =============================
// SUM OF ALL NODES
// =============================
int sumTree(Node* root) {
    if (!root) return 0;
    return root->val + sumTree(root->left) + sumTree(root->right);
}

// =============================
// MAIN
// =============================
int main() {
    Node* root = NULL;

    int arr[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int x : arr) root = insertBST(root, x);

    cout << "Recursive Preorder: "; preorder(root); cout << "\n";
    cout << "Recursive Inorder: "; inorder(root); cout << "\n";
    cout << "Recursive Postorder: "; postorder(root); cout << "\n";

    cout << "Non-Recursive Preorder: "; preorderNR(root); cout << "\n";
    cout << "Non-Recursive Inorder: "; inorderNR(root); cout << "\n";
    cout << "Non-Recursive Postorder: "; postorderNR(root); cout << "\n";

    cout << "BFS: "; BFS(root); cout << "\n";

    cout << "Find 7 -> " << (find(root, 7) ? "YES" : "NO") << "\n";
    cout << "Sum = " << sumTree(root) << "\n";
}
