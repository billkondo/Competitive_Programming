#include "bits/stdc++.h"
using namespace std;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, k, a[maxn];

struct node {
    int ans;
    int Min, Max;
    void merge(node L, node R) {
	ans = max(L.ans, R.ans);
	ans = max(ans, R.Max - L.Min);
	Min = min(L.Min, R.Min);
	Max = max(L.Max, R.Max);
    }
} seg[4 * maxn];

int cnt[maxn];

void update(int idx, int i, int j, int pos) {
    if(i == j) {
	seg[idx].Min = seg[idx].Max = cnt[i];
	seg[idx].ans = 0;
	return;
    }
    int mid = (i + j) >> 1;
    int left = idx << 1;
    int right = left | 1;
    if(pos <= mid) update(left, i, mid, pos);
    else update(right, mid + 1, j, pos);
    seg[idx].merge(seg[left], seg[right]);
}

int solve() {
    for(int i = 1; i <= n; ++i) {
	++cnt[a[i]];
	update(1, 1, n + 1, a[i]);
	if(seg[1].ans > k) return i - 1;
    }
    return n;
}

int main() {
    freopen("nice.in", "r", stdin);
    freopen("nice.out", "w", stdout);
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; ++i) {
	scanf("%d", &a[i]);
	++a[i];
    }
    printf("%d\n", solve());
    return 0;
}
