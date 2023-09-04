#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll ans = 0;
vector <vector<int>> edge;
int dfs(int pos) {
  int height = 0;
  for (auto &nx : edge[pos]) {
    height = max(height, dfs(nx));
  }
  ans += height;
  ++height;
  return height;
}

int main() {
  cin >> n;
  ll k; cin >> k;
  int q; cin >> q;
  edge.resize(n + 1);
  for(int i = 2;i <= n;i++){
    int p; cin >> p;
    edge[p].push_back(i);
  }
  dfs(1);
  cout << (k <= ans ? "YA" : "TIDAK") << endl;
}