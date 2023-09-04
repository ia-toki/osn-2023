#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    A[i]--;
  }
  vector<int> dp(N + 1, 1e9);
  vector<pair<int, int>> last(2 * N + 1, {-1e9, -1});
  dp[0] = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] > i) {
      dp[i + 1] = dp[i] + 1;
    } else if (A[i] > 0) {
      if (auto p = last[N + A[i] - i]; i - p.first - 1 <= A[i]) {
        dp[i + 1] = p.second + i - p.first - 1;
      } else {
        dp[i + 1] = dp[i - A[i]] + A[i];
      }
    } else {
      dp[i + 1] = dp[i];
    }
    last[N + A[i] - i] = {i, dp[i + 1]};
    dp[i + 1] = min(dp[i + 1], dp[i] + 1);
  }
  cout << dp[N] << '\n';
  return 0;
}
