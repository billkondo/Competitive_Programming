#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args)

typedef long long ll;

const int maxn = 5e5 + 10;

int Q;

double ans;

vector<int> S;
ll pre[maxn];

double f(int x, int add) {
    return 1.0 * (pre[x] + add) / (x + 1); 
}

void add(int x) {
    S.push_back(x);

    pre[S.size() - 1] = pre[S.size() - 2] + x;

    int l = 0;
    int r = S.size() - 2;

    while(r - l > 1) {
	int mid = (l + r) >> 1;
	if(f(mid, x) < f(mid + 1, x))
	    r = mid;
	else
	    l = mid;
    }

    ans = max(ans, 1.0 * x - f(l + 1, x));
}

int main() {
    scanf("%d", &Q);
    S.push_back(0);
    
    while(Q--) {
	int type;
	scanf("%d", &type);
	if(type == 1) {
	    int x;
	    scanf("%d", &x);
	    add(x);
	}
	else printf("%.15lf\n", ans);
    }

    return 0;
}
