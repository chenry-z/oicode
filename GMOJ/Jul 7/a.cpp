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
		_putchar('\n');
		return *this;
} } io;
const int maxN = 2E5;
struct sgt {
	int val[maxN << 5], ls[maxN << 5], rs[maxN << 5], tol;
	void Insert(int &x, int l, int r, int p, int pre) {
		x = ++tol;
		val[x] = val[pre] + 1;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (p <= mid) rs[x] = rs[pre], Insert(ls[x], l, mid, p, ls[pre]);
		else ls[x] = ls[pre], Insert(rs[x], mid + 1, r, p, rs[pre]);
	}

	int Query(std::vector<std::pair<int, int>> &a, int l, int r, int p) {
		if (l == r) return l;
		int rk = 0;
		for (auto item : a) {
			int L = item.first, R = item.second;
			rk += val[ls[R]] - val[ls[L]];
		}
		int mid = (l + r) >> 1;
		if (rk >= p) {
			for (auto &item : a) {
				item.first = ls[item.first];
				item.second = ls[item.second];
			}
			return Query(a, l, mid, p);
		} else {
			for (auto &item : a) {
				item.first = rs[item.first];
				item.second = rs[item.second];
			}
			return Query(a, mid + 1, r, p - rk);

		}
	}
} st;
int main() {
	int n, m;
	io >> n >> m;
	std::vector<int> a(n);
	for (auto &c : a) io >> c;
	auto b = a;
	std::sort(b.begin(), b.end());
	b.erase(std::unique(b.begin(), b.end()), b.end());
	std::vector<int> rt(n + 1);
	for (int i = 0; i < n; ++i) {
		st.Insert(rt[i + 1], 0, b.size(), std::lower_bound(b.begin(), b.end(), a[i]) - b.begin(), rt[i]);
	}
	for (int k, p; m--;) {
		io >> k >> p;
		std::vector<std::pair<int, int>> a(k);
		for (auto &c : a) {
			io >> c.first >> c.second;
			c.first = rt[c.first - 1], c.second = rt[c.second];
		}
		io << b[st.Query(a, 0, b.size(), p)];
	}
}