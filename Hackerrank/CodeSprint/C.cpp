#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;

int q;
int X[2], Y[2];
pii p[2];

int dx[] = {1, 0, -1, -1, -1, 0, 1, 1};
int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};

struct piece {
    char type;
    int x, y, state;
};

vector<piece> ans;

void correct(int x, int y, int state) {
    for(int i = 0; i < (int)ans.size(); ++i) 
	if(ans[i].x == x && ans[i].y == y) 
	    ans[i].state = state;
}

bool ok(int l, int r, int x) {
    return l < x && x < r;
}

bool Free(pii A, pii B) {
    if(A.first == B.first) {
	int L = min(A.second, B.second);
	int R = max(A.second, B.second);

	if(p[0].first == B.first && ok(L, R, p[0].second)) return false;
	if(p[1].first == B.first && ok(L, R, p[1].second)) return false;

	for(int i = 0; i < (int)ans.size(); ++i)
	    if(!ans[i].state) {
		if(ans[i].x != A.first) continue;
		if(ok(L, R, ans[i].y)) return false;
	    }
    }

    if(A.second == B.second) {
	int L = min(A.first, B.first);
	int R = max(A.first, B.first);

	if(p[0].second == B.second && ok(L, R, p[0].first)) return false;
	if(p[1].second == B.second && ok(L, R, p[1].first)) return false;

	for(int i = 0; i < (int)ans.size(); ++i)
	    if(!ans[i].state) {
		if(ans[i].y != A.second) continue;
		if(ok(L, R, ans[i].x)) return false;
	    }
    }

    if(A.first + A.second == B.first + B.second) {
	int l = min(A.first, B.first);
	int r = max(A.first, B.first);

	int L = min(A.second, B.second);
	int R = max(A.second, B.second);


	if(p[0].first + p[0].second == A.first + A.second && ok(l, r, p[0].first) && ok(L, R, p[0].second)) return false;
	if(p[1].first + p[1].second == A.first + A.second && ok(l, r, p[1].first) && ok(L, R, p[1].second)) return false;

	for(int i = 0; i < (int)ans.size(); ++i)
	    if(!ans[i].state) {
		if(ans[i].x + ans[i].y != A.first + A.second) continue;
		if(ok(L, R, ans[i].x) && ok(L, R, ans[i].y)) return false;
	    }
    }

    if(A.first - A.second == B.first - B.second) {
	int l = min(A.first, B.first);
	int r = max(A.first, B.first);
	
	int L = min(A.second, B.second);
	int R = max(A.second, B.second);
	

	if(p[0].first - p[0].second == A.first - A.second && ok(l, r, p[0].first) && ok(L, R, p[0].second)) return false;
	if(p[1].first - p[1].second == A.first - A.second && ok(l, r, p[1].first) && ok(L, R, p[1].second)) return false;
	
	for(int i = 0; i < (int)ans.size(); ++i)
	    if(!ans[i].state) {
		if(ans[i].x - ans[i].y != A.first - A.second) continue;
		if(ok(L, R, ans[i].x) && ok(L, R, ans[i].y)) return false;
	    }
    }
    
    return true;
}

bool check() {
    int king = 0;
    for(int k = 0; k < 2; ++k)
	for(int i = 0; i < (int)ans.size(); ++i) {
	    if(!ans[i].state) {
		pii P = {ans[i].x, ans[i].y};
		if(!Free(p[k], P)) continue;
		if(p[k].first == ans[i].x) { ++king; break; }
		else if(p[k].second == ans[i].y) {++king; break; }
		else if(p[k].first + p[k].second == ans[i].x + ans[i].y) { ++king; break; }
		else if(p[k].first - p[k].second == ans[i].x - ans[i].y) { ++king; break; }
	    }
	}
    return king == 2;
}

bool checkmate() {
    for(int k = 0; k < 2; ++k) 
	for(int i = 0; i < 8; ++i) {
	    int x = X[k] + dx[i];
	    int y = Y[k] + dy[i];

	    if(x < 0 || y < 0 || x == 8 || y == 8) continue;
	    if(pii(x, y) == p[k ^ 1]) continue;

	    correct(x, y, 1);
	    p[k] = {x, y};

	    bool flag = check();
	    
	    correct(x, y, 0);
	    p[k] = {X[k], Y[k]};

	    if(!flag) return false;
	}

    return true;
}

bool can(int x, int y) {
    for(int k = 0; k < 2; ++k) if(pii(x, y) == p[k]) return false;
    for(int i = 0; i < (int)ans.size(); ++i)
	if(ans[i].x == x && ans[i].y == y)
	    return false;
    return true;
}

bool solveTwo(int it) {
    if(it == 2) return checkmate();
    for(int i = 0; i < 8; ++i)
	for(int j = 0; j < 8; ++j)
	    if(can(i, j)) {
		ans.push_back({'Q', i, j, 0});
		if(solveTwo(it + 1)) return true;
		ans.pop_back();
	    }
    return false;
}

bool solveThree(int it) {
    if(it == 3) return checkmate();
    for(int i = 0; i < 8; ++i)
	for(int j = 0; j < 8; ++j)
	    if(can(i, j)) {
		ans.push_back({'Q', i, j, 0});
		if(solveThree(it + 1)) return true;
		ans.pop_back();
	    }
    return false;
}

bool solveFour(int it) {
    if(it == 4) return checkmate();
    for(int i = 0; i < 8; ++i)
	for(int j = 0; j < 8; ++j)
	    if(can(i, j)) {
		ans.push_back({'Q', i, j, 0});
		if(solveFour(it + 1)) return true;
		ans.pop_back();
	    }
    return false;
}

void solve() {
    ans.clear();

    if(solveTwo(0)) return;
    if(solveThree(0)) return;
    solveFour(0);
}

int main() {
    scanf("%d", &q);
    while(q--) {
	for(int k = 0; k < 2; ++k) {
	    scanf("%d %d", &X[k], &Y[k]);
	    p[k] = {X[k], Y[k]};
	}
	solve();
	printf("%d\n", (int)ans.size());
	for(int i = 0; i < (int)ans.size(); ++i)
	    printf("%c %d %d\n", ans[i].type, ans[i].x, ans[i].y);
    }
    return 0;
}
