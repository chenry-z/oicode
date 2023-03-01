#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int N, X;
	cin >> N >> X;
	vector<int> a(N), b(N);
	for (int i = 0; i < N; ++i) cin >> a[i] >> b[i];
	long long ans = INT64_MAX, sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += a[i] + b[i];
		ans = min(ans, sum + 1ll * (X - i - 1) * b[i]);
		if (X == i + 1) break;
	}
	cout << ans;
	return 0;
}