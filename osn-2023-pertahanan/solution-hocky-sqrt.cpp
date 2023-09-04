#include <bits/stdc++.h>
using namespace std;


namespace sqrtBlock {

const int BLOCKS = 500;
inline int ceil(int a, int b) { return a / b + !!(a % b); }
inline int getStartIndex(int i) { return i * BLOCKS; }
inline int getLBIndex(int pos) { return pos / BLOCKS; }
inline int getUBIndex(int pos) { return ceil(pos, BLOCKS); }

vector <int> blockManual;
vector <int> sqrtBlocks;
int N;
void init(int n) {
  N = n;
  blockManual.resize(n + 5, INT_MAX);
  sqrtBlocks.resize(n / BLOCKS + 5, INT_MAX);
}

void update(int pos, int val) {
  int segmentIndex = getLBIndex(pos);
  sqrtBlocks[segmentIndex] = min(sqrtBlocks[segmentIndex], val);
  blockManual[pos] = min(blockManual[pos], val);
}

int query(int l, int r) {
  int st = getUBIndex(l);
  int ed = getLBIndex(r) - 1;
  int ret = INT_MAX;
  for (int i = st; i <= ed; i++) ret = min(ret, sqrtBlocks[i]);
  int tmpEnd = min(r, min(N, getStartIndex(st)));
  for (int i = l; i <= tmpEnd; i++) ret = min(ret, blockManual[i]);
  for (int i = max(l, getStartIndex(ed)); i <= r; i++) ret = min(ret, blockManual[i]);
  return ret;
}
}

int main() {

  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n; cin >> n;
  sqrtBlock::init(n + 3);
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
  sqrtBlock::update(n + 1, n + 1);
  auto checkRange = [&](int pos, int l, int r, int safeCount) {

    if (l > r) return;
    int bestCost = sqrtBlock::query(l + 1, r + 1);
    int bestDp = bestCost - pos - safeCount;
    memo[pos] = min(memo[pos], bestDp);
  };
  for (int i = n; i >= 1; i--) {
    checkRange(i, i, bucket[i][0] - 1, 0);
    for (int j = 0; j < (int)(bucket[i].size()) - 1; j++) {
      // Query for the comparator
      checkRange(i, bucket[i][j], bucket[i][j + 1] - 1, j + 1);
    }
    sqrtBlock::update(i, memo[i] + i);
    // cout << i << " " << memo[i] << endl;
  }
  cout << memo[1] << endl;
}