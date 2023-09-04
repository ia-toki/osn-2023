#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;
long long n, a[200069];

int main()
{
	long long k;
	
	scanf("%lld%lld", &n, &k);
	printf("%lld\n", n - n / k);
}
