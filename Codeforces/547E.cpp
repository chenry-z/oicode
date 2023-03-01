#include <bits/stdc++.h>
struct ACAutomaton {
	const static int sigma = 26;
	using Info = std::array<int, sigma>;
	std::vector<Info> nxt;
	std::vector<int> fail, pos, fa;
	ACAutomaton(int n = 1) : nxt(n), fa(n) {}
	void Insert(std::string s) {
		int p = 0;
		for (auto &c : s) {
			if (nxt[p][c - 'a'] == 0) {
				fa.push_back(p);
				nxt[p][c - 'a'] = nxt.size();
				nxt.emplace_back(Info());
			}
			p = nxt[p][c - 'a'];
		}
		pos.push_back(p);
	}
	auto Build() {
		std::queue<int> q;
		fail.resize(nxt.size());
		for (auto &c : nxt[0]) if (c) q.push(c);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < sigma; ++i) {
				if (nxt[u][i] == 0) nxt[u][i] = nxt[fail[u]][i];
				else {
					fail[nxt[u][i]] = nxt[fail[u]][i];
					q.push(nxt[u][i]);
				}
			}
		}
		std::vector<std::vector<int>> ret(nxt.size());
		for (int i = 1; i < (int)nxt.size(); ++i) ret[fail[i]].push_back(i);
		return std::tuple{ret, pos, fa};
	}
} ac;
template<typename T>
class Fenwick {
	const int n;
	std::vector<T> a;
	T _Sum(int x) {
		T res = 0;
		for (; x; x -= x & (-x)) res += a[x];
		return res;
	}
public:
	Fenwick(int n = 0) : n(n), a(n + 1) {}
	void Add(int x, const T &v) {for (; x <= n; x += x & -x) a[x] += v;}
	T Sum(int l, int r) {return _Sum(r) - _Sum(l - 1);}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, q;
	std::cin >> n >> q;
	for (int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;
		ac.Insert(s);
	}
	auto [e, pos, fa] = ac.Build();
	std::vector<int> dfn(e.size()), dfnr(e.size());
	Fenwick<int> bit(e.size());
	int _ = 0;
	std::function<void(int)> DFS = [&](int u) {
		dfn[u] = ++_;
		for (int v : e[u]) DFS(v);
		dfnr[u] = _;
	};
	DFS(0);
	std::vector<int> ans(q);
	std::vector<std::vector<std::array<int, 3>>> f(n);
	for (int i = 0, l, r, x; i < q; ++i) {
		std::cin >> l >> r >> x;
		--x;
		if (l > 1) f[l - 2].push_back({x, i, -1});
		f[r - 1].push_back({x, i, 1});
	}
	for (int i = 0; i < n; ++i) {
		int p = pos[i];
		while (p) bit.Add(dfn[p], 1), p = fa[p];
		for (auto &[x, id, d] : f[i]) {
			ans[id] += d * bit.Sum(dfn[pos[x]], dfnr[pos[x]]);
		}
	}
	for (auto &x : ans) std::cout << x << '\n';
	return 0;
}