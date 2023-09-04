#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  vector <vector <int>> grid(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= p; i++) {
    int t, w; cin >> t >> w;
    if (t == 1) {
      for (int x = 1; x <= w; x++) {
        for (int y = 1; y <= w; y++) {
          grid[x][y] ^= 1;
        }
      }
    } else {
      for (int x = w; x <= n; x++) {
        for (int y = w; y <= n; y++) {
          grid[x][y] ^= 1;
        }
      }
    }
  }
  int q; cin >> q;
  for(int i = 1;i <= q;i++){
    int x, y; cin >> x >> y;
    cout << grid[x][y] << endl;
  }
}
