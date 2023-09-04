#include <bits/stdc++.h>
using namespace std;
#define pb push_back
vector <int> edge[100005];

int main() {
  int n, k, q; cin >> n >> k >> q;
  for (int i = 2; i <= n; i++) {
    int p; cin >> p;
    edge[p].pb(i);
  }
  cout << "YA" << endl;
  if (q == 1) {
    for (int i = 1; i <= n; i++) cout << i << endl;
  }
}