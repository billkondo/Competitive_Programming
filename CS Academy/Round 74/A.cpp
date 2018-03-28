#include "bits/stdc++.h"
using namespace std;

int a, l, h;

int solve() {
    for(int x = 0; x <= a; ++x)
	for(int y = 0; y <= a - x; ++y) {
	    int z = a - (x + y);
	    int Legs = x * 2 + 4 * y + 4 * z;
	    int Horns = y * 2 + z;
	    if(Legs == l && Horns == h) return z;
	}
    return 0;
}

int main() {
    cin >> a >> l >> h;
    cout << solve() << '\n';
    return 0;
}
