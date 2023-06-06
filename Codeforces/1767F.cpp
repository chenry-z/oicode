#include <bits/stdc++.h>
struct Data {
	const int B;
	std::vector<int> sum, mx;
	std::vector<std::vector<int>> val;
	Data(int V, int B, int n) : B(B), sum(V), mx(V / B + 1), val(V / B + 1, std::vector<int>(n + 1)) {
		for (int i = 0; i <= V / B; ++i) val[i][0] = 1E9;
	}
	void Update(const std::pair<bool, int> &w) {
		auto [op, v] = w;
		if (op) {
			--val[v / B][sum[v]];
			++val[v / B][++sum[v]];
			if (val[v / B][mx[v / B] + 1] != 0) ++mx[v / B];
		} else {
			--val[v / B][sum[v]];
			++val[v / B][--sum[v]];
			if (val[v / B][mx[v / B]] == 0) --mx[v / B];
		}
	}
	int Query() {
		int cur = *std::max_element(mx.begin(), mx.end());
		for (int i = 0; i < (int)val.size(); ++i)
			if (cur == mx[i])
				for (int j = i * B; j < (i + 1) * B; ++j)
					if (cur == sum[j]) return j;
		return assert(false), -1;
	}
};
int BB;
struct Query {
	int l, r, id;
	bool operator < (const Query &rsh) {
		if (l / BB == rsh.l / BB) {
			if ((l / BB) & 1) return r < rsh.r;
			return r > rsh.r;
		}
		return l < rsh.l;
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	std::vector<std::vector<int>> e(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i], --a[i];
	for (int i = 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	std::vector<int> son(n, -1), sz(n, 1), pos(n);
	std::function<void(int, int)> DFS = [&](int u, int fa) {
		for (auto v : e[u]) {
			if (v == fa) continue;
			DFS(v, u);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	};
	DFS(0, -1);
	std::vector<std::pair<bool, int>> Q(1);
	DFS = [&](int u, int fa) {
		auto Add = [&](auto self, int uu, int ffa, bool op) -> void {
			Q.emplace_back(op, a[uu]);
			for (auto vv : e[uu])
				if (vv != ffa) self(self, vv, uu, op);
		};
		for (auto v : e[u]) {
			if (v == fa || v == son[u]) continue;
			DFS(v, u);
			Add(Add, v, u, false);
		}
		if (son[u] != -1) DFS(son[u], u);
		for (auto v : e[u]) {
			if (v == fa || v == son[u]) continue;
			Add(Add, v, u, true);
		}
		pos[u] = Q.size();
		Q.emplace_back(true, a[u]);
	};
	DFS(0, -1);
	Data f(*std::max_element(a.begin(), a.end()) + 1, 450, n);
	int q;
	std::cin >> q;
	std::vector<Query> Qq(q);
	std::vector<int> ans(q);
	BB = std::ceil(Q.size() / std::sqrt(q));
	for (int i = 0, l, r; i < q; ++i) {
		std::cin >> l >> r;
		if (pos[l - 1] > pos[r - 1]) std::swap(l, r);
		Qq[i] = {pos[l - 1], pos[r - 1], i};
	}
	std::sort(Qq.begin(), Qq.end());
	for (int L = 0, R = 0; auto [l, r, id] : Qq) {
		while (R < r) f.Update(Q[++R]);
		while (L < l) f.Update(Q[++L]);
		while (R > r) f.Update({!Q[R].first, Q[R].second}), --R;
		while (L > l) f.Update({!Q[L].first, Q[L].second}), --L;
		ans[id] = f.Query();
	}
	for (auto c : ans) std::cout << c + 1 << '\n';
	return 0;
}