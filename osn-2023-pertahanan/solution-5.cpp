#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069];

int main()
{
	long long i, z = 0;
	bool bad = 1;
	
	scanf("%lld", &n);
	for(i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		if(a[i] == 1)
		{
			bad = 0;
		}
		else
		{
			if(bad)
			{
				z++;
				bad = 0;
			}
			else
			{
				bad = 1;
			}
		}
	}
	printf("%lld\n", z);
}
