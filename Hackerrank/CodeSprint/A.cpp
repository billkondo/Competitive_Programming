#include "bits/stdc++.h"
using namespace std;

const int N = 1e3 + 10;

int n, m;

int freq[N];

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i) {
	int c;
	scanf("%d", &c);
	++freq[c];
    }
    for(int i = 0; i < m; ++i) printf("%d ", freq[i]);
    return 0;
}
