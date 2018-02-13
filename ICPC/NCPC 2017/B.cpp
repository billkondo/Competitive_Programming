#include "bits/stdc++.h"
using namespace std;

typedef pair<double, int> pii;
const int maxn = 5e2 + 10;

int n;
string s[maxn];
double a[maxn], b[maxn];

double t = 1e9;
vector<int> ans;

void solve() {
  for(int i = 1; i <= n; ++i) {
    double cmp = a[i];

    priority_queue<pii> T;

    vector<int> ids;
    ids.push_back(i);
    for(int j = 1; j <= n; ++j)
      if(i != j) 
	T.push({-b[j], j});

    for(int k = 0; k < 3; ++k) {
      cmp -= T.top().first;
      ids.push_back(T.top().second);
      T.pop();
    }

    if(cmp < t) {
      t = cmp;
      ans = ids;
    }
  }
}

int main() {
  cin >> n;
  for(int i = 1; i <= n; ++i) cin >> s[i] >> a[i] >> b[i];
  solve();
  cout << fixed << setprecision(10) << t << endl;
  for(int i = 0; i < 4; ++i) cout << s[ans[i]] << endl;
  return 0;
}
