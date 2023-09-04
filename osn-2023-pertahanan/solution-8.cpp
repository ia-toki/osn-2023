#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069], dp[200069], mxa[200069];

int main()
{
	long long i, j;
	
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
		if(i - a[i] >= 0)
		{
			dp[i] = max(dp[i], mxa[i - a[i]] + 1);
		}
		mxa[i] = max(mxa[i - 1], dp[i]);
	}
	printf("%lld\n", n - mxa[n]);
}
