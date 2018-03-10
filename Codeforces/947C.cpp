#include "bits/stdc++.h"
using namespace std;

const int LOG = 31;
const int maxn = 3e5 + 10;

int n;
int a[maxn];
int p[maxn];

int ans[maxn];

struct node {
    int cnt;
    int left, right;
} Trie[maxn * LOG];

int cur;

void add(int x) {
    int curNode = 0;
    for(int k = LOG - 1; k >= 0; --k) {
	if((1 << k) & x) {
	    if(!Trie[curNode].right) Trie[curNode].right = ++cur;
	    curNode = Trie[curNode].right;
	}
	else {
	    if(!Trie[curNode].left) Trie[curNode].left = ++cur;
	    curNode = Trie[curNode].left;
	}

        ++Trie[curNode].cnt;
    }
}

int query(int x) {
    int curNode = 0;
    int ans = 0;
    for(int k = LOG - 1; k >= 0; --k) {
	int left = Trie[curNode].left;
	int right = Trie[curNode].right;
	
	if((1 << k) & x) {
	    if(right && Trie[right].cnt) {
		--Trie[right].cnt;
		curNode = right;
	    }
	    else {
		--Trie[left].cnt;
		curNode = left;
		ans += (1 << k);
	    }
	}
	else {
	    if(left && Trie[left].cnt) {
		--Trie[left].cnt;
		curNode = left;
	    }
	    else {
		--Trie[right].cnt;
		curNode = right;
		ans += (1 << k);
	    }
	}
    }

    return ans;
}

void solve() {
    for(int i = 1; i <= n; ++i) add(p[i]);
    for(int i = 1; i <= n; ++i) ans[i] = query(a[i]);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
    solve();
    for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
    return 0;
}
