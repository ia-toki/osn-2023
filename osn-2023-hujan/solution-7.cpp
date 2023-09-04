#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n; cin >> n;

	ll ans = 1ll;
	for (int i = 0; i < n; i++) {
		for (int x, j = 0; j < n; j++) {
			cin >> x;
			if (i == j) ans = (ans * 1ll * (x + 1)) % mod;
		}
	}
	cout << ans << endl;
}