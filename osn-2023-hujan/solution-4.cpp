#include <bits/stdc++.h>
using namespace std;

#define ll long long

void ans(ll x) {
	cout << x << endl;
	exit(0);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n; cin >> n;
	vector<vector<ll> > v(n, vector<ll>(n));

	ll sm = 0ll;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> v[i][j];
			if (i == j) sm += v[i][j];
		}
	}

	vector<int> perm(n);
	iota(perm.begin(), perm.end(), 0);
	do {
		ll sm2 = 0ll;
		for (int i = 0; i < n; i++) 
			sm2 += v[i][perm[i]];
		if (sm != sm2) ans(0);
	} while (next_permutation(perm.begin(), perm.end()));
	ans(1);
}