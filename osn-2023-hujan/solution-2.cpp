#include <bits/stdc++.h>
using namespace std;

void ans(int x) {
	cout << x % 1000000007 << endl;
	exit(0);
}

int main() {
	int n; cin >> n; // n = 2
	int a, b, c, d; cin >> a >> b >> c >> d;
	if (a == -1 && b == -1) ans(-1);
	if (c == -1 && d == -1) ans(-1);
	if (a == -1 && c == -1) ans(-1);
	if (b == -1 && d == -1) ans(-1);
	int smad = -1, smbc = -1;
	if (b != -1 && c != -1) smbc = b + c;
	if (a != -1 && d != -1) smad = a + d;
	if (smad == -1) {
		if (a == -1 && d == -1) ans(b + c + 1);
		else {
			if (b + c - max(a, d) >= 0) ans(1);
			else ans(0);
		}
	} else if (smbc == -1) {
		if (b == -1 && c == -1) ans(a + d + 1);
		else {
			if (a + d - max(b, c) >= 0) ans(1);
			else ans(0);
		}
	} else {
		if (a + d != b + c) ans(0);
		else ans(1);
	}
}