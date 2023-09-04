#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, m, nv = 0, vi[100069];
vector<long long> al[100069];

long long dfs(long long x)
{
	long long i, sz = al[x].size(), l, c = 1;
	
	vi[x] = nv;
	for(i = 0; i < sz; i++)
	{
		l = al[x][i];
		if(vi[l] < nv)
		{
			c += dfs(l);
		}
	}
	return c;
}

int main()
{
	long long i, k, l, mn = inf, mx = -inf, z = 0;
	
	scanf("%lld%lld", &n, &m);
	for(i = 0; i < m; i++)
	{
		scanf("%lld%lld", &k, &l);
		al[k].push_back(l);
		al[l].push_back(k);
	}
	for(i = 1; i <= n; i++)
	{
		z += i * (n + 1 - i);
		nv++;
		if(dfs(i) == 3)
		{
			mn = min(mn, i);
			mx = max(mx, i);
		}
	}
	if(mn != inf)
	{
		z -= mn * (n + 1 - mx) * 3;
	}
	printf("%lld\n", z);
}
