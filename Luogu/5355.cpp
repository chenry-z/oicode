#include <bits/stdc++.h>
constexpr int N = 100001, B = 337;
struct Query {
	int op, l, r, id, x;
	bool operator < (const Query &rsh) {
		if (l / B == rsh.l / B) {
			if ((l / B) & 1) return r < rsh.r;
			return r > rsh.r;
		}
		return l < rsh.l;
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1), sum(N);
	for (int i = 1; i <= n; ++i) std::cin >> a[i];
	std::bitset<N> f1, f2;
	auto Plus = [&](int x) {
		return (f1 << (N - x) & f2).any();
	};
	auto Minus = [&](int x) {
		return (f1 << x & f1).any();
	};
	auto Times = [&](int x) {
		for (int i = 1; i <= std::sqrt(x); ++i)
			if (x % i == 0 && f1[i] && f1[x / i]) return true;
		return false;
	};
	auto Divide = [&](int x) {
		for (int i = 1; i * x < N; ++i)
			if (f1[i] && f1[i * x]) return true;
		return false;
	};
	auto Add = [&](int x) {
		f1[x] = f2[N - x] = true;
		++sum[x];
	};
	auto Del = [&](int x) {
		--sum[x];
		if (sum[x] == 0) f1[x] = f2[N - x] = 0;
	};
	std::vector<bool> ans(m);
	std::vector<Query> Q;
	std::vector<std::vector<std::tuple<int, int, int>>> D(B + 1);
	for (int i = 0, op, l, r, x; i < m; ++i) {
		std::cin >> op >> l >> r >> x;
		if (op == 4 && x <= B) D[x].emplace_back(l, r, i);
		else Q.emplace_back(op, l, r, i, x);
	}
	for (int x = 1; x <= B; ++x) {
		std::vector<int> lst(N), pos(n + 1);
		for (int i = 1; i <= n; ++i) {
			lst[a[i]] = i;
			pos[i] = pos[i - 1];
			if (a[i] * x < N) pos[i] = std::max(pos[i], lst[a[i] * x]);
			if (a[i] % x == 0) pos[i] = std::max(pos[i], lst[a[i] / x]);
		}
		for (auto [l, r, id] : D[x]) ans[id] = pos[r] >= l;
	}
	std::sort(Q.begin(), Q.end());
	for (int L = 1, R = 0; auto [op, l, r, id, x] : Q) {
		while (R < r) Add(a[++R]);
		while (L > l) Add(a[--L]);
		while (R > r) Del(a[R--]);
		while (L < l) Del(a[L++]);
		if (op == 2) ans[id] = Plus(x);
		else if (op == 1) ans[id] = Minus(x);
		else if (op == 3) ans[id] = Times(x);
		else ans[id] = Divide(x);
	}
	for (int i = 0; i < m; ++i) std::cout << (ans[i] ? "yuno\n" : "yumi\n");
	return 0;
}