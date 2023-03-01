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
	}
} io;
int main() {
	int n, m;
	io >> n >> m;
	int B = 120, Bs = (n - 1) / B + 1;
	using i64 = long long;
	i64 a[n + 1], sum[Bs];
	for (int i = 1; i <= n; ++i) io >> a[i];
	int L[Bs], R[Bs], bel[n + 1];
	for (int i = 0, j = 1, k = 1; j <= n; ++i, ++j) {
		L[i] = j;
		for (k = j; k <= std::min(j + B - 1, n); ++k)
			bel[k] = i, sum[i] += a[k];
		R[i] = j = k - 1;
	}
	i64 pre[B][B], suf[B][B];
	for (int op, x, y, z; m--;) {
		io >> op >> x >> y;
		if (op == 1) {
			io >> z;
			if (x >= B)
				for (int i = y; i <= n; i += x)
					a[i] += z, sum[bel[i]] += z;
			else {
				for (int i = 1; i <= y; ++i) suf[x][i] += z;
				for (int i = y; i <= x; ++i) pre[x][i] += z;
			}
		} else {
			i64 ans = 0;
			if (bel[x] == bel[y])
				for (int i = x; i <= y; ++i) ans += a[i];
			else {
				for (int i = x; i <= R[bel[x]]; ++i) ans += a[i];
				for (int i = bel[x] + 1; i < bel[y]; ++i) ans += sum[i];
				for (int i = L[bel[y]]; i <= y; ++i) ans += a[i];
			}
			for (int i = 1; i < B; ++i) {
				int bL = (x - 1) / i + 1, bR = (y - 1) / i + 1;
				int L = (x - 1) % i + 1, R = (y - 1) % i + 1;
				if (bL == bR) ans += pre[i][R] - pre[i][L - 1];
				else ans += pre[i][i] * (bR - bL - 1) + suf[i][L] + pre[i][R];
			}
			io << ans % 1000000007;
		}
	}
	return 0;
}