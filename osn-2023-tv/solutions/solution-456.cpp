#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  vector <pair<int, int>> queries;
  for (int i = 1; i <= p; i++) {
    int t, w; cin >> t >> w;
    if (t == 1) {
      queries.emplace_back(1, w);
    } else {
      queries.emplace_back(w, n);
    }
  }
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    int ans = 0;
    for (auto query : queries) {
      if (query.first <= x && x <= query.second) {
        if (query.first <= y && y <= query.second) {
          ans ^= 1;
        }
      }
    }
    cout << ans << endl;
  }
}
