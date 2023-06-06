#include <bits/stdc++.h>
#pragma GCC optimize(2)
struct Mat {
	int n;
	std::vector<std::vector<double>> v;
	Mat(int n, int m) : n(n), v(n, std::vector<double>(m, 0)) {}
	Mat operator * (const Mat& rhs) const {
		Mat res(n, n);
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < n; ++k) {
				if (v[i][k] == 0) continue;
				for (int j = 0; j < n; ++j) {
					res.v[i][j] += v[i][k] * rhs.v[k][j];
				}
			}
		}
		return res;
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int N, R, Q, S, m = 1;
	std::cin >> N >> R >> Q >> S;
	std::vector<std::vector<int>> pos(R + 1, std::vector<int>(Q + 1));
	for (int i = 0; i <= R; ++i)
		for (int j = 1; j <= Q; ++j)
			pos[i][j] = m++;
	auto Check = [&](double x) {
		Mat mt(m, m);
		for (int i = 0; i <= R; ++i)
			for (int j = 2; j <= Q; ++j)
				mt.v[pos[i][j]][pos[0][j - 1]] = 1 - x;
		for (int i = 0; i <= R; ++i)
			for (int j = 1; j <= Q; ++j)
				mt.v[pos[i][j]][pos[std::min(R, i + 1)][std::min(Q, j + 1)]] = x;
		for (int i = 0; i <= R; ++i)
			for (int j = 1; j <= Q; ++j)
				mt.v[pos[i][j]][0] = x * std::min(R, i + 1);
		std::vector<double> ans(m);
		mt.v[0][0] = 1;
		ans[0] = x;
		ans[pos[1][Q]] = x;
		if (Q > 1) ans[pos[0][Q - 1]] = 1 - x;
		for (int n = N - 1; n; n >>= 1, mt = mt * mt)
			if (n & 1) {
				std::vector<double> tmp(m);
				for (int k = 0; k < m; ++k)
					for (int j = 0; ans[k] != 0 && j < m; ++j)
						tmp[j] += mt.v[k][j] * ans[k];
				ans = tmp;
			}
		return ans[0] >= S;
	};
	if (!Check(0.999999)) return std::cout << "Impossible." << std::endl, 0;
	double l = 0, r = 1;
	while (r - l > 1e-7) {
		double mid = (l + r) / 2;
		if (Check(mid)) r = mid;
		else l = mid;
	}
	std::cout << std::fixed << std::setprecision(6) << l << '\n';
	return 0;
}