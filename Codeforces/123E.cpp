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
int main() {
	int n;
	io >> n;
	using f64 = long double;
	std::vector<int> _x(n), _y(n), sz(n, 1);
	std::vector<f64> x(n), y(n);
	std::vector<std::vector<int>> e(n);
	for (int i = 1, u, v; i < n; ++i) {
		io >> u >> v;
		--u, --v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for (int i = 0; i < n; ++i) io >> _x[i] >> _y[i];
	int _sx = std::accumulate(_x.begin(), _x.end(), 0);
	int _sy = std::accumulate(_y.begin(), _y.end(), 0);
	for (int i = 0; i < n; ++i) x[i] = 1. * _x[i] / _sx, y[i] = 1. * _y[i] / _sy;
	f64 sx = std::accumulate(x.begin(), x.end(), (f64)0.0);
	f64 ans = 0;
	std::function<void(int, int)> DFS = [&](int u, int fa) {
		for (auto v : e[u]) {
			if (v == fa) continue;
			DFS(v, u);
			sz[u] += sz[v];
			x[u] += x[v];
			ans += x[v] * sz[v] * y[u];
		}
		ans += (sx - x[u]) * (n - sz[u]) * y[u];
	};
	DFS(0, -1);
	std::cout << std::fixed << std::setprecision(15) << ans << '\n';
	return 0;
}