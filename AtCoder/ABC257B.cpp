#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int n, k, q;
	cin >> n >> k >> q;
	std::vector<int> a(k), b(n);
	std::vector<int> L(q);
	for (int i = 0; i < k; ++i) cin >> a[i], b[--a[i]] = i;
	while (q--) {
		int c;
		cin >> c;
		--c;
		if (a[c] != n - 1 && b[a[c] + 1] == 0) {
			b[a[c]] = 0;
			b[a[c] + 1] = c;
			a[c]++;
		}
	}
	for (auto &c : a) cout << c << ' ';
	return 0;
}

