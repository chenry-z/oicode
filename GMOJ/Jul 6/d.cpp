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
	int n, m;
	io >> n;
	std::vector<int> a(n);
	for (auto &c : a) io >> c;
	std::vector<int> s(n + 1);
	io >> m;
	for (int r, aa, bb; m--;) {
		io >> r >> aa >> bb;
		for (int i = 1; i <= n; ++i) s[i] = s[i - 1] ^ a[i - 1];
		int ans = -1;
		for (int i = aa - 1; i <= bb - 1; ++i) {
			int cur = s[i] ^ s[r - 1];
			ans = std::max(ans, a[r - 1] - cur);
		}
		if (ans == 0) ans = -1;
		io << ans << "\n";
		if (ans != -1) a[r - 1] -= ans;
	}
	return 0;
}