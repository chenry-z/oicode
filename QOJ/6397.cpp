#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, ans = 0, P = 998244353;
	std::cin >> n;
	std::vector<int> w(n);
	for (auto &c : w) std::cin >> c;
	std::vector<long long> F(1 << n, INT64_MAX / 2);
	F[1] = 0;
	for (int i = 1; i < n; ++i) F[1 << i] = w[n - i];
	auto Min = [&](long long &x, long long y) { x > y ? x = y : x; };
	for (int S = 1; S < (1 << n); ++S)
		for (int i = 0; i < n; ++i)
			Min(F[(S | (S << (n - i)) | (S >> i)) & ((1 << n) - 1)], F[S] + w[i]);
	for (int S = (1 << n) - 1; S; --S)
		for (int i = 0; i < n; ++i)
			if (!(S >> i & 1)) Min(F[S], F[S | (1 << i)]);
	for (int S = 0; S < (1 << n); ++S) (ans += S * F[S] % P) %= P;
	std::cout << ans << '\n';
	return 0;
}