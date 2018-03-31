#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 1e4 + 10;

int n[3];
vector<pii> points[3];
int red, green;
int Up[2][maxn], Down[2][maxn];

ll cross(pii o, pii a, pii b) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}

void solve() {
    red = green = 0;
    sort(points[2].begin(), points[2].end());

    for(int i = 0; i < n[2]; ++i)
	for(int j = i + 1; j < n[2]; ++j) {
	    int id = i * n[2] + j;
	    int L = min(points[2][i].first, points[2][j].first);
	    int R = max(points[2][i].first, points[2][j].first);

	    for(int k = 0; k <= 1; ++k) {
		Up[k][id] = Down[k][id] = 0;
		for(int p = 0; p < n[k]; ++p) {
		    int x = points[k][p].first;
		    if(x <= L || x > R) continue;
		    if(cross(points[2][i], points[2][j], points[k][p]) < 0) 
			++Down[k][id];					
		    else 
			++Up[k][id];					
		}
	    }
	}

    for(int i = 0; i < n[2]; ++i)
	for(int j = i + 1; j < n[2]; ++j)
	    for(int k = j + 1; k < n[2]; ++k) {
		int right = (points[2][j].first > points[2][k].first) ? j : k;
		int id = i * n[2] + right;
		int other = (right == j) ? k : j;
		int X = i * n[2] + other;
		int Y = min(other, right) * n[2] + max(other, right);
		if(cross(points[2][i], points[2][right], points[2][other]) < 0) {
		    int Red = Down[0][id] - Down[0][X] - Down[0][Y];
		    int Green = Down[1][id] - Down[1][X] - Down[1][Y];
		    if(Red > Green) ++red;
		    else if(Green > Red) ++green;
		}
		else {
		    int Red = Up[0][id] - Up[0][X] - Up[0][Y];
		    int Green = Up[1][id] - Up[1][X] - Up[1][Y];
		    if(Red > Green) ++red;
		    else if(Green > Red) ++green;
		}
	    }
}

int main() {
    int test = 0;
    while(scanf("%d %d %d", &n[0], &n[1], &n[2])) {
	if(n[0] == -1 && n[1] == -1 && n[2] == -1) break;

	for(int k = 0; k <= 2; ++k) {
	    points[k].clear();
	    for(int i = 0; i < n[k]; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		points[k].push_back({x, y});
	    }
	}
	solve();
	printf("Case %d: %d %d\n", ++test, red, green);
    }
    return 0;
}
