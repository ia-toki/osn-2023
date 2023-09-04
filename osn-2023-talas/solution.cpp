#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int kMaxN = 100000;

int P[kMaxN];
vector<int> adj[kMaxN];
int height[kMaxN];
int deepest[kMaxN];

int main() {
	int N; long long K; int Q;
  scanf("%d %lld %d", &N, &K, &Q);
  for (int i = 1; i < N; ++i) {
    scanf("%d", &P[i]);
    adj[--P[i]].push_back(i);
  }

  for (int i = N - 1; i >= 0; --i) {
    deepest[i] = -1; height[i] = 0;
    for (int j : adj[i]) {
      if (height[i] < height[j] + 1) {
        deepest[i] = j;
        height[i] = height[j] + 1;
      }
    }
  }

  int idx = 0;
  vector<bool> chained(N);
  vector<int> ans(N);
  for (int i = 0; i < N; ++i) {
    if (chained[i]) continue;
    vector<int> chain;
    for (int j = i; j != -1; j = deepest[j]) {
      chain.push_back(j);
      chained[j] = true;
    }
    int len = chain.size();

    vector<int> nums(len);
    for (int k = 0; k < len; ++k) {
      nums[k] = ++idx;
    }
    int j = len - 1;
    while (j > 0 && 1LL * (len - j) * (len - j + 1) / 2 <= K) --j;
    reverse(nums.begin() + j, nums.end());
    K -= 1LL * (len - j) * (len - j - 1) / 2;

    if (j > 0) while (K > 0) swap(nums[j - 1], nums[j]), --K, ++j;
    for (int k = 0; k < len; ++k) {
      ans[chain[k]] = nums[k];
    }
  }

  if (K > 0) return 0 * printf("TIDAK\n");
  printf("YA\n");
  if(Q == 0) return 0;
  for (int i = 0; i < N; ++i) {
    if(i < N - 1) printf("%d ", ans[i]);
    else printf("%d", ans[i]);
  }
  printf("\n");
  return 0;
}
