#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, P;
  scanf("%d %d", &N, &P);

  vector<int> L, R;
  for (int i = 0; i < P; ++i) {
    int T, W;
    scanf("%d %d", &T, &W);
    if (T == 1) L.push_back(W);
    else if (T == 2) R.push_back(W);
  }
  sort(L.begin(), L.end());
  sort(R.begin(), R.end());
  int Q;
  scanf("%d", &Q);
  for (int j = 0; j < Q; ++j) {
    int X, Y;
    scanf("%d %d", &X, &Y);
    if (X > Y) swap(X, Y);

    int ans = 0;
    ans += L.end() - lower_bound(L.begin(), L.end(), Y);
    ans += upper_bound(R.begin(), R.end(), X) - R.begin();
    printf("%d\n", ans & 1);
  }
  return 0;
}
