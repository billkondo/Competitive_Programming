#include "bits/stdc++.h"
using namespace std;

const int N = 30;
const int M = 1e3 + 10;

int n, m, k;
string s[M];

int problems[M];
int penalty[M];

char c[M][N];
int a[M][N], t[M][N];
int Time[M];

string S[M];
char C[M][N];
int A[M][N], T[M][N];

map<string, int> Map;

bool mrk[M];

struct team {
    string s;
    int problems, penalty, time;
    int id;
};

inline bool operator < (team &a, team &b) {
    if(a.problems > b.problems) return true;
    if(a.problems < b.problems) return false;
    if(a.penalty < b.penalty) return true;
    if(a.penalty > b.penalty) return false;
    if(a.time < b.time) return true;
    if(a.time > b.time) return false;
    if(a.s < b.s) return true;
    return false;
}

vector<team> Teams; 

bool solve() {
    for(int i = 1; i <= k; ++i) {
	int id = Map[S[i]];
	mrk[id] = true;
	problems[id] = penalty[id] = Time[id] = 0;
	for(int j = 1; j <= n; ++j) 
	    if(C[i][j] == '+') {
		++problems[id];
		penalty[id] += (A[i][j] - 1) * 20 + T[i][j];
		Time[id] = max(Time[id], T[i][j]);
	    }

	if(i > 1) {
	    int last = Map[S[i - 1]];
	    if(problems[last] < problems[id] || (problems[last] == problems[id] && penalty[last] > penalty[id])
	       || (problems[last] == problems[id] && penalty[last] == penalty[id] && Time[last] > Time[id])
	       || (problems[last] == problems[id] && penalty[last] == penalty[id] && Time[last] == Time[id] && s[last] > s[id]))
		return false;
	}
    }
    for(int i = 1; i <= m; ++i) Teams.push_back({s[i], problems[i], penalty[i], Time[i], i});
    sort(Teams.begin(), Teams.end());

    int First = 0;
    while(First < m && !mrk[Teams[First].id]) ++First;
    if(Teams[First].problems < n) return true;
    
    int Last = m - 1;
    while(Last >= 0 && !mrk[Teams[Last].id]) --Last;

    for(int i = First + 1; i < Last; ++i) {
	int id = Teams[i].id;
	if(mrk[id]) continue;
	int pen = Teams[i].penalty;
	for(int j = 1; j <= n; ++j)
	    if(c[id][j] != '+') pen += a[id][j] * 20 + 240;
	
	if(pen > Teams[First].penalty || (pen == Teams[First].penalty && Teams[First].time > 240)
	   || (pen == Teams[First].penalty && Teams[First].time == 240 && Teams[i].s > Teams[First].s))
	    return false;
    }
    
    return true;
}

int main() {
    cin.sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i = 1; i <= m; ++i) {
	cin >> s[i];
	Map[s[i]] = i;
	for(int j = 1; j <= n; ++j) {
	    cin >> c[i][j] >> a[i][j] >> t[i][j];
	    if(c[i][j] == '+') {
		++problems[i];
		penalty[i] += (a[i][j] - 1) * 20 + t[i][j];
		Time[i] = max(Time[i], t[i][j]);
	    }
	}
    }
    for(int i = 1; i <= k; ++i) {
	cin >> S[i];
	for(int j = 1; j <= n; ++j)
	    cin >> C[i][j] >> A[i][j] >> T[i][j];
    }
    if(solve()) cout << "Leaked\n";
    else cout << "Fake\n";
    return 0;
}
