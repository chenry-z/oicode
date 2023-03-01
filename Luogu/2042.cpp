#include <bits/stdc++.h>
const int maxN = 4E6 + 5;
struct SplayTree {
	int rt, tol = 0, sz[maxN], son[maxN][2], fa[maxN], val[maxN], sum[maxN], lmax[maxN], rmax[maxN], ans[maxN];
	bool swp[maxN], tag[maxN];
	std::vector<int> trash;
	bool Get(int x) {return x == son[fa[x]][1];}
	void PushUp(int x) {
		sz[x] = sz[son[x][0]] + sz[son[x][1]] + 1;
		sum[x] = sum[son[x][0]] + sum[son[x][1]] + val[x];
		lmax[x] = std::max(lmax[son[x][0]], val[x] + sum[son[x][0]] + std::max(lmax[son[x][1]], 0));
		rmax[x] = std::max(rmax[son[x][1]], val[x] + sum[son[x][1]] + std::max(rmax[son[x][0]], 0));
		ans[x] = std::max({ans[son[x][0]], ans[son[x][1]], std::max(0, lmax[son[x][1]]) + std::max(0, rmax[son[x][0]]) + val[x]});
	}
	void PushDown(int x) {
		if (swp[x]) {
			std::swap(lmax[son[x][0]], rmax[son[x][0]]);
			std::swap(lmax[son[x][1]], rmax[son[x][1]]);
			std::swap(son[x][0], son[x][1]);
			swp[son[x][0]] ^= 1;
			swp[son[x][1]] ^= 1;
			swp[x] = 0;
		}
		if (!tag[x]) return;
		if (son[x][0] != 0) {
			tag[son[x][0]] = true;
			val[son[x][0]] = val[x];
			sum[son[x][0]] = val[x] * sz[son[x][0]];
			lmax[son[x][0]] = std::max(0, val[x] * sz[son[x][0]]);
			rmax[son[x][0]] = std::max(0, val[x] * sz[son[x][0]]);
			ans[son[x][0]] = std::max(val[x], val[x] * sz[son[x][0]]);
		}
		if (son[x][1] != 0) {
			tag[son[x][1]] = true;
			val[son[x][1]] = val[x];
			sum[son[x][1]] = val[x] * sz[son[x][1]];
			lmax[son[x][1]] = std::max(0, val[x] * sz[son[x][1]]);
			rmax[son[x][1]] = std::max(0, val[x] * sz[son[x][1]]);
			ans[son[x][1]] = std::max(val[x], val[x] * sz[son[x][1]]);
		}
		tag[x] = false;
	}
	void Rotate(int x) {
		int y = fa[x], z = fa[y], chk = Get(x);
		son[y][chk] = son[x][!chk];
		if (son[x][!chk] != 0) fa[son[x][!chk]] = y;
		fa[fa[son[x][!chk] = y] = x] = z;
		if (z != 0) son[z][y == son[z][1]] = x;
		PushUp(y);
		PushUp(x);
	}
	void Splay(int x, int k) {
		for (int f; (f = fa[x]) != k; Rotate(x))
			if (fa[f] != k) Rotate(Get(f) == Get(x) ? f : x);
		if (k == 0) rt = x;
	}
	int Find(int x) {
		for (int cur = rt; PushDown(cur), true;) {
			if (x <= sz[son[cur][0]]) cur = son[cur][0];
			else {
				x -= sz[son[cur][0]] + 1;
				if (x == 0) return cur;
				cur = son[cur][1];
			}
		}
		return 0;
	}
	void NewNode(int &x, int v, int f) {
		if (trash.empty()) x = ++tol;
		else x = trash.back(), trash.pop_back();
		val[x] = sum[x] = ans[x] = v;
		lmax[x] = rmax[x] = std::max(v, 0);
		fa[x] = f;
		sz[x] = 1;
		tag[x] = swp[x] = false;
		PushUp(x);
	}
	void Insert(int x, int w) {
		Splay(Find(x), 0);
		Splay(Find(x + 1), rt);
		NewNode(son[son[rt][1]][0], w, son[rt][1]);
		PushUp(son[rt][1]);
		PushUp(rt);
	}
	void Recycle(int x) {
		int &l = son[x][0], &r = son[x][1];
		if (l) Recycle(l);
		if (r) Recycle(r);
		trash.push_back(x);
		l = r = fa[x] = 0;
		swp[x] = tag[x] = false;
		val[x] = sum[x] = lmax[x] = rmax[x] = 0;
	}
	void Delete(int l, int r) {
		Splay(Find(l), 0);
		Splay(Find(r + 2), rt);
		Recycle(son[son[rt][1]][0]);
		son[son[rt][1]][0] = 0;
		PushUp(son[rt][1]);
		PushUp(rt);
	}
	void Replace(int l, int r, int w) {
		Splay(Find(l), 0);
		Splay(Find(r + 2), rt);
		int x = son[son[rt][1]][0];
		tag[x] = true;
		val[x] = w;
		sum[x] = w * sz[x];
		lmax[x] = std::max(0, w * sz[x]);
		rmax[x] = std::max(0, w * sz[x]);
		ans[x] = std::max(w, w * sz[x]);
		PushDown(x);
		PushUp(son[son[rt][1]][0]);
		PushUp(son[rt][1]);
		PushUp(rt);
	}
	void Reverse(int l, int r) {
		Splay(Find(l), 0);
		Splay(Find(r + 2), rt);
		swp[son[son[rt][1]][0]] ^= 1;
		PushDown(son[son[rt][1]][0]);
		PushUp(son[son[rt][1]][0]);
		PushUp(son[rt][1]);
		PushUp(rt);
	}
	int QuerySum(int l, int r) {
		Splay(Find(l), 0);
		Splay(Find(r + 2), rt);
		return sum[son[son[rt][1]][0]];
	}
	int QueryMax() {
		return ans[rt];
	}
	SplayTree() {
		val[0] = lmax[0] = rmax[0] = ans[0] = -1E9;
		NewNode(rt, -1E9, 0);
		NewNode(son[rt][1], -1E9, rt);
	}
} tree;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	for (int i = 0, x; i < n; ++i) {
		std::cin >> x;
		tree.Insert(i + 1, x);
	}
	for (int pos, tol, w; m--;) {
		std::string s;
		std::cin >> s;
		char c = s[0];
		if (c == 'I') {
			std::cin >> pos >> tol;
			for (int i = 0, x; i < tol; ++i) {
				std::cin >> x;
				tree.Insert(pos + i + 1, x);
			}
		} else if (c == 'D') {
			std::cin >> pos >> tol;
			tree.Delete(pos, pos + tol - 1);
		} else if (s[2] == 'K') {
			std::cin >> pos >> tol >> w;
			tree.Replace(pos, pos + tol - 1, w);
		} else if (c == 'R') {
			std::cin >> pos >> tol;
			tree.Reverse(pos, pos + tol - 1);
		} else if (c == 'G') {
			std::cin >> pos >> tol;
			std::cout << tree.QuerySum(pos, pos + tol - 1) << '\n';
		} else std::cout << tree.QueryMax() << '\n';
	}
	return 0;
}