#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long inf = 1e18;
long long n, m;
pair<long long, long long> ed[200069];
vector<long long> al[100069];

int main()
{
	long long i, j, k, l, sz, mx, mn, p, z = 0;
	
	scanf("%lld%lld", &n, &m);
	for(i = 1; i <= m; i++)
	{
		scanf("%lld%lld", &k, &l);
		ed[i] = {k, l};
		al[k].push_back(l);
		al[l].push_back(k);
	}
	for(i = 1; i <= n; i++)
	{
		mx = 0;
		mn = n + 1;
		sz = al[i].size();
		for(j = 0; j < sz; j++)
		{
			p = al[i][j];
			if(p < i)
			{
				mx = max(mx, p);
			}
			else if(p > i)
			{
				mn = min(mn, p);
			}
		}
		z += (i - mx) * (mn - i);
	}
	for(i = 1; i <= m; i++)
	{
		k = ed[i].fr;
		l = ed[i].sc;
		mx = 0;
		mn = n + 1;
		sz = al[k].size();
		for(j = 0; j < sz; j++)
		{
			p = al[k][j];
			if(p != l)
			{
				if(p < k)
				{
					mx = max(mx, p);
				}
				else if(p > l)
				{
					mn = min(mn, p);
				}
				else
				{
					break;
				}
			}
		}
		if(j < sz)
		{
			continue;
		}
		sz = al[l].size();
		for(j = 0; j < sz; j++)
		{
			p = al[l][j];
			if(p != k)
			{
				if(p < k)
				{
					mx = max(mx, p);
				}
				else if(p > l)
				{
					mn = min(mn, p);
				}
				else
				{
					break;
				}
			}
		}
		if(j < sz)
		{
			continue;
		}
		z += (k - mx) * (mn - l) * 2;
	}
	printf("%lld\n", z);
}
