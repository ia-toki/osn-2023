#include <bits/stdc++.h>

using namespace std;

long long n, nn = 1, dp[169];
bool ft = 1;

inline bool qr(long long x)
{
	printf("%lld\n", x);
	fflush(stdout);
	if(ft)
	{
		ft = 0;
		return 0;
	}
	else
	{
		long long i, k;
		char ch;
		
		for(i = 0; i < 3; i++)
		{
			scanf(" %c", &ch);
		}
		if(ch == 'S')
		{
			exit(0);
		}
		k = ch == 'B';
		for(i = 0; i < 6; i++)
		{
			scanf(" %c",&ch);
		}
		return k;
	}
}

inline long long yk(long long x)
{
	return lower_bound(dp + 1, dp + nn + 1, x) - dp;
}

int main()
{
	long long k, lh, rh, md, md2, p;
	
	scanf("%lld%lld", &n, &k);
	dp[1] = 1;
	for(; dp[nn] < n;)
	{
		nn++;
		dp[nn] = dp[nn - 1] + dp[nn - 2] + 1;
	}
	for(lh = 1, rh = n, md = -1; 1;)
	{
		if(md == -1)
		{
			p = yk(rh - lh + 1);
			md = lh + dp[p - 1];
			qr(md);
		}
		p = yk(md - lh);
		md2 = lh + dp[max(p - 1, 0ll)];
		if(qr(md2))
		{
			rh = md - 1;
			md = md2;
		}
		else
		{
			lh = md + 1;
			md = -1;
		}
	}
}
