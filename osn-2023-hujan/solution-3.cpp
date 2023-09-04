#include <bits/stdc++.h>
using namespace std;

void ans(int x) {
	cout << x << endl;
	exit(0);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n; cin >> n;
	vector<int> sumcol(n, 0), sumrow(n, 0);
	for (int i = 0; i < n; i++) {
		for (int x, j = 0; j < n; j++) {
			cin >> x;
			sumrow[i] += x;
			sumcol[j] += x;
		}
	}

	for (int i = 0; i < n; i++) {
		// sumrow/sumcol = -n -> all values in row/col are -1
		if (sumrow[i] + n == 0) ans(-1);
		if (sumcol[i] + n == 0) ans(-1);
	}
	ans(1);
}