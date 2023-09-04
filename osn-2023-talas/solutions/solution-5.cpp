#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
  int n; cin >> n;
  ll k; cin >> k;
  int q; cin >> q;
  ll length1 = 0;
  ll length2 = 0;
  ll intersection = 0;
  for(int i = 2;i <= n;i++){
    int p; cin >> p;
    if(p != i - 1){
      intersection = p;
      length1 = i - 1 - p;
      length2 = n - i + 1;
    }
  }
  ll ans = (length1 * (length1 - 1) / 2) + (length2 * (length2 - 1) / 2);
  for(int i = 1;i <= intersection;i++){
    ans += max(length1, length2) + i - 1;
  }
  cout << (k <= ans ? "YA" : "TIDAK") << endl;
}