#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
LL k;
int q;
vector<vector<int>> edge;
namespace solver {
vector <int> ans;
vector <int> val;
int solve() {
  int swapCount = 0;
  for (int i = n; i >= 1; i--) {
    int current = i;
    // Find minimum untuk anak anaknya
    do {
      int currentMinimum = current;
      for (auto &nx : edge[current]) {
        if (val[nx - 1] < val[currentMinimum - 1]) {
          currentMinimum = nx;
        }
      }
      if (currentMinimum == current) break;
      swap(val[currentMinimum - 1], val[current - 1]);
      swapCount++;
      current = currentMinimum;
    } while (1);
  }
  for (int i = 1; i <= n; i++) {
    for (auto &nx : edge[i]) {
      assert(val[i - 1] < val[nx - 1]);
    }
  }
  return swapCount;
}
}

void answer(const vector <int> ans) {
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
  cin >> n >> k >> q;
  edge.resize(n + 1);
  for (int i = 2; i <= n; i++) {
    int p; cin >> p;
    edge[p].push_back(i);
  }
  vector <int> perm(n);
  iota(begin(perm), end(perm), 1);
  do {
    solver::ans = solver::val = perm;
    if (solver::solve() == k) answer(perm);
  } while (next_permutation(begin(perm), end(perm)));
  answer({});
}