#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


int main() {
  LL n, k; cin >> n >> k;
  if(k <= n * (n - 1) / 2) {
    cout << "YA" << endl;
  } else {
    cout << "TIDAK" << endl;
  }
}