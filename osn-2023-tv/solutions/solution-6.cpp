#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  int t1, w; cin >> t1 >> w;
  int t2; cin >> t2 >> w;
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    if (x == y && x == w) {
      cout << 0 << endl;
    } else if (max(x, y) <= w && min(x, y) < w) {
      cout << 1 << endl;
    } else if (max(x, y) > w && min(x, y) >= w) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
}