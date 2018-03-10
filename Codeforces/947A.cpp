#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e6 + 10;

bool prime[maxn];
int Min[maxn];

void sieve() {
    prime[1] = true;
    for(int i = 1; i < maxn; ++i) Min[i] = INT_MAX;

    Min[1] = 1;

    for(int i = 2; i < maxn; ++i)
	if(!prime[i]) {
	    Min[i] = i;
	    for(int j = i + i; j < maxn; j += i) {
		prime[j] = true;
		int q = j / i;
		Min[j] = min(Min[j], i * (q - 1) + 1); 
	    }		
	}
}

int solve(int x2) {
    int ans = INT_MAX;
    int l = INT_MAX;
    
    for(int i = 1; i <= x2; ++i)
	if(x2 % i == 0 && !prime[i]) {
	    int q = x2 / i;
	    l = min(l, i * (q - 1) + 1);
	}

    for(int i = l; i < x2; ++i)
	ans = min(ans, Min[i]);

    return ans;
}

int main() {
    int x2;
    scanf("%d", &x2);
    sieve();
    printf("%d\n", solve(x2));
    return 0;
}
