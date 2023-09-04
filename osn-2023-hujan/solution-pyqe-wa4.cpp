#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long dv = 1e9 + 7, inf = 1e18;
long long n, nn = 0, a[1069][1069], dis[2069], rg[1069];
vector<pair<long long, long long>> al[2069];
bitset<2069> vtd;

pair<long long, long long> dfs(long long x)
{
	long long i, sz = al[x].size(), l, w;
	pair<long long, long long> tmp = {-inf, inf}, tmp2;
	
	vtd[x] = 1;
	if(x <= n)
	{
		tmp.fr = max(tmp.fr, dis[x]);
	}
	else
	{
		tmp.sc = min(tmp.sc, dis[x]);
	}
	for(i = 0; i < sz; i++)
	{
		l = al[x][i].fr;
		w = al[x][i].sc;
		if(!vtd[l])
		{
			dis[l] = dis[x] + w;
			tmp2 = dfs(l);
			tmp.fr = max(tmp.fr, tmp2.fr);
			tmp.sc = min(tmp.sc, tmp2.sc);
		}
		else if(dis[l] != dis[x] + w)
		{
			printf("0\n");
			exit(0);
		}
	}
	return tmp;
}

int main()
{
	long long i, j, ml = 1, z = 1;
	pair<long long, long long> tmp;
	
	scanf("%lld", &n);
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			scanf("%lld", &a[i][j]);
			if(a[i][j] != -1)
			{
				al[i].push_back({n + j, a[i][j]});
				al[n + j].push_back({i, -a[i][j]});
			}
		}
	}
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			if(a[i][j] != -1)
			{
				break;
			}
		}
		if(j > n)
		{
			printf("-1\n");
			return 0;
		}
		for(j = 1; j <= n; j++)
		{
			if(a[j][i] != -1)
			{
				break;
			}
		}
		if(j > n)
		{
			printf("-1\n");
			return 0;
		}
	}
	for(i = 1; i <= n * 2; i++)
	{
		if(!vtd[i])
		{
			tmp = dfs(i);
			if(tmp.fr > tmp.sc)
			{
				printf("0\n");
				return 0;
			}
			nn++;
			rg[nn] = tmp.sc - tmp.fr;
		}
	}
	for(i = 1; i <= nn; i++)
	{
		z = z * (rg[i] + 1) % dv;
		ml = ml * rg[i] % dv;
	}
	z = (z + dv - ml) % dv;
	printf("%lld\n", z);
}
