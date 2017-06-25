#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
const int maxn = 3e5 + 10;

int n, k;
ll d[maxn];

struct node{
	int sum;
	ll lazy, maior;
	void merge(node L, node R){
		sum = L.sum + R.sum;
		maior = max(L.maior, R.maior);
	}
}seg[4*maxn];

inline void build(int idx, int i, int j){
	if(i == j){
		if(d[i] >= k) seg[idx].sum = 1, seg[idx].maior = -1;
		else seg[idx].maior = d[i];
		return;
	}
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	build(left,i,mid);
	build(right,mid+1,j);
	seg[idx].merge(seg[left],seg[right]);
}

inline void refresh(int idx, int i, int j){
	if(!seg[idx].lazy) return;
	int left = idx << 1;
	int right = left | 1;
	if(i != j){
		seg[left].lazy += seg[idx].lazy;
		seg[right].lazy += seg[idx].lazy;
	}
	if(seg[idx].maior != -1) seg[idx].maior += seg[idx].lazy;
	seg[idx].lazy = 0;
}

inline void update(int idx, int i, int j, int ini, int fim){
	refresh(idx,i,j);
	if(i > j || j < ini || fim < i) return;
	if(seg[idx].maior == -1) return;
	if(ini <= i && j <= fim){
		++seg[idx].lazy;
		refresh(idx,i,j);
		return;
	}
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	update(left,i,mid,ini,fim);
	update(right,mid+1,j,ini,fim);
	seg[idx].merge(seg[left],seg[right]);
}

inline int find(int idx, int i, int j, int ini, int fim){
	refresh(idx,i,j);
	if(seg[idx].maior == -1) return -1;
	if(i > j || j < ini || fim < i) return -1;
	if(i == j) return i;
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	refresh(left,i,mid);
	refresh(right,mid+1,j);
	if(seg[left].maior > seg[right].maior){
		int q = find(left,i,mid,ini,fim);
		if(q != -1) return q;
		return find(right,mid+1,j,ini,fim);
	}
	else{
		int q = find(right,mid+1,j,ini,fim);
		if(q != -1) return q;
		return find(left,i,mid,ini,fim);
	}
}

inline void change(int idx, int i, int j, int pos){
	refresh(idx,i,j);
	if(i == j){
		seg[idx].maior = -1;
		seg[idx].sum = 1;
		return;
	}
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	if(pos <= mid) change(left,i,mid,pos);
	else change(right,mid+1,j,pos);
	seg[idx].merge(seg[left],seg[right]);
}

inline ll solo(int idx, int i, int j, int pos){
	refresh(idx,i,j);
	if(i == j) return seg[idx].maior;
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	if(pos <= mid) return solo(left,i,mid,pos);
	return solo(right,mid+1,j,pos);
}

inline int get(int idx, int i, int j, int ini, int fim){
	refresh(idx,i,j);
	if(i > j || j < ini || fim < i) return 0;
	if(ini <= i && j <= fim) return seg[idx].sum;
	int mid = (i + j) >> 1;
	int left = idx << 1;
	int right = left | 1;
	return get(left,i,mid,ini,fim) + get(right,mid+1,j,ini,fim);
}

void inicjuj(int N, int K, int D[]){
	n = N, k = K;
	for(int i = 1; i <= n; ++i) d[i] = D[i - 1];
	build(1,1,n);
}

void podlej(int a, int b){
	++a, ++b;
	update(1,1,n,a,b);
	int q = find(1,1,n,a,b);
	while(solo(1,1,n,q) >= k)
	{
		change(1,1,n,q);
		q = find(1,1,n,a,b);
	}
}

int dojrzale(int a, int b){
	++a, ++b;
	return get(1,1,n,a,b);
}