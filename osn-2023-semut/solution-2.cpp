#include <bits/stdc++.h>

using namespace std;

long long n, m;
vector<long long> al[100069];
bitset<100069> vtd;

long long dfs(long long x, long long lb, long long rb)
{
	long long i, sz = al[x].size(), l, c = 1;
	
	vtd[x] = 1;
	for(i = 0; i < sz; i++)
	{
		l = al[x][i];
		if(!vtd[l] && l >= lb && l <= rb)
		{
			c += dfs(l, lb, rb);
		}
	}
	return c;
}

int main()
{
	long long i, j, r, k, l, p, c, z = 0;
	
	scanf("%lld%lld", &n, &m);
	for(i = 0; i < m; i++)
	{
		scanf("%lld%lld", &k, &l);
		al[k].push_back(l);
		al[l].push_back(k);
	}
	for(i = 1; i <= n; i++)
	{
		for(j = i; j <= n; j++)
		{
			for(r = i; r <= j; r++)
			{
				for(p = i; p <= j; p++)
				{
					vtd[p]=0;
				}
				c = dfs(r, i, j);
				z += c <= 2;
			}
		}
	}
	printf("%lld\n", z);
}
