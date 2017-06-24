#include "bits/stdc++.h"
using namespace std;

double p, q;

int main()
{
	cin >> p >> q;
	p /= 100;
	q /= 100;
	cout << fixed << setprecision(10) << (p/q)+(q/p) << '\n';
	return 0;
}	