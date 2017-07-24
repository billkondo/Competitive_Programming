#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define debug(args...) //fprintf(stderr,args)
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define REP(i,a,b) for(int i = a; i >= b; --i)

typedef long long ll;
typedef pair<int,int>pii;

const int maxn = 2e5 + 10;

int n, m;
ll k, d;

struct node{
	ll ans, sum, pre, suf;

	void merge(node L, node R){
		sum = L.sum + R.sum;
		pre = max(L.pre,L.sum+R.pre);
		suf = max(R.suf,R.sum+L.suf);
		ans = max(L.ans,max(R.ans,L.suf+R.pre));
	}

} seg[4 * maxn];

void build(int idx, int i, int j){
	if(i == j){
		seg[idx].ans = seg[idx].sum = seg[idx].pre = seg[idx].suf = -k;
		return;
	}

	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;

	build(left,i,mid);
	build(right,mid+1,j);

	seg[idx].merge(seg[left],seg[right]);
}

void update(int idx, int i, int j, int pos, ll val){
	if(i == j){
		seg[idx].ans += val;
		seg[idx].sum += val;
		seg[idx].pre += val;
		seg[idx].suf += val;
		return;
	}

	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;

	if(pos <= mid) update(left,i,mid,pos,val);
	else update(right,mid+1,j,pos,val);

	seg[idx].merge(seg[left],seg[right]);
}

int main(){
	scanf("%d %d %lld %lld", &n, &m, &k, &d);

	build(1,1,n);

	for(int i = 1; i <= m; ++i){
		int r, x;
		scanf("%d %d", &r, &x);
		update(1,1,n,r,x);

		node q = seg[1];

		debug("ans = %lld\n",q.ans);

		if(q.ans > d * k) printf("NIE\n");
		else printf("TAK\n");
	}

	return 0;
}