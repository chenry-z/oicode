#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) std::cin >> a[i];
	std::vector<std::array<int, 5>> Q(q);
	std::vector<std::vector<std::pair<int, int>>> O(n + 1);
	for (int i = 0; i < q; ++i) {
		auto &[l, r, x, y, m] = Q[i];
		std::cin >> l >> r >> x >> y >> m;
		x %= m, y %= m;
		if (l > 1) O[l - 1].emplace_back(i, -1);
		O[r].emplace_back(i, 1);
	}
	std::vector<int> ans(q);
	constexpr int B = 600, N = 100000;
	std::vector<std::vector<int>> F(B + 1);
	for (int i = 1; i <= B; ++i) F[i].resize(i);
	std::vector<int> block(N + 1), L((N + B - 1) / B + 1), R((N + B - 1) / B + 1);
	for (int i = 1, j; i <= N; i = j + 1) {
		j = std::min(N, (i + B - 1) / B * B);
		int blk = (j + B - 1) / B;
		L[blk] = i, R[blk] = j;
		for (int k = i; k <= j; ++k) block[k] = blk;
	}
	std::vector<int> G1(block[N] + 1), G2(N + 1);
	auto Insert = [&](int x) {
		for (int i = 1; i <= B; ++i) ++F[i][x % i];
		for (int i = x; i <= R[block[x]]; ++i) ++G2[i];
		for (int i = block[x]; i <= block[n]; ++i) ++G1[i];
	};
	auto Query = [&](int l, int r) {
		int bL = block[l], bR = block[r];
		if (bL == bR) return l == L[bL] ? G2[r] : G2[r] - G2[l - 1];
		return G2[R[bL]] - (l == L[bL] ? 0 : G2[l - 1]) + G2[r] + G1[bR - 1] - G1[bL];
	};
	for (int i = 1; i <= n; ++i) {
		Insert(a[i]);
		for (auto [id, op] : O[i]) {
			auto [l, r, x, y, m] = Q[id];
			int ret = 0;
			if (x == y) continue;
			if (x > y) std::swap(x, y);
			if (m <= B)
				for (int i = m - y; i < m - x; ++i) ret += F[m][i];
			else {
				for (int i = 1; ; ++i) {
					int l = i * m - y, r = i * m - x - 1;
					if (l > N) break;
					if (r > N) r = N;
					ret += Query(l, r);
				}
			}
			ans[id] += op * ret;
		}
	}
	for (int i = 0; i < q; ++i) {
		auto [l, r, x, y, m] = Q[i];
		std::cout << ((x < y) ? r - l + 1 - ans[i] : ans[i]) << '\n';
	}
	return 0;
}