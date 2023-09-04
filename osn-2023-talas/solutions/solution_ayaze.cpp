#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, q;
long long k;
vector<int> chld[N];

int height[N], longestChild[N];
int endIndex;
int ans[N];

void read() {
  scanf("%d %lld %d", &n, &k, &q);
  for (int i = 2 ; i <= n ; i++) {
    int parent; scanf("%d", &parent);
    chld[parent].push_back(i);
  }
}

void prepare() {
  for (int i = n ; i >= 1 ; i--) {
    height[i] = 1;
    for (int nex : chld[i]) {
      if (height[nex] + 1 > height[i]) {
        height[i] = height[nex] + 1;
        longestChild[i] = nex;
      }
    }
  }

  endIndex = n;
}

vector<int> greedyPermute(int length, long long swapCount) {
  int x = 1;
  while (1ll * x * (x - 1) / 2 < swapCount) x++;

  int leftover = swapCount - 1ll * (x - 1) * (x - 2) / 2;
  vector<int> ret(length);
  for (int i = 0, j = x - 1 ; i + 1 < x ; i++, j--) {
    if (j == x - 1 - leftover) j--;
    ret[i] = j;
  }
  ret[x - 1] = x - 1 - leftover;
  iota(ret.begin() + x, ret.end(), x);

  reverse(ret.begin(), ret.end());
  return ret;
}

void dfs(int now) {
  int length = height[now];
  long long maxSwap = 1ll * length * (length - 1) / 2;
  long long usedSwap = min(maxSwap, k);

  vector<int> perm = greedyPermute(length, usedSwap);
  k -= usedSwap;
  int startIndex = endIndex - length + 1;
  endIndex -= length;

  for (int i = now, j = 0 ; i > 0 ; i = longestChild[i], j++) {
    ans[i] = perm[j] + startIndex;
    for (int nex : chld[i]) {
      if (nex == longestChild[i]) continue;
      dfs(nex);
    }
  }
}

int main() {
  read();
  prepare();
  dfs(1);

  if (k > 0) {
    ans[1] = -1;
    n = 1;
  }
  
  if (ans[1] == -1) {
    cout << "TIDAK" << endl;
    return 0;
  }

  cout << "YA" << endl;

  if (q == 1) {
    for (int i = 1 ; i <= n ; i++) {
      printf("%d%c", n - ans[i] + 1, " \n"[i == n]);
    }
  }
  return 0;
}
