#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint MOD = 1e9 + 7;

int main() {
  int N, P;
  cin >> N >> P;
  vector<int> a, b;
  for (int i = 0; i < P; i++) {
    int t, w;
    cin >> t >> w;
    if (t == 1) {
      a.emplace_back(w);
    } else {
      b.emplace_back(N - w + 1);
    }
  }
  auto calc = [&](const vector<int> &v, int x, int y) -> int {
    return end(v) - lower_bound(begin(v), end(v), max(x, y));
  };
  int Q;
  cin >> Q;
  while (Q--) {
    int x, y;
    cin >> x >> y;
    cout << (calc(a, x, y) + calc(b, N - x + 1, N - y + 1)) % 2 << '\n';
  }
  return 0;
}
