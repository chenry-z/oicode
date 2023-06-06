#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> L(n), R(n);
	std::vector<int> a;
	for (int i = 0; i < n; ++i) {
		std::cin >> L[i] >> R[i];
		a.emplace_back(L[i]), a.emplace_back(R[i]);
	}
	std::sort(a.begin(), a.end());
	a.erase(std::unique(a.begin(), a.end()), a.end());
	auto P1 = [&](int x, int lo) {
		if (lo < L[x]) return 0.0;
		if (lo > R[x]) return 1.0;
		return double(lo - L[x]) / (R[x] - L[x]);
	};
	std::vector ans(n, std::vector(n * 2, 0.0));
	std::vector sum(n, std::vector(n + 1, std::vector(n + 1, 0.0)));
	for (int p = 1; p < (int)a.size(); ++p) {
		int lo = a[p - 1], hi = a[p];
		std::vector f(n + 1, std::vector<double>());
		for (int i = 0; i <= n; ++i) f[i].resize(n - i + 1);
		f[0][0] = 1;
		auto Trans = [&](int x, int &cnt) {
			double p1 = P1(x, lo), p2 = P1(x, hi);
			for (int i = cnt; i >= 0; --i)
				for (int j = cnt - i; j >= 0; --j) {
					f[i + 1][j] += f[i][j] * p1;
					f[i][j + 1] += f[i][j] * (p2 - p1);
					f[i][j] = f[i][j] * (1 - p2);
				}
			++cnt;
		};
		std::function<void(int, int, int)> Solve = [&](int l, int r, int cnt) {
			if (r - l == 1) {
				double cur = P1(l, hi) - P1(l, lo);
				for (int i = 0; i <= cnt; ++i)
					for (int j = 0; i + j <= cnt; ++j)
						sum[l][i][j] += f[i][j] * cur;
				return;
			}
			int m = (l + r) >> 1, backup_cnt = cnt;
			auto backup = f;
			for (int i = l; i < m; ++i) Trans(i, cnt);
			Solve(m, r, cnt);
			f = backup, cnt = backup_cnt;
			for (int i = m; i < r; ++i) Trans(i, cnt);
			Solve(l, m, cnt);
		};
		Solve(0, n, 0);
	}
	for (int x = 0; x < n; ++x)
		for (int i = 0; i <= n; ++i)
			for (int j = 0; i + j <= n; ++j)
				for (int k = 1; k <= j + 1; ++k)
					ans[x][i + k] += sum[x][i][j] / (j + 1);
	std::cout << std::fixed << std::setprecision(7);
	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= n; ++j)
			std::cout << ans[i][j] << " \n"[j == n];
	return 0;
}