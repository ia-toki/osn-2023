#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  int t, w; cin >> t >> w;
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    if(t == 1) cout << (max(x, y) <= w) << endl;
    if(t == 2) cout << (min(x, y) >= w) << endl;
  }
}