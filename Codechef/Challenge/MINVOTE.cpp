#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 10;

int t, n;
int a[maxn];

int ans[maxn];

vector<ll> S;
unordered_map<ll, int> M;
int N;

ll pre[maxn];

void compress() {
    N = 0;
    M.clear();
    sort(S.begin(), S.end());
    for(auto i: S) M[i] = ++N;
}

int bit[3 * maxn];

void add(int idx, int val) {
    while(idx <= N) {
	bit[idx] += val;
	idx += (idx & -idx);
    }
}

int query(int idx) {
    int ret = 0;
    while(idx > 0) {
	ret += bit[idx];
	idx -= (idx & -idx);
    }
    return ret;
}

void init() {
    for(int i = 1; i <= N; ++i) bit[i] = 0;
}

int solve() {
    for(int i = 1; i <= n; ++i) {
	ans[i] = 0;
	pre[i] = pre[i - 1] + a[i];
    }

    S.clear();
    S.push_back(0);
    
    for(int i = 1; i <= n; ++i) {
	S.push_back(pre[i]);
	S.push_back(pre[i] + a[i]);
	S.push_back(pre[i - 1] - a[i]);
    }

    compress();

    init();
    for(int i = 1; i <= n; ++i) {
	int cmp = M[pre[i - 1]];
	ans[i] += (i - 1) - query(cmp - 1);
	add(M[pre[i] + a[i]], +1);
    }

    init();
    for(int i = n; i >= 1; --i) {
	int cmp = M[pre[i]];
	ans[i] += query(cmp);
	add(M[pre[i - 1] - a[i]], +1);
    }
}

int main() {
    cin.sync_with_stdio(false);
    cin >> t;
    while(t--) {
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	solve();
	for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
	cout << '\n';
    }
    return 0;
}
