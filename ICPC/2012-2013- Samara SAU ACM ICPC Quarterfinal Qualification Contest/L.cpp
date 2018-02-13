#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 2e5 + 10;

int n;
ll s[maxn], a[maxn];

int main()
{
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> s[i], a[i] = s[i] - s[i - 1];
	for(int i = 1; i <= n; ++i) cout << a[i] << " ";
	cout << '\n';
	
	return 0;
}
