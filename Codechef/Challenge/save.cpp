#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr, args);

typedef long long ll;

const int MAX = 1e5 + 10;
const int maxn = 1;
const int maxPrimes = 9600;

int n, q;
int a[maxn];

bool prime[MAX];

vector<int> primes[MAX];
vector<int> Div[MAX];
vector<int> p;

void sieve() {
    prime[1] = true;
    for(int i = 2; i < MAX; ++i) {
	for(int j = i; j < MAX; j += i) {
	    Div[j].push_back(i);
	    if(!prime[i]) {
		primes[j].push_back(i);
		if(i != j) prime[j] = true;
	    }
	}
	if(!prime[i]) p.push_back(i);
    }

    cout << p.size() << endl;
}

struct BIT {
    short bit[maxn];

    void add(int idx, int val) {
	while(idx <= n) {
	    bit[idx] += val;
	    idx += (idx & -idx);
	}
    }

    int get(int idx) {
	int ans = 0;
	while(idx > 0) {
	    ans += bit[idx];
	    idx -= (idx & -idx);
	}
	return ans;
    }

    int query(int l, int r) {
	return get(r) - get(l - 1);
    }
} Tree[maxPrimes];

void change(int x, bool flag) {
    // for(auto k: Div[a[x]]) 
    // 	update(1, 1, n, x, k, flag);
}


int get(int l, int r, int g) {
    int ans = 0;
    int sz = (int)primes[g].size();
   
    for(int mask = 1; mask < (1 << sz); ++mask) {
	int m = 1;
	int cnt = 0;
	for(int i = 0; i < primes[g].size(); ++i)
	    if((1 << i) & mask) {
		++cnt;
		m *= primes[g][i];
	    }

    // 	if(cnt & 1) ans += query(1, 1, n, l, r, m);
    // 	else ans -= query(1, 1, n, l, r, m);
    }
    return r - l + 1 - ans;
}

int main() {
    cin.sync_with_stdio(false);

    sieve();
    
    cin >> n;

    for(int i = 1; i <= n; ++i) {
	cin >> a[i];
	change(i, true);
    }
    
    cin >> q;
    
    while(q--) {
	int type;
	cin >> type;

	if(type == 1) {
	    int x, y;
	    cin >> x >> y;

	    change(x, false);
	    a[x] = y;
	    change(x, true);
	}

	if(type == 2) {
	    int l, r, g;
	    cin >> l >> r >> g;
	    cout << get(l, r, g) << '\n';
	}
    }
}
