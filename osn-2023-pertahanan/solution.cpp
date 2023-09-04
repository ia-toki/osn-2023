#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069], dp[200069], dp2[400069], mxa[200069];

int main()
{
	long long i;
	
	scanf("%lld", &n);
	for(i = -n; i <= n; i++)
	{
		dp2[n + i] = -inf;
	}
	for(i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		dp[i] = dp2[n + a[i] - i] + 1;
		if(i - a[i] >= 0)
		{
			dp[i] = max(dp[i], mxa[i - a[i]] + 1);
		}
		dp2[n + a[i] - i] = max(dp2[n + a[i] - i], dp[i]);
		mxa[i] = max(mxa[i - 1], dp[i]);
	}
	printf("%lld\n", n - mxa[n]);
}
