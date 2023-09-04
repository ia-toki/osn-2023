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

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> v[i][j];
		}
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (v[i][j] + v[i + 1][j + 1] != v[i][j + 1] + v[i + 1][j])
				ans(0);
		}
	}
	ans(1);
}