#pragma GCC optimize("Ofast,no-stack-protector,O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;

int main(){

  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n; cin >> n;
  vector <int> isi(n + 2);
  for(int i = 1;i <= n;i++){
    cin >> isi[i];
    isi[i] -= i + 1;
  }
  vector <int> memo(n + 2, INT_MAX);
  memo[n + 1] = 0;
  for(int i = n;i >= 1;i--) {
    // Cari min
    int hitCount = 0;
    for(int j = i;j <= n;j++){
      hitCount += (isi[j] != -i);
      memo[i] = min(memo[i], memo[j + 1] + hitCount);
    }
  }
  cout << memo[1] << endl;
}