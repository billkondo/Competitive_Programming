#include "bits/stdc++.h"
using namespace std;

bool ok(int x, int y) {
    if(!y) return false;
    if(y == 1) return x == 0;
    return x >= y - 1 && (x - (y - 1)) % 2 == 0;
}

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    if(ok(x, y)) printf("Yes\n");
    else printf("No\n");
    return 0;
}
