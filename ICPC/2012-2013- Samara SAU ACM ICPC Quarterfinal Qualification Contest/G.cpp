#include "bits/stdc++.h"
using namespace std;

string s;

bool solve()
{
	if(s.size() > 26) return false;
	map <char, int> used;
	map <char, int> f;
	for(auto i: s) ++f[i];
	for(int i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		if(!used[c]) used[c] = true;
		else
		{
			bool ok = false;
			for(char l = 'a'; l <= 'z'; ++l)
				if(!used[l] && !f[l])
				{
					--f[c];
					used[l] = true;
					++f[l];
					s[i] = l;
					ok = true;
					break;
				}

			if(!ok)
			{
				for(char l = 'a'; l <= 'z'; ++l)
					if(!used[l])
					{
						used[l] = true;
						s[i] = l;
						break;
					}
			}
		}
	}
}

int main()
{
	cin >> s;
	if(solve()) cout << s << '\n';
	else cout << "IMPOSSIBLE\n";
	
	return 0;
}
