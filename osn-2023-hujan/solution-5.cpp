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

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = 0; k < n; k++)
				for (int l = k + 1; l < n; l++)
					if (v[i][k] + v[j][l] != v[i][l] + v[j][k])
						ans(0);
	ans(1);
}