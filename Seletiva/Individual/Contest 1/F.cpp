#include <cstdio>

typedef long long ll;

const int maxn = 2e5 + 10;
const int LOG = 20;

int n, m;

int dp[LOG][maxn];

int st[maxn], ed[maxn], cur;
int h[maxn];

int A[maxn];
int H[maxn];

typedef struct node * pnode;

struct node {
    int vertex;
    pnode nx;

    node() {
	vertex = -1;
	nx = NULL;
    }
};

struct list {
    pnode head, tail;
    list() {
	head = tail = NULL;
    }
};

list Adj[maxn];

void addEdge(int u, int v) {
    pnode newNode = new node();
    newNode->vertex = v;
    if(Adj[u].head == NULL) {
	Adj[u].head = newNode;
	Adj[u].tail = newNode;
    }
    else {
	Adj[u].tail->nx = newNode;
	Adj[u].tail = newNode;
    }
}

void dfs(int v, int par) {
    st[v] = ++cur;
    A[cur] = v;
    H[cur] = h[v];

    pnode Cur = Adj[v].head;
    while(Cur) {
	int u = Cur->vertex;
	if(u != par) {
	    h[u] = h[v] + 1;
	    dfs(u, v);
	}
	Cur = Cur->nx;
    }
    
    ed[v] = ++cur;
    A[cur] = par;
    H[cur] = h[par];
}

int N;
int Min[LOG][maxn];
int Node[LOG][maxn];
int Log2[maxn];

void buildRMQ() {
    N = cur;

    for(int i = 1; i <= N; ++i) {
	Min[0][i] = H[i];
	Node[0][i] = A[i];
    }
    
    for(int k = 1; k < LOG; ++k)
	for(int i = 1; i + (1 << k) - 1 <= N; ++i)
	    if(Min[k - 1][i] < Min[k - 1][i + (1 << (k - 1))]) {
		Min[k][i] = Min[k - 1][i];
		Node[k][i] = Node[k - 1][i];
	    }
	    else {
		Min[k][i] = Min[k - 1][i + (1 << (k - 1))];
		Node[k][i] = Node[k - 1][i + (1 << (k - 1))];
	    }

    for(int i = 2; i <= N; ++i) 
	Log2[i] = Log2[i >> 1] + 1;
}

inline int lca(int x, int y) {
    if(st[x] > st[y]) {
	int tmp = x;
	x = y;
	y = tmp;
    }
    int L = st[x];
    int R = st[y];
    int len = Log2[R - L + 1];
    if(Min[len][L] < Min[len][R - (1 << len) + 1]) return Node[len][L];
    return Node[len][R - (1 << len) + 1];
}

int pre[maxn];

inline ll solve() {
    ll ans = 0;
    for(int i = 1; i <= n + n; ++i) pre[i] += pre[i - 1];
    for(int i = 2; i <= n; ++i) {
	int edges = pre[ed[i]] - pre[st[i] - 1];
	if(edges == 1) ++ans;
	else if(!edges) ans += m;
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n - 1; ++i) {
	int a, b;
	scanf("%d %d", &a, &b);
	addEdge(a, b);
	addEdge(b, a);
    }

    dfs(1, 1);
    buildRMQ();
    for(int i = 1; i <=  m; ++i) {
	int a, b;
	scanf("%d %d", &a, &b);
	int c = lca(a, b);
	if(c == a) ++pre[st[b]], --pre[ed[c]];
	else if(c == b) ++pre[st[a]], --pre[ed[c]];
	else pre[ed[c]] -= 2, ++pre[st[a]], ++pre[st[b]];
    }
    printf("%lld", solve());
    return 0;
}
