#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  vector <int> updates;
  for (int i = 1; i <= p; i++) {
    int t, w; cin >> t >> w;
    updates.push_back(w);
  }
  sort(begin(updates), end(updates));
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    x = max(x, y);
    int ans = end(updates) - lower_bound(begin(updates), end(updates), x);
    cout << (ans & 1) << endl;
  }
}
