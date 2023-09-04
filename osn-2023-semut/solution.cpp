#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long inf = 1e18;
long long n, m, mxa[100069][2], mna[100069][2];
pair<long long, long long> ed[200069];

int main()
{
	long long i, ii, k, l, z = 0;
	
	scanf("%lld%lld", &n, &m);
	for(i = 1; i <= n; i++)
	{
		for(ii = 0; ii < 2; ii++)
		{
			mxa[i][ii] = 0;
			mna[i][ii] = n + 1;
		}
	}
	for(i = 1; i <= m; i++)
	{
		scanf("%lld%lld", &k, &l);
		ed[i] = {k, l};
		mxa[l][1] = max(mxa[l][1], min(mxa[l][0], k));
		mxa[l][0] = max(mxa[l][0], k);
		mna[k][1] = min(mna[k][1], max(mna[k][0], l));
		mna[k][0] = min(mna[k][0], l);
	}
	for(i = 1; i <= n; i++)
	{
		z += (i - mxa[i][0]) * (mna[i][0] - i);
	}
	for(i = 1; i <= m; i++)
	{
		k = ed[i].fr;
		l = ed[i].sc;
		if(mna[k][0] == l && mxa[l][0] == k)
		{
			z += (k - max(mxa[k][0], mxa[l][1])) * (min(mna[l][0], mna[k][1]) - l) * 2;
		}
	}
	printf("%lld\n", z);
}
