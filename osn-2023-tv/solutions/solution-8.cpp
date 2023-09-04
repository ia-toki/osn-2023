#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n, p; cin >> n >> p;
  vector <int> updates[2];
  for (int i = 1; i <= p; i++) {
    int t, w; cin >> t >> w;
    updates[t - 1].push_back(w);
  }
  for (int i = 0; i < 2; i++) {
    sort(begin(updates[i]), end(updates[i]));
  }
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    pair <int, int> ans;
    ans.second = end(updates[0]) - lower_bound(begin(updates[0]), end(updates[0]), x);
    ans.first = upper_bound(begin(updates[1]), end(updates[1]), x) - begin(updates[1]);
    cout << ((ans.first & 1) ^ (ans.second & 1)) << endl;
  }
}
