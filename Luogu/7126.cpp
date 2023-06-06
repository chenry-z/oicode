#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
struct Node {
	Node *ch[2];
	int val, id, mn;
	unsigned sz;
	Node(int val = 0, int id = -1) : val(val), id(id), mn(val), sz(rng()) {
		ch[0] = ch[1] = nullptr;
	}
	void upd() {
		// sz = (ch[0] == nullptr ? 0 : ch[0] -> sz) + (ch[1] == nullptr ? 0 : ch[1] -> sz) + 1;
		mn = val;
		if (ch[0] != nullptr) mn = std::min(mn, ch[0] -> mn);
		if (ch[1] != nullptr) mn = std::min(mn, ch[1] -> mn);
	}
};
struct BST {
	Node *root;
	std::array<Node *, 2> Split(Node *cur, int key) {
		if (cur == nullptr)
			return {nullptr, nullptr};
		if (cur -> id <= key) {
			auto [l, r] = Split(cur -> ch[1], key);
			cur -> ch[1] = l;
			cur -> upd();
			return {cur, r};
		}
		auto [l, r] = Split(cur -> ch[0], key);
		cur -> ch[0] = r;
		cur -> upd();
		return {l, cur};
	}
	Node *Merge(Node *u, Node *v) {
		if (u == nullptr)
			return v;
		if (v == nullptr)
			return u;
		if (u -> sz < v -> sz) {
		// if (int(rng() % (u -> sz + v -> sz)) < u -> sz) {
			u -> ch[1] = Merge(u -> ch[1], v);
			u -> upd();
			return u;
		}
		v -> ch[0] = Merge(u, v -> ch[0]);
		v -> upd();
		return v;
	}
} tr;
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
class FastIostream {
	const int maxBF = 1 << 20;
	char *inbuf, *inst, *ined, *oubuf, *oust, *oued;
	void _flush() { fwrite(oubuf, 1, oued - oust, stdout); }
	char _getchar() {
		if (inst == ined) inst = inbuf, ined = inbuf + fread(inbuf, 1, maxBF, stdin);
		return inst == ined ? EOF : *inst++;
	} void _putchar(const char &c) {
		if (oued == oust + maxBF) _flush(), oued = oubuf;
		*oued++ = c;
	}
public:
	FastIostream() {
		inst = ined = inbuf = new char[maxBF];
		oust = oued = oubuf = new char[maxBF];
	} ~FastIostream() {_flush();}
	template <typename Int> FastIostream &operator>>(Int &n) {
		static char c;
		bool flag = false;
		while ((c = _getchar()) < '0' || c > '9') if (c == '-') flag = true;
		for (n = c - '0'; (c = _getchar()) >= '0' && c <= '9'; n = n * 10 + (c - 48));
		if (flag) n = ~n + 1;
		return *this;
	} template <typename Int> FastIostream &operator<<(Int n) {
		if (n < 0) _putchar('-'), n = ~n + 1;
		static char S[40];
		int t = 0;
		do {S[t++] = '0' + n % 10, n /= 10;} while (n);
		for (int i = 0; i < t; ++i) _putchar(S[t - i - 1]);
		return *this;
	} FastIostream &operator<<(const char *s) {
		for (int i = 0; s[i]; ++i) _putchar(s[i]);
		return *this;
	}
} io;
int main() {
	// std::ios::sync_with_stdio(false);
	// std::cin.tie(nullptr);
	int n, m, C, root = -1;
	io >> n >> m >> C;
	std::vector<std::vector<int>> e(n);
	for (int i = 1, x; i < n; ++i) {
		io >> x;
		--x;
		e[x].emplace_back(i);
		e[i].emplace_back(x);
	}
	std::vector<int> sz(n), dep(n), rnk(n), suf(n, n), pre(n, -1);
	std::vector<bool> vis(n);
	std::queue<int> q;
	q.emplace(0);
	for (dep[0] = 1; q.size(); ) {
		int u = q.front(); q.pop();
		static int dfx = 0;
		rnk[u] = dfx++;
		for (auto v : e[u])
			if (dep[v] == 0) dep[v] = dep[u] + 1, q.emplace(v);
	}
	std::function<void(int, int, int)> DFS_root = [&](int u, int fa, int tot) {
		int mx = tot - sz[u];
		for (auto v : e[u])
			if (v != fa && !vis[v]) {
				DFS_root(v, u, tot);
				if (root != -1) return;
				mx = std::max(mx, sz[v]);
			}
		if (mx <= (tot + 1) / 2) root = u;
	};
	std::vector<int> a;
	std::function<void(int, int)> DFS = [&](int u, int fa) {
		a.emplace_back(u);
		sz[u] = 1;
		for (auto v : e[u])
			if (v != fa && !vis[v]) dep[v] = dep[u] + 1, DFS(v, u), sz[u] += sz[v];
	};
	std::function<void(int)> Solve = [&](int rt) {
		a.clear(), vis[rt] = true, dep[rt] = 0, DFS(rt, -1);
		if (sz[rt] == 1) return;
		std::sort(a.begin(), a.end(), [&](const int &x, const int &y) {
			return rnk[x] < rnk[y];
		});
		std::stack<Node*> newed;
		for (auto u : a) {
			auto [L, R] = tr.Split(tr.root, u);
			auto _new = new Node(dep[u], u);
			newed.emplace(_new);
			int res = -1;
			for (auto cur = L; cur != nullptr && cur -> mn + dep[u] <= C; )
				if (cur -> ch[1] != nullptr && cur -> ch[1] -> mn + dep[u] <= C) cur = cur -> ch[1];
				else if (cur -> val + dep[u] <= C) {
					res = cur -> id;
					break;
				} else cur = cur -> ch[0];
			pre[u] = std::max(pre[u], res);
			res = n;
			for (auto cur = R; cur != nullptr && cur -> mn + dep[u] <= C; )
				if (cur -> ch[0] != nullptr && cur -> ch[0] -> mn + dep[u] <= C) cur = cur -> ch[0];
				else if (cur -> val + dep[u] <= C) {
					res = cur -> id;
					break;
				} else cur = cur -> ch[1];
			suf[u] = std::min(suf[u], res);
			tr.root = tr.Merge(L, tr.Merge(_new, R));
		}
		for (; newed.size(); newed.pop()) delete newed.top();
		tr.root = nullptr;
		for (auto v : e[rt])
			if (!vis[v]) root = -1, DFS_root(v, rt, sz[v]), Solve(root);
	};
	DFS(0, -1), DFS_root(0, -1, n), Solve(root);
	std::vector<std::vector<std::pair<int, int>>> T(n + 2), Q(n + 1);
	for (int i = 0; i < n; ++i) {
		T[pre[i] + 2].emplace_back(i + 1, 1);
		T[pre[i] + 2].emplace_back(suf[i] + 1, -1);
		T[i + 2].emplace_back(i + 1, -1);
		T[i + 2].emplace_back(suf[i] + 1, 1);
	}
	std::vector<int> ans(m);
	for (int i = 0, l, r; i < m; ++i) {
		io >> l >> r;
		Q[l].emplace_back(r, i);
	}
	Fenwick<int> bit(n);
	for (int i = 1; i <= n; ++i) {
		for (auto [p, w] : T[i]) bit.Add(p, w);
		for (auto [r, id] : Q[i]) ans[id] = bit.Sum(1, r);
	}
	for (auto c : ans) io << c << "\n";
	return 0;
}
// 84 pts