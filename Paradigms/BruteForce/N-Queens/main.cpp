#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Check if placing a queen at (row, col) is safe
    bool isSafe(int row, int col, vector<string>& board, int n) {
        int duprow = row;
        int dupcol = col;

        // Check left in the same row
        while (col >= 0) {
            if (board[row][col] == 'Q') return false;
            col--;
        }

        row = duprow;
        col = dupcol;
        // Check upper-left diagonal
        while (col >= 0 && row >= 0) {
            if (board[row][col] == 'Q') return false;
            col--;
            row--;
        }

        row = duprow;
        col = dupcol;
        // Check lower-left diagonal
        while (col >= 0 && row < n) {
            if (board[row][col] == 'Q') return false;
            col--;
            row++;
        }

        return true;
    }

    // Backtracking function to place queens
    void checkplaces(int col, int n, vector<vector<string>>& ans, vector<string>& board) {
        // Base condition: all queens are placed
        if (col == n) {
            ans.push_back(board);
            return;
        }

        // Try placing a queen in each row for this column
        for (int row = 0; row < n; row++) {
            if (isSafe(row, col, board, n)) {
                board[row][col] = 'Q';
                checkplaces(col + 1, n, ans, board);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        checkplaces(0, n, ans, board);
        return ans;
    }
};

// Helper function to print solutions
void printSolutions(const vector<vector<string>>& solutions) {
    for (int i = 0; i < solutions.size(); i++) {
        cout << "Solution " << i + 1 << ":\n";
        for (const string& row : solutions[i]) {
            cout << row << "\n";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the value of N for N-Queens problem: ";
    cin >> n;

    Solution sol;
    vector<vector<string>> solutions = sol.solveNQueens(n);

    cout << "Number of solutions: " << solutions.size() << "\n\n";
    printSolutions(solutions);

    return 0;
}
