#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MX = 1005;
const ll mod = 1e9 + 7;

int n, v[MX][MX], a[MX][2];
bool vis[MX][2], can = 1;
vector<vector<pair<int, int> > > cc;
vector<pair<int, int> > rt;

void dfs(int nw, int dir, int val) {
	if (vis[nw][dir]) {
		if (val != a[nw][dir]) can = 0;
		return;
	}
	rt.push_back({nw, dir});
	vis[nw][dir] = 1;
	a[nw][dir] = val;

	for (int i = 0; i < n; i ++) {
		int cr = (dir ? v[i][nw] : v[nw][i]);
		if (cr == -1) continue;
		int nval = cr - val;
		dfs(i, 1 - dir, nval);
	}
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			cin >> v[i][j];
	
	can = 1;
	for (int i = 0; i < n; i ++) {
		rt.clear();
		if (!vis[i][0]) {
			dfs(i, 0, 0);
			cc.push_back(rt);
		}
	}

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++) {
			if (!vis[j][1]) continue;
			int x = a[i][0], y = a[j][1];
			if (v[i][j] != -1 && x + y != v[i][j]) can = 0;
		}

	if (can == 0) {
		cout << 0 << endl;
		return 0;
	}

	ll mul1 = 1ll, mul2 = 1ll;
	for (auto e : cc) {
		int R = (int)mod, L = -R;
		for (auto i : e) {
			if (i.second == 0)
				L = max(L, -a[i.first][i.second]);
			else
				R = min(R, a[i.first][i.second]);
		}
		if (L > R) {
			cout << 0 << endl;
			return 0;
		}
		int len = R - L + 1, len2 = R - L;
		mul1 = (mul1 * len) % mod;
		mul2 = (mul2 * len2) % mod;
	}

	for (int i = 0; i < n; i ++) {
		bool waow = 0;
		for (int j = 0; j < n; j ++) {
			if (v[i][j] != -1) waow = 1;
		}
		if (!waow) {
			cout << "-1" << endl;
			return 0;
		}
		waow = 0;
		for (int j = 0; j < n; j ++) {
			if (v[j][i] != -1) waow = 1;
		}
		if (!waow) {
			cout << "-1" << endl;
			return 0;
		}
	}

	cout << mul1 << endl;
	return 0;
}
