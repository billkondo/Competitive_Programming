#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
const int maxn = 1e5 + 10;

int n;
string s[maxn];

struct word {
    ll S, H;
    int id;
};

bool operator < (word a, word b) {
    return a.S * b.H > b.S * a.H;
}

vector<word> S;

ll solve() {
    sort(S.begin(), S.end());
    ll ans = 0;
    ll h = 0;
    for(int i = n - 1; i >= 0; --i) {
	int id = S[i].id;
	for(int k = s[id].size() - 1; k >= 0; --k)
	    if(s[id][k] == 's') ans += h;
	    else ++h;
    }
    return ans;
}

int main() {
    cin.sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
	cin >> s[i];
	int x = 0;
	int y = 0;
	for(auto c: s[i])
	    if(c == 's') ++x;
	    else ++y;
	S.push_back({x, y, i});
    }
    cout << solve() << '\n';
    return 0;
}
