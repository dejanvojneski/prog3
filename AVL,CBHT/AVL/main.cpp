#include <iostream>
#include <climits>

using namespace std;

struct Node{
    int val;
    Node *left;
    Node *right;
    int height;
    Node(const int val=INT_MIN) {
        this->val = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int getHeight(Node* n){
    if(n == nullptr) return 0;
    return n->height;
}

void computeHeightFromChildren(Node* current){
    if(current == nullptr) return;
    int leftH = getHeight(current->left);
    int rightH = getHeight(current->right);
    if(leftH > rightH) current->height = leftH + 1;
    else current->height = rightH + 1;
}

Node* rightRotate(Node* current){
    if(current == nullptr) return current;
    if(current->left == nullptr) return current;

    Node* newRoot = current->left;
    current->left = newRoot->right;
    newRoot->right = current;

    computeHeightFromChildren(current);
    computeHeightFromChildren(newRoot);

    return newRoot;
}

Node* leftRotate(Node* current){
    if(current == nullptr) return current;
    if(current->right == nullptr) return current;

    Node* newRoot = current->right;
    current->right = newRoot->left;
    newRoot->left = current;

    computeHeightFromChildren(current);
    computeHeightFromChildren(newRoot);

    return newRoot;
}

Node* leftRightRotate(Node* current){
    if(current == nullptr) return current;
    current->left = leftRotate(current->left);
    return rightRotate(current);
}

Node* rightLeftRotate(Node* current){
    if(current == nullptr) return current;
    current->right = rightRotate(current->right);
    return leftRotate(current);
}

Node* balance(Node* current){
    if(current == nullptr) return current;

    computeHeightFromChildren(current);

    int leftH = getHeight(current->left);
    int rightH = getHeight(current->right);

    if(leftH > rightH + 1){
        int leftleftH = 0;
        int leftrightH = 0;
        if(current->left != nullptr){
            if(current->left->left != nullptr) leftleftH = getHeight(current->left->left);
            else leftleftH = 0;
            if(current->left->right != nullptr) leftrightH = getHeight(current->left->right);
            else leftrightH = 0;
        }
        if(leftleftH >= leftrightH) return rightRotate(current);
        return leftRightRotate(current);
    }

    if(rightH > leftH + 1){
        int rightleftH = 0;
        int rightrightH = 0;
        if(current->right != nullptr){
            if(current->right->left != nullptr) rightleftH = getHeight(current->right->left);
            else rightleftH = 0;
            if(current->right->right != nullptr) rightrightH = getHeight(current->right->right);
            else rightrightH = 0;
        }
        if(rightrightH >= rightleftH) return leftRotate(current);
        else return rightLeftRotate(current);
    }

    return current;
}

Node* insert(Node* root, const int value){
    if(root == nullptr || root->val == INT_MIN) return new Node(value);
    if(value < root->val) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    return balance(root);
}

void preorder(Node *r) {
    if(r == nullptr) return;
    cout << r->val << " h=" << r->height << "\n";
    preorder(r->left);
    preorder(r->right);
}

void delTree(Node *r) {
    if (r->left) delTree(r->left);
    if (r->right) delTree(r->right);
    delete r;
}

int main() {
    Node* root;
    int values[] = {30, 20, 10, 25, 40, 50, 45};
    for(int v : values){
        root = insert(root, v);
    }
    preorder(root);
    cout << endl;
    delTree(root);

    return 0;
}