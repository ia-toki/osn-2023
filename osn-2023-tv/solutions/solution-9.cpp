#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  vector <vector <int>> updates;
  updates.push_back(vector<int>(n + 5));
  updates.push_back(vector<int>(n + 5));
  for (int i = 1; i <= p; i++) {
    int t, w; cin >> t >> w;
    updates[t - 1][w] ^= 1;
  }
  for (int j = n; j >= 1; j--) {
    updates[0][j] ^= updates[0][j + 1];
  }
  for (int j = 1; j <= n; j++) {
    updates[1][j] ^= updates[1][j - 1];
  }
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    if (x > y) swap(x, y);
    cout << (updates[0][y]^updates[1][x]) << endl;
  }
}
