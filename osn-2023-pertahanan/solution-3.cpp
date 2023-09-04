#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069], ca[200069], z = inf;

void rk(long long cdh)
{
	if(cdh <= n)
	{
		for(ca[cdh] = 1; ca[cdh] <= n; ca[cdh]++)
		{
			if(ca[cdh] == 1 || ca[cdh] == ca[cdh - 1] + 1)
			{
				rk(cdh + 1);
			}
		}
	}
	else
	{
		long long i, c = 0;
		
		for(i = 1; i <= n; i++)
		{
			c += ca[i] != a[i];
		}
		z = min(z, c);
	}
}

int main()
{
	long long i;
	
	scanf("%lld", &n);
	for(i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
	}
	rk(1);
	printf("%lld\n", z);
}
