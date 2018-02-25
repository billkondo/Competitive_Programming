#include "bits/stdc++.h"
using namespace std;

#define debug(args...) //fprintf(stderr, args);

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 2e5 + 10;
const int alpha = 30;

int t, n, m;
string w, s, S;

ll mod[] = {(ll)1e9 + 7, (ll)1e9 + 9};
ll base[] = {29, 43};

int f[alpha], g[alpha];
ll Hash[2][N];
ll pot[2][N];

inline ll get(int id, int l, int r) {
    ll sum = (Hash[id][r] - Hash[id][l - 1] + mod[id]) % mod[id];
    ll div = pot[id][l - 1];
    return (sum * div) % mod[id];
}

ll fpow(int id, ll a, ll b) {
    if(!b) return 1LL;
    if(b & 1LL) return (a * fpow(id, a, b - 1)) % mod[id];
    ll c = fpow(id, a, b / 2);
    return (c * c) % mod[id];
}

inline bool check() {
    for(int i = 0; i < alpha; ++i)
	if(f[i] != g[i])
	    return false;
    return true;
}

inline pii query(int l, int r) {
    ll x = get(0, l, r);
    ll y = get(1, l, r);
    return {x, y};
}

int solve() {
    n = (int)w.size();
    m = (int)s.size();

    for(int k = 0; k < 2; ++k) {
	pot[k][0] = 1LL;
	for(int i = 1; i <= m; ++i) {
	    Hash[k][i] = (Hash[k][i - 1] + (s[i - 1] - 'a') * pot[k][i - 1]) % mod[k];
	    pot[k][i] = (pot[k][i - 1] * base[k]) % mod[k];
	}
	
	for(int i = 1; i <= m; ++i) pot[k][i] = fpow(k, pot[k][i], mod[k] - 2);
    }

    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));

    for(int i = 1; i <= n; ++i) ++f[w[i - 1] - 'a'];
    
    map<pii, int> cnt;
    int ok = 0;

    for(int i = 0; i < alpha; ++i) if(!f[i]) ++ok;

    for(int i = 1; i < n; ++i) {
	int x = s[i - 1] - 'a';
	if(f[x] == g[x]) --ok;
	++g[x];
	if(f[x] == g[x]) ++ok;
    }
    
    for(int i = n; i <= m; ++i) {
	pii h = query(i - n + 1, i);
	int x = s[i - 1] - 'a';
	
	if(f[x] == g[x]) --ok;
	++g[x];
	if(f[x] == g[x]) ++ok;
	
	if(i - n) {
	    int y = s[i - n - 1] - 'a';
	    if(f[y] == g[y]) --ok;
	    --g[s[i - n - 1] - 'a'];
	    if(f[y] == g[y]) ++ok;
	}
	
	if(check()) ++cnt[h];
    }

    int ans = 0;
    for(auto i: cnt) ans = max(ans, i.second);
    
    if(!ans) return false;

    map<pii, int> mrk;
    int pos = -1;

    for(int i = n; i <= m; ++i) {
	pii h = query(i - n + 1, i);
	
	if(cnt[h] != ans) continue;
	if(mrk.find(h) != mrk.end()) continue;

	mrk[h] = true;

	if(pos != -1) {
	    int l = 0;
	    int r = n - 1;

	    int POS = i - n + 1;
	    
	    while(l < r) {
		int mid = (l + r + 1) >> 1;
		pii A = query(POS, POS + mid - 1);
		pii B = query(pos, pos + mid - 1);
		if(A != B) r = mid - 1;
		else l = mid;
	    }

	    if(s[POS + r - 1] < s[pos + r - 1]) 
		pos = POS;
	}
	else 
	    pos = i - n + 1;
    }

    S.clear();
    for(int i = pos; i <= pos + n - 1; ++i)
	S.push_back(s[i - 1]);
    
    return true;
}

int main() {
    cin.sync_with_stdio(false);
    cin >> t;
    while(t--) {
	cin >> w >> s;
	if(solve()) cout << S << '\n';
	else cout << -1 << '\n';
    }
    return 0;
}
