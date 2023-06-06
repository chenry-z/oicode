#include <bits/stdc++.h>
std::vector<unsigned long long> P(1);
struct sgt {
	std::vector<std::tuple<unsigned long long, int, int, int>> val;
	void Insert(int &x, int l, int r, int p) {
		val.emplace_back(0, 0, 0, 0);
		if (x != 0) val.back() = val[x];
		x = val.size() - 1;
		auto &[sum, _, ls, rs] = val[x];
		++_;
		sum += P[p];
		if (l == r) return;
		int m = (l + r) >> 1;
		if (p <= m) Insert(ls, l, m, p);
		else Insert(rs, m + 1, r, p);
	}
	int Query(int u, int v, int l, int r) {
		auto [sumu, _u, lsu, rsu] = val[u];
		auto [sumv, _v, lsv, rsv] = val[v];
		int c1 = sumu;
		int c2 = sumv;
		if (c1 == c2) return 0;
		if (c1 == 0 || c2 == 0 || l == r) return _u - _v;
		int m = (l + r) >> 1;
		int cur = Query(rsu, rsv, m + 1, r);
		if (cur == 0) cur = Query(lsu, lsv, l, m);
		return cur;
	}
	sgt(int n) {
		val.reserve(n);
		val.emplace_back(0, 0, 0, 0);
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	std::mt19937_64 rng(std::chrono::steady_clock().now().time_since_epoch().count());
	for (int i = 1; i <= 1E6; ++i) P.emplace_back(rng());
	while (T--) {
		int n, L, R, head = 0;
		std::cin >> n >> L >> R;
		std::vector<int> a(n), b(n), rt(n);
		for (auto &c : a) std::cin >> c;
		for (auto &c : b) std::cin >> c;
		if (n == 1) {
			std::cout << "1\n" << b[0] << '\n';
			continue;
		}
		std::vector<int> q, pre(n, -1);
		sgt st(n << 5);
		st.Insert(rt[0], 1, n, b[0]);
		for (int i = 1, t = 0; i < n; ++i) {
			while (t < n && a[t] <= a[i] - L) {
				while (head < (int)q.size() && st.Query(rt[q.back()], rt[t], 1, n) < 0) q.pop_back();
				q.emplace_back(t++);
			}
			while (head < (int)q.size() && a[q[head]] < a[i] - R) ++head;
			if (head == (int)q.size() || rt[q[head]] == 0) continue;
			pre[i] = q[head];
			st.Insert(rt[i] = rt[q[head]], 1, n, b[i]);
		}
		if (pre[n - 1] == -1) {
			std::cout << "-1\n";
			continue;
		}
		std::vector<int> ans;
		for (int u = n - 1; u != -1; u = pre[u]) ans.emplace_back(b[u]);
		std::cout << ans.size() << '\n';
		std::sort(ans.begin(), ans.end(), std::greater<int>());
		for (auto c : ans) std::cout << c << ' ';
		std::cout << '\n';
		// for (int i = 0; i < n; ++i) std::cout << pre[i] << " \n"[i == n - 1];
	}
	return 0;
}