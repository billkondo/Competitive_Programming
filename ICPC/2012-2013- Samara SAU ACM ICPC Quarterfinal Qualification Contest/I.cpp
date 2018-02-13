#include "bits/stdc++.h"
using namespace std;

#define debug(args...) fprintf(stderr,args)

const int maxn = 2e5 + 10;

int n, t[maxn], c[maxn];

struct node
{
	int maior,lazy;
}seg[4*maxn];

inline void refresh(int idx, int i, int j)
{
	if(!seg[idx].lazy) return;
	int left = idx << 1;
	int right = left | 1;
	if(i != j)
	{
		seg[left].lazy += seg[idx].lazy;
		seg[right].lazy += seg[idx].lazy;
	}
	if(seg[idx].maior != -1) seg[idx].maior += seg[idx].lazy;
	seg[idx].lazy = 0;
}

inline void build(int idx, int i, int j)
{
	if(i == j)
	{
		seg[idx].maior = -1;
		return;
	}
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	build(left,i,mid);
	build(right,mid + 1,j);
	seg[idx].maior = -1;
}

inline void update(int idx, int i, int j, int ini, int fim)
{
	refresh(idx,i,j);
	if(i > j || j < ini || fim < i) return;
	if(seg[idx].maior == -1) return;
	if(ini <= i && j <= fim)
	{
		++seg[idx].lazy;
		refresh(idx,i,j);
		return;
	}
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;	
	update(left,i,mid,ini,fim);
	update(right,mid + 1,j,ini,fim);
	seg[idx].maior = max(seg[left].maior, seg[right].maior);
}

inline void change(int idx, int i, int j, int pos, int val)
{
	refresh(idx,i,j);
	if(i == j)
	{
		seg[idx].maior = val;
		return;
	}
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	if(pos <= mid) change(left,i,mid,pos,val);
	else change(right,mid + 1,j,pos,val);
	seg[idx].maior = max(seg[left].maior, seg[right].maior);
}

inline int get(int idx, int i, int j, int ini, int fim)
{
	refresh(idx,i,j);
	if(i > j || j < ini || fim < i) return -1;
	if(seg[idx].maior == -1) return -1;
	if(i == j) return i;
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	int q = -1;
	refresh(left,i,mid);
	refresh(right,mid + 1,j);
	if(seg[left].maior > seg[right].maior)
	{ 
		q = get(left,i,mid,ini,fim);
		if(q != -1) return q;
		return get(right,mid + 1,j,ini,fim);
	}
	else
	{
		q = get(right,mid + 1,j,ini,fim);
		if(q != -1) return q;
		return get(left,i,mid,ini,fim);
	}
}

inline int value(int idx,int i,int j,int pos)
{
	refresh(idx,i,j);
	if(i == j)return seg[idx].maior;
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	if(pos <= mid) return value(left,i,mid,pos);
	else return value(right,mid+1,j,pos);
}

int ans[maxn];

int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i) scanf("%d%d",&t[i],&c[i]);
	build(1,1,n);
	for(int i = 1; i <= n; ++i)
	{
		int j = i;
		int T = t[i - 1] + 1;
		while(T < t[i])
		{
			int q = get(1,1,n,1,i);
			if(q == -1) break;
			ans[q] = T; 
			change(1,1,n,q,-1);
			update(1,1,n,1,i-1);
			++T;
		}
		while(j <= n && t[i] == t[j])
		{
			change(1,1,n,j,c[j]); 
			++j;
		}
		i = j - 1;
		int q = get(1,1,n,1,i);
		if(q != -1) 
		{
			ans[q] = t[i]; 
			change(1,1,n,q,-1);
		}
		update(1,1,n,1,i);
	}
	int T = t[n] + 1;
	while(true)
	{
		int q = get(1,1,n,1,n);
		if(q == -1) break;
		ans[q] = T++;
		change(1,1,n,q,-1);
		update(1,1,n,1,n);
	}
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}