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
  if (k > n * (n - 1) / 2) answer({});
  LL inversion = 0;
  vector <LL> ans;
  for (int i = n; i >= 1; i--) {
    LL nextInversion = i - 1;
    if (inversion + nextInversion > k) {
      // insert here
      LL remainingSwap = k - inversion;
      for (int j = 1; j <= i; j++) {
        ans.push_back(j);
      }
      for (int j = n - 1; j >= 0; j--) {
        if (remainingSwap == 0) break;
        remainingSwap--;
        swap(ans[j], ans[j - 1]);
      }
      break;
    } else {
      ans.push_back(i);
    }
    inversion += nextInversion;
  }
  answer(ans);
}