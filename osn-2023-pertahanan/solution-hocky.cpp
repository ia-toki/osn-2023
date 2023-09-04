#include <bits/stdc++.h>
using namespace std;

namespace segmentTree {
vector <int> segt;
void update(int kiri, int kanan, int idx, int target, int val) {
  if (target < kiri || kanan < target) return;
  if (kiri == kanan) {
    segt[idx] = val;
    return;
  }
  int mid = (kiri + kanan) >> 1;
  update(kiri, mid, idx * 2, target, val);
  update(mid + 1, kanan, idx * 2 + 1, target, val);
  segt[idx] = min(segt[idx * 2], segt[idx * 2 + 1]);
}

int query(int kiri, int kanan, int idx, int l, int r) {
  if (r < kiri || kanan < l) return INT_MAX;
  if (l <= kiri && kanan <= r) {
    return segt[idx];
  }
  int mid = (kiri + kanan) >> 1;
  int leftValue = query(kiri, mid, idx * 2, l, r);
  int rightValue = query(mid + 1, kanan, idx * 2 + 1, l, r);
  return min(leftValue, rightValue);
}
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n; cin >> n;
  segmentTree::segt.resize(n * 4 + 20);
  vector <int> isi(n + 2);
  vector <vector <int> > bucket(n + 2);
  for (int i = 1; i <= n; i++) {
    cin >> isi[i];
    isi[i] -= i + 1;
    isi[i] = -isi[i];
    if (1 <= isi[i] && isi[i] <= n && isi[i] <= i) {
      bucket[isi[i]].push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) bucket[i].push_back(n + 1);
  vector <int> memo(n + 2, INT_MAX);
  memo[n + 1] = 0;
  segmentTree::update(1, n + 1, 1, n + 1, n + 1);
  auto checkRange = [&](int pos, int l, int r, int safeCount) {

    if (l > r) return;
    int bestCost = segmentTree::query(1, n + 1, 1, l + 1, r + 1);
    int bestDp = bestCost - pos - safeCount;
    memo[pos] = min(memo[pos], bestDp);
  };
  for (int i = n; i >= 1; i--) {
    checkRange(i, i, bucket[i][0] - 1, 0);
    for (int j = 0; j < (int)(bucket[i].size()) - 1; j++) {
      // Query for the comparator
      checkRange(i, bucket[i][j], bucket[i][j + 1] - 1, j + 1);
    }
    segmentTree::update(1, n + 1, 1, i, memo[i] + i);
    // cout << i << " " << memo[i] << endl;
  }
  cout << memo[1] << endl;
}