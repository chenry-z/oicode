#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int N, M, X, T, D;
	cin >> N >> M >> X >> T >> D;
	if (M >= X) std::cout << T;
	else std::cout << T - D * (X - M);
	return 0;
}