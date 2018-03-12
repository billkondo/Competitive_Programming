#include "bits/stdc++.h"
using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    while(t--) {
	int n;
	scanf("%d", &n);

	map<int, int> f;

	for(int i = 1; i <= n; ++i) {
	    int a;
	    scanf("%d", &a);
	    ++f[a];
	}

	int ans = 0;
	for(auto i: f) ans += i.second - 1;

	printf("%d\n", ans);
    }
    
    return 0;
}
