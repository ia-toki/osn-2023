#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069], dp[200069];

int main()
{
	long long i, j, z = 0;
	
	scanf("%lld", &n);
	for(i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		dp[i] = -inf;
		for(j = i - 1; j >= max(i - a[i] + 1, 1ll); j--)
		{
			if(a[j] == a[i] - (i - j))
			{
				dp[i] = dp[j] + 1;
				break;
			}
		}
		if(dp[i] == -inf)
		{
			for(j = 0; j <= i - a[i]; j++)
			{
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	for(i = 1; i <= n; i++)
	{
		z = max(z, dp[i]);
	}
	printf("%lld\n", n - z);
}
