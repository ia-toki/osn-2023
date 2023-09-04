#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;

void ans(ll x) {
	cout << x << endl;
	exit(0);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n; cin >> n;

	vector<vector<int> > v(n, vector<int>(n));
	vector<int> sumcol(n, 0), sumrow(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> v[i][j];
			sumrow[i] += v[i][j];
			sumcol[j] += v[i][j];
		}
	}
	
	for (int i = 0; i < n; i++) {
		// sumrow/sumcol = -n -> all values in row/col are -1
		if (sumrow[i] + n == 0) ans(-1);
		if (sumcol[i] + n == 0) ans(-1);
	}

	int msk = 1;
	for (int i = 0; i < n; i++) msk *= 8;

	set<vector<vector<int> > > possible;
	for (int tp = 0; tp < msk; tp++) {
		vector<int> row(n), col(n, -1);
		for (int tmp = tp, i = 0; i < n; i++) {
			row[i] = tmp % 8;
			tmp /= 8;
		}

		for (int i = 0; col[0] != -2 && i < n; i++) {
			for (int j = 0; col[0] != -2 && j < n; j++) {
				if (v[i][j] != -1) {
					int clj = v[i][j] - row[i];
					if (clj < 0) col[0] = -2;
					else if (col[j] != -1 && col[j] != clj) col[0] = -2;
					else col[j] = clj;
				}
			}
		}
		for (int j = 0; j < n; j++) if (col[j] < 0) col[0] = -2;

		if (col[0] != -2) {
			bool ok = 1;
			vector<vector<int> > nv(n, vector<int>(n, 0));
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					nv[i][j] = row[i] + col[j];
					if (v[i][j] != -1 && v[i][j] != nv[i][j]) ok = 0;
				}
			}
			if (ok) possible.insert(nv);
		}
	}

	cout << possible.size() << endl;
	return 0;
}