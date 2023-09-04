#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, m, c, mn, mx;
vector<long long> al[100069];
bitset<100069> vtd;

void dfs(long long x)
{
	long long i, sz = al[x].size(), l;
	
	vtd[x] = 1;
	c++;
	mn = min(mn, x);
	mx = max(mx, x);
	for(i = 0; i < sz; i++)
	{
		l = al[x][i];
		if(!vtd[l])
		{
			dfs(l);
		}
	}
}

int main()
{
	long long i, k, l, z = 0;
	
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
		if(!vtd[i])
		{
			c = 0;
			mn = inf;
			mx = -inf;
			dfs(i);
			if(c == 3)
			{
				z -= mn * (n + 1 - mx) * 3;
			}
		}
	}
	printf("%lld\n", z);
}
