#include <bits/stdc++.h>
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
struct node {
	int ls, rs, cnt;
	long long sum;
	node(int ls = 0, int rs = 0, int cnt = 0, long long sum = 0)
	    : ls(ls), rs(rs), cnt(cnt), sum(sum) {};
};
std::vector<long long> val;
struct Seg {
	node tr[30000000];
	int tol = 0;
	int Insert(int pre, int l, int r, int L, int R, const int &lim) {
		int rt = pre;
		tr[rt = ++tol] = tr[pre];
		if (L <= l && r <= R) {
			++tr[rt].cnt;
			tr[rt].sum += val[r] - val[l - 1];
			return rt;
		}
		int mid = (l + r) >> 1;
		if (L <= mid) tr[rt].ls = Insert(tr[rt].ls, l, mid, L, R, lim);
		if (R > mid) tr[rt].rs = Insert(tr[rt].rs, mid + 1, r, L, R, lim);
		tr[rt].sum = tr[tr[rt].ls].sum + tr[tr[rt].rs].sum + (val[r] - val[l - 1]) * tr[rt].cnt;
		return rt;
	}
	long long Query(int x, int l, int r, int L, int R, long long w) {
		if (L > r || R < l) return 0;
		if (x == 0) return (val[std::min(R, r)] - val[std::max(L, l) - 1]) * w;
		if (L <= l && r <= R) return tr[x].sum + (val[r] - val[l - 1]) * w;
		int mid = (l + r) >> 1;
		return Query(tr[x].ls, l, mid, L, R, w + tr[x].cnt) + Query(tr[x].rs, mid + 1, r, L, R, w + tr[x].cnt);
	}
	void Clear() {tol = 0;}
	int Size() {return tol;}
} st;
int main() {
	int n, q;
	io >> n >> q;
	std::vector<int> a(n + 1), top(n), dfn(n), rnk(n + 1), sz(n, 1), son(n, -1), fa(n, -2);
	val.resize(n);
	std::vector<long long> ss(n + 1), dep(n), sum(n + 1);
	for (int i = 1; i <= n; ++i) io >> a[i], --a[i];
	std::vector<std::vector<std::pair<int, int>>> e(n);
	for (int i = 1, u, v, w; i < n; ++i) {
		io >> u >> v >> w;
		--u, --v;
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
	}
	auto DFS = [&](auto self, int u) -> void {
		for (auto &[v, w] : e[u]) {
			if (fa[v] != -2) continue;
			fa[v] = u;
			dep[v] = dep[u] + w;
			val[v] = w;
			self(self, v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
		}
	};
	auto HLD = [&](auto self, int u, int t) -> void {
		top[u] = t;
		static int _ = 0;
		rnk[dfn[u] = ++_] = u;
		if (son[u] == -1) return;
		self(self, son[u], t);
		for (auto &[v, w] : e[u])
			if (v != fa[u] && v != son[u]) self(self, v, v);
	};
	fa[0] = -1; DFS(DFS, 0); HLD(HLD, 0, 0);
	for (int i = 1; i <= n; ++i) ss[i] = ss[i - 1] + val[rnk[i]];
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + dep[a[i]];
	val = ss;
	std::vector<int> rt(n + 1);
	auto Modify = [&](int x, int u) {
		int lim = st.Size();
		for (; u != -1; u = fa[top[u]])
			rt[x] = st.Insert(rt[x], 1, n, dfn[top[u]], dfn[u], lim);
	};
	auto Query = [&](int x, int u) {
		long long ans = x * dep[u] + sum[x];
		for (; u != -1; u = fa[top[u]])
			ans -= 2ll * st.Query(rt[x], 1, n, dfn[top[u]], dfn[u], 0);
		return ans;
	};
	for (int i = 1; i <= n; ++i) rt[i] = rt[i - 1], Modify(i, a[i]);
	long long ans = 0;
	for (int op, x, v, l, r; q--;) {
		io >> op;
		if (op == 1) {
			io >> l >> r >> v;
			l ^= ans, r ^= ans, v ^= ans;
			--v;
			io << (ans = Query(r, v) - Query(l - 1, v)) << "\n";
			ans %= (1 << 30);
		} else {
			io >> x;
			x ^= ans;
			std::swap(a[x], a[x + 1]);
			sum[x] = sum[x - 1] + dep[a[x]];
			if (st.Size() > 2.999E7) {
				st.Clear();
				for (int i = 1; i <= n; ++i) rt[i] = rt[i - 1], Modify(i, a[i]);
			} else {
				rt[x] = rt[x - 1];
				Modify(x, a[x]);
			}
		}
	}
	return 0;
}