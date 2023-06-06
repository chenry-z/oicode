#include <bits/stdc++.h>
using i64 = long long;
struct Trie {
	std::vector<std::array<int, 2>> f;
	std::vector<int> _;
	Trie() : f(1), _(1) {
		f.reserve(3E7);
		_.reserve(3E7);
	}
	void Insert(int id, i64 x) {
		int p = 0;
		for (int i = 59; i >= 0; --i) {
			int c = x >> i & 1;
			if (f[p][c] == 0) {
				f[p][c] = f.size();
				f.push_back({});
				_.push_back(0);
			}
			p = f[p][c];
		}
		_[p] = id;
	}
	int Query(i64 x) {
		int p = 0;
		for (int i = 59; i >= 0; --i) {
			int c = x >> i & 1;
			if (f[p][c ^ 1]) p = f[p][c ^ 1];
			else p = f[p][c];
		}
		return _[p];
	}
};
template<class T>
void ChkMax(T &x, T y) {
	if (x < y) x = y;
}
int main() {
	int n;
	std::cin >> n;
	std::vector<int> fa(n, -1);
	std::vector<std::vector<int>> e(n);
	std::vector<i64> a(n), ans(n, -1);
	for (int i = 1; i < n; ++i) {
		std::cin >> fa[i];
		--fa[i];
		e[fa[i]].emplace_back(i);
	}
	Trie f;
	std::tuple<i64, int, int> fans;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		f.Insert(i, a[i]);
		int id = f.Query(a[i]);
		ChkMax(fans, {a[i] ^ a[id], id, i});
	}
	std::vector<bool> flag(n);
	std::function<void(int, i64)> DFS = [&](int u, i64 mx) {
		ans[u] = mx;
		f.Insert(u, a[u]);
		ChkMax(mx, a[f.Query(a[u])] ^ a[u]);
		std::function<void(int)> Insert = [&](int uu) {
			f.Insert(uu, a[uu]);
			ChkMax(mx, a[f.Query(a[uu])] ^ a[uu]);
			for (auto &vv : e[uu]) Insert(vv);
		};
		for (auto &v : e[u]) if (!flag[v]) Insert(v);
		for (auto &v : e[u]) if (flag[v]) DFS(v, mx);
	};
	auto [ffans, x, y] = fans;
	for (int u = x; u != -1; u = fa[u]) flag[u] = true;
	f = Trie(), DFS(0, 0);
	flag.assign(n, false);
	for (int u = y; u != -1; u = fa[u]) flag[u] = true;
	f = Trie(), DFS(0, 0);
	for (int i = 0; i < n; ++i)
		std::cout << (ans[i] != -1 ? ans[i] : ffans) << '\n';
	return 0;
}