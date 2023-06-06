#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
using mint = atcoder::modint998244353;
int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> e(m);
	vector<mint> f(1 << n, 1);
	for (auto &[x, y] : e) cin >> x >> y, --x, --y;
	for (int s = 0; s < (1 << n); ++s) {
		vector<vector<mint>> a(n, vector<mint>(n));
		for (auto &[x, y] : e) {
			if ((s >> x & 1) && (s >> y & 1)) {
				a[x][x] += 1, a[y][y] += 1;
				a[x][y] -= 1, a[y][x] -= 1;
			}
		}
		for (int i = 1; i < n; ++i) {
			if (!(s >> i & 1)) continue;
			for (int j = i + 1; j < n; ++j) {
				if (!(s >> j & 1)) continue;
				if (a[i][i] == 0 && a[j][i] != 0) {
					f[s] = - f[s];
					swap(a[i], a[j]);
					break;
				}
				f[s] *= a[i][i];
				if (f[s] == 0) continue;
				mint tt = 1 / f[s];
				for (int j = i + 1; j < n; ++j) {
					mint tmp = a[j][i] * tt;
					for (int k = i; k < n; ++k)
						a[j][k] -= tmp * a[i][k];
				}
			}
		}
	}
	vector<vector<mint>> g(n, vector<mint>(1 << n));
	g[0][0] = 1;
	for (int i = 1; i < n; ++i) {
		for (int S = 0; S < (1 << n); ++S) {
			// if (i == __builtin_popcount(S)) g[i][S] = f[S];
			for (int T = (S - 1) & S; T > 0; T = (T - 1) & S) {
				int tt = __builtin_popcount(T);
				if (i - tt + 1 >= 0) g[i][S] += f[T] * g[i - tt + 1][S ^ T];
			}
			cerr << i << ' ' << S << ' ' << g[i][S].val() << endl;
		}
	}
	mint ret = 1;
	for (int i = 1; i < n; ++i) {
		ret *= 1;
		cout << (g[i][(1 << n) - 1] * ret / mint(m).pow(i)).val() << '\n';
	}
	return 0;
}