#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int funk(const int c, const vector<int>& coins) {
    vector<int> change(c+1, INT_MAX);
    change[0]=0;
    for (int i=1; i<=c; i++) {
        for (const auto e : coins) {
            if (i-e>=0 && change[i-e]!=INT_MAX) {
                change[i]=min(change[i], change[i-e]+1);
            }
        }
    }
    return change[c];
}

int main() {
    vector<int> coins{1, 3, 11, 21};
    vector<int> v{124, 226, 121};
    for (const auto c: v) cout << funk(c, coins) << "\n";
    return 0;
}