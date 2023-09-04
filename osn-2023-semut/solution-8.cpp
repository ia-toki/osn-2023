#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long inf = 1e18;
long long n, m, mxa[100069], mna[100069];
pair<long long, long long> ed[200069];

int main()
{
	long long i, k, l, z = 0;
	
	scanf("%lld%lld", &n, &m);
	for(i = 1; i <= n; i++)
	{
		mxa[i] = 0;
		mna[i] = n + 1;
	}
	for(i = 1; i <= m; i++)
	{
		scanf("%lld%lld", &k, &l);
		ed[i] = {k, l};
		mxa[l] = max(mxa[l], k);
		mna[k] = min(mna[k], l);
	}
	for(i = 1; i <= n; i++)
	{
		z += (i - mxa[i]) * (mna[i] - i);
	}
	for(i = 1; i <= m; i++)
	{
		k = ed[i].fr;
		l = ed[i].sc;
		if(mna[k] == l && mxa[l] == k)
		{
			z += (k - mxa[k]) * (mna[l] - l) * 2;
		}
	}
	printf("%lld\n", z);
}
