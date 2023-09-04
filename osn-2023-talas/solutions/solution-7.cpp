#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, k, q;

void answer(const vector <LL> ans) {
  if (ans.empty()) {
    cout << "TIDAK" << endl;
    exit(0);
  }
  cout << "YA" << endl;
  if (q == 0) exit(0);
  for (auto &element : ans) cout << element << " ";
  cout << endl;
  exit(0);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k >> q;
  vector <LL> ans(n);
  iota(begin(ans), end(ans), 1);
  for (int i = n; i >= 1; i--) {
    for (int j = n - 1; j >= n - i + 1; j--) {
      if (k == 0) break;
      k--;
      swap(ans[j], ans[j - 1]);
    }
  }
  if (k == 0) answer(ans);
  else answer({});
}