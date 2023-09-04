#include <bits/stdc++.h>

using namespace std;

long long n, m, dsu[100069], cc[100069];
vector<long long> al[100069];

long long fd(long long x)
{
	if(dsu[x] != x)
	{
		dsu[x] = fd(dsu[x]);
	}
	return dsu[x];
}

int main()
{
	long long i, j, r, k, l, sz, sm, z = 0;
	
	scanf("%lld%lld", &n, &m);
	for(i = 0; i < m; i++)
	{
		scanf("%lld%lld", &k, &l);
		al[k].push_back(l);
		al[l].push_back(k);
	}
	for(i = 1; i <= n; i++)
	{
		sm = 0;
		for(j = i; j <= n; j++)
		{
			dsu[j] = j;
			cc[j] = 1;
			sm++;
			sz = al[j].size();
			for(r = 0; r < sz; r++)
			{
				l = al[j][r];
				if(l >= i && l <= j)
				{
					if(fd(l) != fd(j))
					{
						sm -= cc[fd(l)] * (cc[fd(l)] <= 2);
						sm -= cc[fd(j)] * (cc[fd(j)] <= 2);
						cc[fd(j)] += cc[fd(l)];
						dsu[fd(l)] = fd(j);
						sm += cc[fd(j)] * (cc[fd(j)] <= 2);
					}
				}
			}
			z += sm;
		}
	}
	printf("%lld\n", z);
}
