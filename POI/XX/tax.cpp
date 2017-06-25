#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 10;

int N;
long long D, M, X[MAXN];
multiset <long long> Set;

int solve ()
{
	multiset <long long> :: iterator it = Set.begin();

	bool found = false;

	long long bonus = -1;

	while (it != Set.end())
	{
		if ((*it) >= (M - D))
		{
			found = true;

			if ((*it) >= M + D)
				return 1;

			bonus = ((*it) - (M - D)) / 2;

			Set.erase (it);
			break;
		}

		it++;
	}

	if (!found)
		return 0;

	it = Set.begin();

	int pos = 0;
	while (it != Set.end())
	{
		X[++pos] = (*it);
		it++;
	}

	reverse (X + 1, X + 1 + N - 1);

	long long cur = 0;

	for (int i = 1; i <= N - 1; i++)
	{
		if (X[i] <= D - cur)
			return 0;

		X[i] -= (D - cur);

		if (M - cur <= X[i])
			return i;

		if (D - cur - bonus <= X[i])
			return i + 1;

		cur += X[i];
	}

	return 0;
}

int main ()
{
	scanf ("%lld %lld %d", &M, &D, &N);

	for (int i = 1; i <= N; i++)
	{
		long long x;
		scanf ("%lld", &x);
		Set.insert (x);
	}

	printf ("%d\n", solve());

	return 0;
}