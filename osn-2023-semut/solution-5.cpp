#include <bits/stdc++.h>

using namespace std;

long long n;

int main()
{
	long long i, z = 0;
	
	scanf("%lld", &n);
	for(i = 1; i <= n; i++)
	{
		z += i * (n + 1 - i);
	}
	printf("%lld\n", z);
}
