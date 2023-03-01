#include <bits/stdc++.h>
const int maxN = 2E5 + 5;
struct SplayTree {
	int rt, sz[maxN], son[maxN][2], fa[maxN], val[maxN], sum[maxN], lmax[maxN], rmax[maxN], ans[maxN], tol;
	void Init() {
		val[0] = lmax[0] = rmax[0] = ans[0] = -1E9;
		NewNode(rt, -1E9, 0);
		NewNode(son[rt][1], -1E9, rt);
	}
	void PushUp(int x) {
		sz[x] = sz[son[x][0]] + sz[son[x][1]] + 1;
		sum[x] = sum[son[x][0]] + sum[son[x][1]] + val[x];
		lmax[x] = std::max(lmax[son[x][0]], val[x] + sum[son[x][0]] + std::max(0, lmax[son[x][1]]));
		rmax[x] = std::max(rmax[son[x][1]], val[x] + sum[son[x][1]] + std::max(0, rmax[son[x][0]]));
		ans[x] = std::max({val[x] + std::max(0, lmax[son[x][1]]) + std::max(0, rmax[son[x][0]]), ans[son[x][0]], ans[son[x][1]]});
	}
	bool Get(int x) {return x == son[fa[x]][1];}
	void Rotate(int x) {
		int y = fa[x], z = fa[y], chk = Get(x);
		son[y][chk] = son[x][chk ^ 1];
		if (son[x][chk ^ 1] != 0) fa[son[x][chk ^ 1]] = y;
		fa[fa[son[x][chk ^ 1] = y] = x] = z;
		if (z != 0) son[z][y == son[z][1]] = x;
		PushUp(y);
		PushUp(x);
	}
	void Splay(int x, int k) {
		for (int f; (f = fa[x]) != k; Rotate(x))
			if (fa[f] != k) Rotate(Get(x) == Get(f) ? f : x);
		if (k == 0) rt = x;
	}
	void NewNode(int &x, int v, int f) {
		fa[x = ++tol] = f;
		val[x] = sum[x] = lmax[x] = rmax[x] = ans[x] = v;
		PushUp(x);
	}
	int Find(int x) {
		for (int cur = rt; ;) {
			if (x <= sz[son[cur][0]]) cur = son[cur][0];
			else {
				x -= sz[son[cur][0]] + 1;
				if (x == 0) return cur;
				cur = son[cur][1];
			}
		}
	}
	void Insert(int x, int w) {
		Splay(Find(x), 0);
		Splay(Find(x + 1), rt);
		NewNode(son[son[rt][1]][0], w, son[rt][1]);
		PushUp(son[rt][1]);
		PushUp(rt);
	}
	void Delete(int x) {
		Splay(Find(x), 0); 
		Splay(Find(x + 2), rt);
		son[son[rt][1]][0] = 0;
		PushUp(son[rt][1]);
		PushUp(rt);
	}
	void Replace(int x, int w) {
		Splay(Find(x + 1), 0);
		val[rt] = w;
		PushUp(rt);
	}
	int Query(int l, int r) {
		Splay(Find(l), 0);
		Splay(Find(r + 2), rt);
		return ans[son[son[rt][1]][0]];
	}
} tree;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n;
	std::vector<int> a(n);
	for (auto &c : a) std::cin >> c;
	tree.Init();
	for (int i = 1; i <= n; ++i) tree.Insert(i, a[i - 1]);
	std::cin >> m;
	for (int x, w; m--;) {
		char op;
		std::cin >> op >> x;
		if (op == 'D') {
			tree.Delete(x);
			continue;
		}
		std::cin >> w;
		if (op == 'I') tree.Insert(x, w);
		else if (op == 'R') tree.Replace(x, w);
		else if (op == 'Q') std::cout << tree.Query(x, w) << '\n';
	}
	return 0;
}