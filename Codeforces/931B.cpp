#include "bits/stdc++.h"
using namespace std;

const int maxn = 256 + 10;

int n, a, b;
bool mrk[maxn];

void solve() {
    vector<int> ids;
    for(int i = 1; i <= n; ++i) ids.push_back(i);
    mrk[a] = mrk[b] = true;

    for(int k = 1; ; ++k) {
	vector<int> winners;
	
	if(ids.size() == 2) {
	    printf("Final!\n");
	    return;
	}

	for(int i = 0; i < (int)ids.size(); i += 2) {
	    int x = ids[i];
	    int y = ids[i + 1];

	    if(mrk[x] && mrk[y]) {
		printf("%d\n", k);
		return;
	    }

	    if(mrk[x]) winners.push_back(x);
	    else winners.push_back(y);
	}

	ids = winners;
    }
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    solve();
    return 0;
}
