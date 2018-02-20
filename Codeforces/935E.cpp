#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;

const int maxn = 1e4 + 10;
const int INF = 1e9;

int n;
char s[maxn];
int P, M;

struct node {
    int l, r;
    int left, right;
} Tree[maxn];

int cur;
vector<int> stk;

void addNode(int x, bool flag) {
    ++cur;
    Tree[cur].l = x;

    if(!stk.empty()) {
	int par = stk.back();
	if(!Tree[par].left) Tree[par].left = cur;
	else {
	    assert(!Tree[par].right);
	    Tree[par].right = cur;
	}
    }

    if(flag) stk.push_back(cur);
    else Tree[cur].r = x;
}

void buildTree() {
    for(int i = 0; i < n; ++i) {
	if(s[i] == '(' || (s[i] != '?' && s[i] != ')')) addNode(i, s[i] == '(');
	else
	    if(s[i] == ')') {
		int v = stk.back();
		Tree[v].r = i;
		stk.pop_back();
	    }
    }
}

ll dp[2][maxn][105];
bool mrk[2][maxn][105];
bool flag;

ll f(int type, int v, int op) {
    if(!mrk[type][v][op]) {
	mrk[type][v][op] = true;
	if(!type) {
	    if(Tree[v].l == Tree[v].r) return dp[type][v][op] = (!op) ? (s[Tree[v].l] - '0') : (-INF);

	    dp[type][v][op] = -INF;
	    int L = Tree[v].left;
	    int R = Tree[v].right;

	    if(op) {
		for(int x = 0; x <= 1; ++x)
		    for(int y = 0; y <= 1; ++y)
			for(int i = 0; i <= op - 1; ++i) {
			    if(abs(f(x, L, i)) == INF || abs(f(y, R, op - i - 1)) == INF) continue;
			    if(flag) dp[type][v][op] = max(dp[type][v][op], f(x, L, i) - f(y, R, op - i - 1));
			    else dp[type][v][op]= max(dp[type][v][op], f(x, L, i) + f(y, R, op - i - 1));
			}
	    }

	    for(int x = 0; x <= 1; ++x)
		for(int y = 0; y <= 1; ++y)
		    for(int i = 0; i <= op; ++i) {
			if(abs(f(x, L, i)) == INF || abs(f(y, R, op - i)) == INF) continue;
			if(flag) dp[type][v][op] = max(dp[type][v][op], f(x, L, i) + f(y, R, op - i));
			else dp[type][v][op]= max(dp[type][v][op], f(x, L, i) - f(y, R, op - i));
		    }
	}
	else {
	    if(Tree[v].l == Tree[v].r) return dp[type][v][op] = (!op) ? (s[Tree[v].l] - '0') : (INF);

	    dp[type][v][op] = INF;
	    int L = Tree[v].left;
	    int R = Tree[v].right;

	    if(op) {
		for(int x = 0; x <= 1; ++x)
		    for(int y = 0; y <= 1; ++y)
			for(int i = 0; i <= op - 1; ++i) {
			    if(abs(f(x, L, i)) == INF || abs(f(y, R, op - i - 1)) == INF) continue;
			    if(flag) dp[type][v][op] = min(dp[type][v][op], f(x, L, i) - f(y, R, op - i - 1));
			    else dp[type][v][op]= min(dp[type][v][op], f(x, L, i) + f(y, R, op - i - 1));
			}
	    }

	    for(int x = 0; x <= 1; ++x)
		for(int y = 0; y <= 1; ++y)
		    for(int i = 0; i <= op; ++i) {
			if(abs(f(x, L, i)) == INF || abs(f(y, R, op - i)) == INF) continue;
			if(flag) dp[type][v][op] = min(dp[type][v][op], f(x, L, i) + f(y, R, op - i));
			else dp[type][v][op]= min(dp[type][v][op], f(x, L, i) - f(y, R, op - i));
		    }
	}
    }
    return dp[type][v][op];
}

ll solve() {
    n = strlen(s);
    if(n == 1) return s[0] - '0';
    if(P > M) {
	flag = true;
	swap(P, M);
    }
    buildTree();
    return f(0, 1, P);
}

int main() {
    scanf(" %s %d %d", s, &P, &M);
    printf("%lld\n", solve());
    return 0;
}
