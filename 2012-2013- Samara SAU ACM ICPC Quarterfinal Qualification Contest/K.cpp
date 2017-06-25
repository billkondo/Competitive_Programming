#include "bits/stdc++.h"
using namespace std;

string s;

bool solve()
{
	int n = s.size();
	vector <int> vec;
	for(int i = 0; i < n; ++i)
		if(s[i] == ')')
		{
			if(vec.empty()) return false;
			vec.pop_back();
		}
		else vec.push_back(i);	
	while(!vec.empty()) s.push_back(')'), vec.pop_back();
}

int main()
{	
	cin >> s;
	if(solve()) cout << s << '\n';
	else cout << "IMPOSSIBLE\n";
	
	return 0;
}
