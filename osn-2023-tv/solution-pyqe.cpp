#include <bits/stdc++.h>

using namespace std;

long long n, m, nn[2], a[2][200069];

int main()
{
	long long t, rr, i, ii, k, e, y, x, p, p2;
	
	scanf("%lld%lld", &n, &m);
	for(i = 0; i < m; i++)
	{
		scanf("%lld%lld", &e, &k);
		e--;
		nn[e]++;
		a[e][nn[e]] = k;
	}
	for(ii = 0; ii < 2; ii++)
	{
		sort(a[ii] + 1, a[ii] + nn[ii] + 1);
	}
	scanf("%lld", &t);
	for(rr = 0; rr < t; rr++)
	{
		scanf("%lld%lld", &y, &x);
		if(y > x)
		{
			swap(y, x);
		}
		p = lower_bound(a[0] + 1, a[0] + nn[0] + 1, x) - a[0];
		p2 = upper_bound(a[1] + 1, a[1] + nn[1] + 1, y) - a[1] - 1;
		printf("%lld\n", (nn[0] + 1 - p + p2) % 2);
	}
}
