#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  vector <vector <int>> grid(n + 2, vector<int>(n + 2));
  for (int i = 1; i <= p; i++) {
    int t, w; cin >> t >> w;
    if (t == 1) {
      for(int x = 1;x <= w;x++){
        grid[x][1] ^= 1;
        grid[x][w + 1] ^= 1;
      }
    } else {
      for (int x = w; x <= n; x++) {
        grid[x][w] ^= 1;
        grid[x][n + 1] ^= 1;
      }
    }
  } 
  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= n;j++){
      grid[i][j] ^= grid[i][j - 1];
    }
  }
  int q; cin >> q;
  for(int i = 1;i <= q;i++){
    int x, y; cin >> x >> y;
    cout << grid[x][y] << endl;
  }
}

