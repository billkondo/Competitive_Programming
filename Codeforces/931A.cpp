#include "bits/stdc++.h"
using namespace std;

int l, r;

int get(int x) {
    if(!x) return 0;
    return x * (x + 1) / 2;
}

int solve() {
    int ans = INT_MAX;
    if(l > r) swap(l, r);
    for(int i = l; i <= r; ++i)
	ans = min(ans, get(i - l) + get(r - i));
    return ans;
}

int main() {
    scanf("%d %d", &l, &r);
    printf("%d\n", solve());
    return 0;
}
