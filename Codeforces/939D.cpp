#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5 + 10;
const int MAX = 30;

int n;
char a[maxn], b[maxn];

int par[MAX];
int sz[MAX];

vector<pii> ans;

void init() {
    for(int i = 0; i < MAX; ++i) {
	par[i] = i;
	sz[i] = 1;
    }
}

int root(int v) {
    if(par[v] == v) return v;
    return root(par[v]);
} 

void merge(int x, int y) {
    x = root(x);
    y = root(y);
    if(x == y) return;
    if(sz[y] > sz[x]) swap(x, y);
    sz[x] += sz[y];
    par[y] = x;
}

void solve() {
    init();
    for(int i = 0; i < n; ++i) {
	int x = a[i] - 'a';
	int y = b[i] - 'a';
	if(root(x) == root(y)) continue;
	merge(x, y);
	ans.push_back({a[i], b[i]});
    }
}

int main() {
    scanf("%d %s %s", &n, a, b);
    solve();
    printf("%d\n", (int)ans.size());
    for(auto i: ans) printf("%c %c\n", i.first, i.second);
    return 0;
}
