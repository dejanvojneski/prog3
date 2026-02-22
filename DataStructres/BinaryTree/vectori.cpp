#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

// ------------------ BT ------------------
void insertBT(vector<int> &v, int val) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == INT_MIN) { v[i] = val; return; }
    }
    v.push_back(val);
}

bool findBT(const vector<int> &v, int val) {
    for (int x : v) if (x != INT_MIN && x == val) return true;
    return false;
}

// ------------------ BST ------------------
void insertBST(vector<int> &v, int val) {
    if (v.empty()) { v.push_back(val); return; }
    int i = 0;
    while (true) {
        if (i >= v.size()) v.resize(i+1, INT_MIN);
        if (v[i] == INT_MIN) { v[i] = val; return; }
        if (val < v[i]) i = 2*i + 1;
        else if (val > v[i]) i = 2*i + 2;
        else return; // веќе постои
    }
}

bool findBST(const vector<int> &v, int val) {
    int i = 0;
    while (i < v.size() && v[i] != INT_MIN) {
        if (v[i] == val) return true;
        if (val < v[i]) i = 2*i + 1;
        else i = 2*i + 2;
    }
    return false;
}

// ------------------ Сума ------------------
int sumTree(const vector<int> &v) {
    int s = 0;
    for (int x : v) if (x != INT_MIN) s += x;
    return s;
}

// ------------------ DFS без рекурзија ------------------
void preorder(const vector<int> &v) {
    if (v.empty() || v[0] == INT_MIN) return;
    stack<int> s; s.push(0);
    while (!s.empty()) {
        int i = s.top(); s.pop();
        if (i >= v.size() || v[i] == INT_MIN) continue;
        cout << v[i] << " ";
        if (2*i+2 < v.size()) s.push(2*i+2); // десен
        if (2*i+1 < v.size()) s.push(2*i+1); // лев
    }
    cout << "\n";
}

void inorder(const vector<int> &v) {
    if (v.empty() || v[0] == INT_MIN) return;
    stack<int> s;
    int curr = 0;
    while (!s.empty() || (curr < v.size() && v[curr] != INT_MIN)) {
        while (curr < v.size() && v[curr] != INT_MIN) {
            s.push(curr);
            curr = 2*curr + 1; // лев
        }
        if (s.empty()) break;
        curr = s.top(); s.pop();
        cout << v[curr] << " ";
        curr = 2*curr + 2; // десен
    }
    cout << "\n";
}

void postorder(const vector<int> &v) {
    if (v.empty() || v[0] == INT_MIN) return;
    stack<int> s1, s2;
    s1.push(0);
    while (!s1.empty()) {
        int i = s1.top(); s1.pop();
        if (i >= v.size() || v[i] == INT_MIN) continue;
        s2.push(i);
        if (2*i+1 < v.size()) s1.push(2*i+1);
        if (2*i+2 < v.size()) s1.push(2*i+2);
    }
    while (!s2.empty()) { cout << v[s2.top()] << " "; s2.pop(); }
    cout << "\n";
}

// ------------------ BFS ------------------
void bfs(const vector<int> &v) {
    if (v.empty() || v[0] == INT_MIN) return;
    queue<int> q; q.push(0);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        if (i >= v.size() || v[i] == INT_MIN) continue;
        cout << v[i] << " ";
        if (2*i+1 < v.size()) q.push(2*i+1);
        if (2*i+2 < v.size()) q.push(2*i+2);
    }
    cout << "\n";
}

// ------------------ main ------------------
int main() {
    int n, x;
    cin >> n;

    vector<int> bt(n, INT_MIN);
    vector<int> bst;
    for (int i = 0; i < n; i++) {
        cin >> x;
        insertBT(bt, x);
        insertBST(bst, x);
    }

    cout << "=== Binary Tree ===\n";
    cout << "Sum: " << sumTree(bt) << "\n";
    cout << "Preorder: "; preorder(bt);
    cout << "Inorder: "; inorder(bt);
    cout << "Postorder: "; postorder(bt);
    cout << "BFS: "; bfs(bt);
    cout << "Find 0..9: ";
    for (int i = 0; i < 10; i++) cout << findBT(bt,i) << " ";
    cout << "\n\n";

    cout << "=== Binary Search Tree ===\n";
    cout << "Sum: " << sumTree(bst) << "\n";
    cout << "Preorder: "; preorder(bst);
    cout << "Inorder: "; inorder(bst);
    cout << "Postorder: "; postorder(bst);
    cout << "BFS: "; bfs(bst);
    cout << "Find 0..9: ";
    for (int i = 0; i < 10; i++) cout << findBST(bst,i) << " ";
    cout << "\n";

    return 0;
}
