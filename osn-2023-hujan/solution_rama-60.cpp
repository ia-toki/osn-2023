#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint MOD = 1e9 + 7;

int main() {
  int N;
  cin >> N;
  vector<vector<int>> A(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A[i][j];
    }
  }
  lint ans1 = 1, ans0 = 1;
  vector<vector<int>> vis(2, vector<int>(N));
  vector<vector<lint>> color(2, vector<lint>(N));
  for (int ss = 0; ss < 2; ss++) {
    for (int s = 0; s < N; s++) {
      if (vis[ss][s]) {
        continue;
      }
      vector<pair<int, int>> que;
      auto relax = [&](int xx, int x, lint c) {
        if (!vis[xx][x]) {
          vis[xx][x] = 1;
          color[xx][x] = c;
          que.emplace_back(xx, x);
        } else if (color[xx][x] != c) {
          cout << "0\n";
          exit(0);
        }
      };
      relax(ss, s, 0);
      for (int q = 0; q < int(que.size()); q++) {
        auto [t, u] = que[q];
        if (t == 0) {
          for (int i = 0; i < N; i++) {
            if (A[u][i] != -1) {
              relax(1 - t, i, A[u][i] - color[t][u]);
            }
          }
        } else {
          for (int i = 0; i < N; i++) {
            if (A[i][u] != -1) {
              relax(1 - t, i, A[i][u] - color[t][u]);
            }
          }
        }
      }
      if (que.size() == 1) {
        cout << "-1\n";
        return 0;
      }
      lint mn = 1e18, mx = -1e18;
      for (auto [t, u] : que) {
        if (t == 0) {
          mx = max(mx, -color[t][u]);
        } else {
          mn = min(mn, color[t][u]);
        }
      }
      ans1 *= (mn - mx + 1) % MOD;
      ans0 *= (mn - mx) % MOD;
      ans1 %= MOD;
      ans0 %= MOD;
    }
  }
  lint ans = ((ans1 - ans0) % MOD + MOD) % MOD;
  cout << ans << '\n';
  return 0;
}
