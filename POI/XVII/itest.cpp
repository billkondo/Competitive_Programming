#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define debug(args...) fprintf(stderr,args);
const int maxn = 1e6 + 10;

int m, q;
vector<int>A[maxn];

int main(){
	scanf("%d",&m);
	for(int i = 0; i < m; ++i){
		int a;
		scanf("%d",&a);
		A[a].pb(i);
	}	
	scanf("%d",&q);
	while(q--){
		int n;
		scanf("%d",&n);
		bool yes = true;
		int cur = -1;
		for(int i = 0; i < n; ++i){
			int a;
			scanf("%d",&a);
			if(A[a].empty()){
				yes = false;
				continue;
			}
			if(!yes) continue;
			int _next = upper_bound(A[a].begin(),A[a].end(),cur) - A[a].begin();
			if(_next >= A[a].size()) yes = false;
			else cur = A[a][_next];
		}
		if(yes) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}