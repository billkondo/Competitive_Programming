#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 3e3 + 10;

int n, m;
int p[MAXN];

vector<pii> ans;

int fp;
int sz;
int last;
bool mrk[MAXN];

void dfs(int v) {
    last = v;
    mrk[v] = true;
    ++sz;
    if(!mrk[p[v]]) dfs(p[v]);
}

void removeCicles() {
    for(int k = 1; k <= fp - m; ++k) {
	memset(mrk, false, sizeof(mrk));
	pii change = {INT_MAX, INT_MAX};
	for(int i = 1; i <= n; ++i) {
	    if(mrk[i] || p[i] == i) continue;
	    int v = i;
	    int x = INT_MAX;
	    int y = INT_MAX;
	    mrk[v] = true;
	    x = v;
	    v = p[v];
	    while(v != i) {
		mrk[v] = true;
		if(v < x) {
		    y = x;
		    x = v;
		}
		else if(v < y) y = v;
		v = p[v];
	    }
	    change = min(change, {x, y});
	}
	
	ans.push_back({change.first, change.second});
	swap(p[change.first], p[change.second]);
    }
}

void addCicles() {
    for(int k = 1; k <= m - fp; ++k) {
	memset(mrk, false, sizeof(mrk));
	dfs(1);
	for(int i = 1; i <= n; ++i) {
	    if(!mrk[i]) {
		ans.push_back({1, i});
		swap(p[1], p[i]);
		break;
	    }
	}
    }
}

void solve() {
    for(int i = 1; i <= n; ++i)
	if(!mrk[i]) {
	    sz = 0;
	    dfs(i);
	    fp += sz - 1;
	}

    if(fp == m) return;
    if(m < fp) removeCicles();
    if(m > fp) addCicles();
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
    scanf("%d", &m);
    solve();
    printf("%d\n", (int)ans.size());
    for(auto i: ans) printf("%d %d ", i.first, i.second);
    return 0;
}
