#include "bits/stdc++.h"
using namespace std;

int n;

int main() {
    scanf("%d", &n);
    printf("%d\n", (1 << n) - 1);
    for(int mask = 1; mask < (1 << n); ++mask) {
	int sz = 0;
	vector<int> vec;
	for(int k = 0; k < n; ++k)
	    if((1 << k) & mask) {
		++sz;
		vec.push_back(k);
	    }
	printf("%d ", sz);
	for(auto x: vec)
	    printf("%d ", x + 1);
	printf("\n");
    }
    return 0;
}
