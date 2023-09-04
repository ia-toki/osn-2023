#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069], dp[200069];

int main()
{
	long long i, j, r, sm, z = inf;
	
	scanf("%lld", &n);
	for(i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		dp[i] = inf;
		for(j = 0; j <= i - 1; j++)
		{
			if(j <= i - a[i] || a[j] == a[i] - (i - j))
			{
				sm = dp[j];
				for(r = j + 1; r <= i - 1; r++)
				{
					sm += a[r] != max(a[i] - (i - r), 1ll);
				}
				dp[i] = min(dp[i], sm);
			}
		}
	}
	for(i = 1; i <= n; i++)
	{
		z = min(z, dp[i] + n - i);
	}
	printf("%lld\n", z);
}
