#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  long long K;
  cin >> N >> K >> Q;
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    int p;
    cin >> p;
    adj[--p].emplace_back(i);
  }
  vector<pair<int, int>> deep(N);
  for (int i = N - 1; i >= 0; i--) {
    deep[i] = {0, i};
    for (auto j : adj[i]) {
      deep[i] = max(deep[i], {deep[j].first + 1, j});
    }
  }
  auto construct = [](int n, long long k) -> vector<int> {
    vector<int> ret;
    vector<int> used(n);
    int iter = n - 1;
    for (int iter = n - 1; iter >= 0; iter--) {
      if (iter <= k) {
        k -= iter;
        used[iter] = 1;
        ret.emplace_back(iter);
      }
    }
    assert(k == 0);
    for (int i = 0; i < n; i++) {
      if (used[i] == 0) {
        ret.emplace_back(i);
      }
    }
    assert(ret.size() == n);
    return ret;
  };
  int ctr = 0;
  vector<int> ans(N);
  auto dfs = [&](auto self, int u) -> void {
    vector<int> chain;
    for (int cur = u; chain.empty() || chain.back() != cur;
         cur = deep[cur].second) {
      chain.emplace_back(cur);
    }
    int sz = chain.size();
    long long s = 1ll * sz * (sz - 1) / 2;
    vector<int> p;
    if (K <= s) {
      p = construct(sz, K);
      K = 0;
    } else {
      p = construct(sz, s);
      K -= s;
    }
    for (int i = 0; i < sz; i++) {
      ans[chain[i]] = ctr + p[i];
    }
    ctr += sz;
    for (auto cur : chain) {
      for (auto j : adj[cur]) {
        if (j != deep[cur].second) {
          self(self, j);
        }
      }
    }
  };
  dfs(dfs, 0);
  if (K != 0) {
    cout << "TIDAK\n";
  } else {
    cout << "YA\n";
    for (int i = 0; Q == 1 && i < N; i++) {
      cout << ans[i] + 1 << " \n"[i + 1 == N];
    }
  }
  return 0;
}
