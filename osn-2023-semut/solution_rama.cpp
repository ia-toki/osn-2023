#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> U(M), V(M);
  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    cin >> U[i] >> V[i];
    U[i]--, V[i]--;
    adj[U[i]].emplace_back(V[i]);
    adj[V[i]].emplace_back(U[i]);
  }
  for (int i = 0; i < N; i++) {
    adj[i].emplace_back(-1);
    adj[i].emplace_back(N);
    sort(begin(adj[i]), end(adj[i]));
  }
  const auto getLower = [&](int u, int value, int exclude) {
    auto it = lower_bound(begin(adj[u]), end(adj[u]), value);
    return *prev(it) == exclude ? *prev(prev(it)) : *prev(it);
  };
  const auto getUpper = [&](int u, int value, int exclude) {
    auto it = upper_bound(begin(adj[u]), end(adj[u]), value);
    return *it == exclude ? *next(it) : *it;
  };
  long long ans = 0;
  for (int i = 0; i < N; i++) {
    int l = getLower(i, i, i);
    int r = getUpper(i, i, i);
    ans += 1ll * (i - l) * (r - i);
  }
  for (int i = 0; i < M; i++) {
    int u = U[i], v = V[i];
    int l = max(getLower(u, u, v), getLower(v, v, u));
    int r = min(getUpper(u, u, v), getUpper(v, v, u));
    ans += 2ll * max(0, min(u, v) - l) * max(0, r - max(u, v));
  }
  cout << ans << '\n';
  return 0;
}
