#include "bits/stdc++.h"
using namespace std;

double p, q;

int main()
{
	cin >> p >> q;
	p /= 100;
	q /= 100;
	cout << fixed << setprecision(10) << (p * p + q * q) / (p + q) << '\n';
	return 0;
}	
