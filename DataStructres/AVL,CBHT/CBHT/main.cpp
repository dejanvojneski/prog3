#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
using namespace std;

struct Node {
    string word;
    Node *next;
    Node() {
        word = "";
        next = nullptr;
    }
    ~Node() {
        delete next;
    }
};

// ======================
// HASH FUNCTIONS
// ======================

int hF_WordLength(const string &s) { // mode 0
    return s.size();
}

int hF_CharSum(const string &s) { // mode 1
    int z = 0;
    for (char c : s) {
        z += tolower(c) - 'a' + 1;
    }
    return z;
}

int hF_FirstChar(const string &s) { // mode 2
    return tolower(s[0]) - 'a';
}

int hF_FirstTwoChar(const string &s) { // mode 3
    char a = tolower(s[0]);
    char b = (s.size() > 1 ? tolower(s[1]) : 'a');
    return (a - 'a') * 26 + (b - 'a');
}

// ======================
// INSERT FUNCTION
// ======================

void insertWord(map<int, Node> &m, string &word, int mode = 0) {
    int p = 0;

    if (mode == 0) p = hF_WordLength(word);
    else if (mode == 1) p = hF_CharSum(word);
    else if (mode == 2) p = hF_FirstChar(word);
    else p = hF_FirstTwoChar(word);

    Node *t = &m[p];

    while (t->word != "") {
        if (t->next) t = t->next;
        else t->next = new Node;
    }

    t->word = word;
}

// ======================
// PRINT FUNCTIONS
// ======================

void printTable(const map<int, Node> &m) {
    for (auto e : m) {
        cout << "[" << e.first << "] ";
        Node *t = &((Node&)e.second);
        while (t) {
            if (t->word != "") cout << t->word << " ";
            t = t->next;
        }
        cout << "\n";
    }
}

void printTable(const map<int, Node> &m, ostream &out) {
    for (auto e : m) {
        Node *t = &((Node&)e.second);
        while (t) {
            if (t->word != "") out << t->word << " ";
            t = t->next;
        }
        out << "\n";
    }
}

// ======================
// MAIN
// ======================

int main() {

    map<int, Node> table;
    ifstream file("words.txt");

    if (!file) {
        cout << "Cannot open words.txt\n";
        return 0;
    }

    cout << "Choose hash function:\n";
    cout << "0 - by word length\n";
    cout << "1 - by char sum (a=1...z=26)\n";
    cout << "2 - by first char\n";
    cout << "3 - by first two characters\n";

    int mode;
    cin >> mode;

    string word;

    while (file >> word) {
        insertWord(table, word, mode);
    }

    printTable(table);

    return 0;
}
