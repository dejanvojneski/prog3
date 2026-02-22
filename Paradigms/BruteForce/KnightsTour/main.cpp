#include <bits/stdc++.h>
using namespace std;

int count_possible_onward_moves(vector<vector<int>> &board, int x_moves[], int y_moves[], int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int next_x = x + x_moves[i];
        int next_y = y + y_moves[i];
        if (next_x >= 0 && next_x < 8 && next_y >= 0 && next_y < 8 && board[next_x][next_y] == 0)
            count++;
    }
    return count;
}

vector<tuple<int,int,int>> get_best_moves(vector<vector<int>> &board, int x_moves[], int y_moves[], int x, int y) {
    vector<tuple<int,int,int>> best_moves;
    for (int i = 0; i < 8; i++) {
        int next_x = x + x_moves[i];
        int next_y = y + y_moves[i];
        if (next_x >= 0 && next_x < 8 && next_y >= 0 && next_y < 8 && board[next_x][next_y] == 0)
            best_moves.push_back({next_x, next_y, count_possible_onward_moves(board, x_moves, y_moves, next_x, next_y)});
    }

    // Sort ascending by onward moves (Warnsdorff's heuristic)
    sort(best_moves.begin(), best_moves.end(), [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });

    return best_moves;
}

bool warnsdorff_track_moves(vector<vector<int>> &board, int x, int y, int move_count) {
    if (move_count > 64) return true; // All squares visited

    int x_moves[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y_moves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    vector<tuple<int,int,int>> moves = get_best_moves(board, x_moves, y_moves, x, y);

    for (auto &move : moves) {
        int next_x = get<0>(move);
        int next_y = get<1>(move);
        board[next_x][next_y] = move_count;
        if (warnsdorff_track_moves(board, next_x, next_y, move_count + 1)) return true;
        board[next_x][next_y] = 0; // backtrack
    }

    return false; // Dead end
}

int main() {
    vector<vector<int>> board(8, vector<int>(8, 0));
    board[0][0] = 1; // Starting position

    if (warnsdorff_track_moves(board, 0, 0, 2)) {
        cout << "Knight's Tour completed:\n";
        for (auto &row : board) {
            for (int val : row) cout << setw(2) << val << " ";
            cout << "\n";
        }
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
