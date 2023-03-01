#include <bits/stdc++.h>
using namespace std;
struct DSU {
	vector<int> fa, val;
	vector<vector<int>> bel;
	DSU(int n) : fa(n), val(n), bel(n) { iota(fa.begin(), fa.end(), 0); }
	void Init(int x) { fa[x] = x, bel[x].clear(), bel[x].emplace_back(x); }
	int Find(int x) {
		while (x != fa[x]) x = fa[x] = fa[fa[x]];
		return x;
	}
	void Merge(int x, int y) {
		if ((x = Find(x)) == (y = Find(y))) return;
		if (bel[x].size() > bel[y].size()) swap(x, y);
		fa[x] = y;
		for (auto c : bel[x]) bel[y].emplace_back(c);
	}
};
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	using Info = pair<int, int>;
	int n, m, q;
	cin >> n >> m >> q;
	vector<Info> a(m), _Q;
	vector<pair<int, Info>> ans;
	for (int i = 0; i < m; ++i) cin >> a[i].first >> a[i].second, _Q.emplace_back(4, i);
	for (int op, x, y; q--;) {
		cin >> op >> x;
		if (op == 4) cin >> y, _Q.emplace_back(op, a.size()), a.emplace_back(x, y);
		else if (op != 1) _Q.emplace_back(op, x);
		else _Q.emplace_back(op, ans.size()), ans.emplace_back(x - 1, a[x - 1]);
	}
	vector<bool> vis(a.size());
	DSU dsu[2] = {DSU(a.size()), DSU(a.size())};
	function<void(int, int, vector<Info>)> Solve = [&](int sx, int sy, vector<Info> Q) {
		if (Q.empty() || sx + sy == n) {
			for (auto [op, _x] : Q) if (op == 1) ans[_x].second = a[ans[_x].first];
			return;
		}
		int p[] = {(sx + n - sy) / 2, n - (sx + n - sy) / 2};
		vector<Info> nQ[2];
		set<Info> q[2];
		for (auto [op, _x] : Q) {
			if (op == 1) {
				auto [x, y] = a[ans[_x].first];
				if (x > p[0]) nQ[1].emplace_back(op, _x);
				else if (y > p[1]) nQ[0].emplace_back(op, _x);
				else ans[_x] = {op, {dsu[0].val[dsu[0].Find(ans[_x].first)], dsu[1].val[dsu[1].Find(ans[_x].first)]}};
			} else if (op == 4) {
				auto [x, y] = a[_x];
				if (x > p[0]) nQ[1].emplace_back(4, _x);
				else if (y > p[1]) nQ[0].emplace_back(4, _x);
				else {
					dsu[0].Init(_x), dsu[1].Init(_x);
					dsu[0].val[_x] = x, dsu[1].val[_x] = y;
					q[0].emplace(x, _x), q[1].emplace(y, _x), vis[_x] = true;
				}
			} else if (_x >= p[!(op -= 2)]) {
				if (_x > p[!op]) nQ[op].emplace_back(op + 2, _x);
				int now = -1;
				while (q[op].size() && q[op].begin() -> first <= n - _x) {
					int id = q[op].begin() -> second;
					q[op].erase(q[op].begin());
					if (now == -1) now = id;
					else dsu[op].Merge(now, id), now = dsu[op].Find(now);
				}
				if (now != -1) dsu[op].val[now] = n - _x, q[op].emplace(n - _x, now);
			} else {
				nQ[!op].emplace_back(op + 2, _x);
				while (q[!op].size() && q[!op].begin() -> first <= _x) {
					int id = q[!op].begin() -> second;
					q[!op].erase(q[!op].begin());
					for (auto c : dsu[!op].bel[id]) if (vis[c]) {
						a[c] = {n - _x, dsu[!op].val[dsu[!op].Find(id)]};
						if (op) swap(a[c].first, a[c].second);
						nQ[!op].emplace_back(4, c);
						vis[c] = false;
					}
				}
			}
		}
		Solve(sx, p[1] + 1, nQ[0]), Solve(p[0] + 1, sy, nQ[1]);
	};
	Solve(0, 0, _Q);
	for (auto [id, x] : ans) cout << x.first << ' ' << x.second << '\n';
	return 0;
}