#include "bits/stdc++.h"
using namespace std;
     
#define debug(args...) fprintf(stderr, args);
#define gc getchar_unlocked
     
typedef long long ll;
     
const int MAX = 1e5 + 10;
const int maxn = 4e5 + 10;
     
int n, q;
int a[maxn];
     
bool prime[MAX];
     
vector<int> primes[MAX];
     
inline void sieve() {
    prime[1] = true;
    for(int i = 2; i < MAX; ++i)
	if(!prime[i])
	    for(int j = i; j < MAX; j += i) {	        
		primes[j].push_back(i);
		if(i != j) prime[j] = true;
	    }
}

typedef struct node * pnode;
     
struct node {
    int sum;
    pnode left, right;

    node() {
	sum = 0;
	left = right = NULL;
    }
};

pnode root[MAX];

int getSum(pnode cur) {
    if(!cur) return 0;
    return cur->sum;
}

void update(pnode cur, int i, int j, int pos, int val) {
    if(i == j) {
	cur->sum += val;
	return;
    }
    int mid = (i + j) >> 1;
    if(pos <= mid) {
	if(!cur->left) cur->left = new node();
	update(cur->left, i, mid, pos, val); 
    }
    else {
	if(!cur->right) cur->right = new node();
	update(cur->right, mid + 1, j, pos, val);
    }
    cur->sum = getSum(cur->left) + getSum(cur->right);
}

int query(pnode cur, int i, int j, int l, int r) {
    if(!cur || i > j || j < l || r < i) return 0;
    if(l <= i && j <= r) return getSum(cur);
    int mid = (i + j) >> 1;
    return query(cur->left, i, mid, l, r) + query(cur->right, mid + 1, j, l, r);
}
     
void change(int x, bool flag) {
    int sz = (int)primes[a[x]].size();
    for(int mask = 1; mask < (1 << sz); ++mask) {
	int m = 1;
	for(int i = 0; i < primes[a[x]].size(); ++i)
	    if((1 << i) & mask) 
		m *= primes[a[x]][i];
	update(root[m], 1, n, x, flag ? +1 : -1);
    }
}   
     
inline int get(int l, int r, int g) {
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
     
    	if(cnt & 1) ans += query(root[m], 1, n, l, r);
    	else ans -= query(root[m], 1, n, l, r);
    }
    
    return r - l + 1 - ans;
}

void read (int &x)
{
    register int c = gc();
    x = 0;
    int neg = 0;
    for(; (c < '0' || c > '9') && c != '-'; c = gc());
    if(c == '-') neg = 1 ,c = gc();
    for(; c >= '0' && c <= '9'; c = gc()) x =(x << 1) + (x << 3) + c - '0';
    if(neg == 1) x =- x;
}
     
int main() {
    for(int i = 1; i < MAX; ++i) root[i] = new node();

    sieve();
     
    read(n);
    for(int i = 1; i <= n; ++i) {
	read(a[i]);
    	change(i, true);
    }

    read(q);
        
    while(q--) {
    	int type;
    	read(type);
     
    	if(type == 1) {
    	    int x, y;
    	    read(x);
	    read(y);
     
    	    change(x, false);
    	    a[x] = y;
    	    change(x, true);
    	}
     
    	if(type == 2) {
    	    int l, r, g;
    	    read(l);
	    read(r);
	    read(g);
    	    printf("%d\n", get(l, r, g));
    	}
    }

    return 0;
}
     
