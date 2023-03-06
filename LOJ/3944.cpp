#include <bits/stdc++.h>
struct seg {
	const int n, mod;
	struct node {
		int l, r, delta;
		node(int l = 0, int r = 0, int delta = 0) : l(l), r(r), delta(delta) {}
	};
	static bool cmpL(const node& lsh, const node &rsh) { return lsh.l < rsh.l; }
	static bool cmpR(const node& lsh, const node &rsh) { return lsh.r < rsh.r; }
	std::vector<std::vector<node>> val;
	seg(std::vector<int> A, int M) : n(A.size() - 1), mod(M + 1), val(4 << std::__lg(n)) {
		auto Build = [&](auto &&Build, int x, int l, int r) -> void {
			if (l == r) {
				val[x].emplace_back(0, A[l] - 1, A[l] + 1);
				val[x].emplace_back(A[l], M, A[l]);
				return;
			}
			int m = (l + r) >> 1;
			Build(Build, x << 1, l, m), Build(Build, x << 1 | 1, m + 1, r);
			for (auto [l_, r_, delta] : val[x << 1]) {
				int l__ = (l_ + delta) % mod, r__ = (r_ + delta) % mod, sz = val[x << 1 | 1].size();
				auto pos1 = std::lower_bound(val[x << 1 | 1].begin(), val[x << 1 | 1].end(), node(0, l__, 0), cmpR) - val[x << 1 | 1].begin();
				auto pos2 = std::upper_bound(val[x << 1 | 1].begin(), val[x << 1 | 1].end(), node(r__, 0, 0), cmpL) - val[x << 1 | 1].begin();
				if (l__ > r__) pos2 += sz;
				for (int i = pos1; i < pos2; ++i) {
					auto [L, R, d_] = val[x << 1 | 1][i % sz];
					int L_ = l__, R_ = r__;
					if (l__ > r__) i >= sz ? L_ = 0 : R_ = M;
					L_ = std::max(L_, L), R_ = std::min(R_, R);
					int L__ = (L_ - delta + mod) % mod, R__ = (R_ - delta + mod) % mod;
					val[x].emplace_back(L__, R__, (d_ + delta) % mod);
				}
			}
		};
		Build(Build, 1, 1, n);
	}
	int Query(int x, int l, int r, int L, int R, int v) {
		if (L > R || L > r || l > R) return v;
		if (L <= l && r <= R)
			return (v + std::prev(std::upper_bound(val[x].begin(), val[x].end(), node(v, 0, 0), cmpL)) -> delta) % mod;
		int m = (l + r) >> 1;
		return Query(x << 1 | 1, m + 1, r, L, R, Query(x << 1, l, m, L, R, v));
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int N, M, Q, T = 0;
	std::string S;
	std::cin >> N >> M >> S;
	while ((1 << T) < N / 2) ++T;
	S = " " + S;
	std::vector<int> A(M + 1), bit(T + 1), posL(1), posR(1), sumRed(N + 1), lg(N + 2);
	for (int i = 1; i <= N + 1; ++i) lg[i] = lg[i >> 1] + 1;
	for (int i = 1; i <= T; ++i) bit[i] = 1 << (i - 1);
	for (int i = 1; i <= N; ++i)
		if (S[i] == 'B') posL.emplace_back(i), sumRed[i] = sumRed[i - 1];
		else posR.emplace_back(i), sumRed[i] = sumRed[i - 1] + 1;
	posL.emplace_back(N + 1), posR.emplace_back(N + 1);
	std::reverse(posR.begin(), posR.end());
	for (int i = 1; i <= M; ++i) std::cin >> A[i];
	seg st(A, N);
	std::vector nxt(T + 1, std::vector(T + 1, std::vector(M + 2, 0)));
	std::vector sumL(T + 1, std::vector(M + 1, 0ll)),  sumR(T + 1, std::vector(M + 1, 0ll));
	for (int i = 0; i <= T; ++i)
		for (int j = 0; j <= T; ++j) {
			nxt[i][j][M + 1] = M + 1;
			for (int k = M; k >= 0; --k) {
				nxt[i][j][k] = nxt[i][j][k + 1];
				if (bit[i] < A[k] && A[k] <= N - bit[j] && (A[k] != N || S[N] == 'R')) nxt[i][j][k] = k;
			}
		}
	for (int i = 0; i <= T; ++i)
		for (int j = 1; j <= M; ++j) {
			sumL[i][j] = sumL[i][j - 1], sumR[i][j] = sumR[i][j - 1];
			if (bit[i] >= A[j]) sumL[i][j] += A[j];
			if (A[j] > N - bit[i]) sumR[i][j] += N - A[j];
		}
	std::cin >> Q;
	for (int bl, br; Q--;) {
		std::cin >> bl >> br;
		std::cout << [&]() {
			auto GetR = [&](int L, int R, int pos) {
				int val = posL[L] + sumRed[posR[R] - 1] - sumRed[posL[L]];
				if (pos != -1) {
					if (posR[R] <= pos || (posL[L] < pos && S[pos] == 'B')) ++val;
					val = (val + pos) % (N + 1);
				}
				return val;
			};
			for (int L = 0, R = 0, bitL = 0, bitR = 0, p = bl; ;) {
				int to = std::min(br + 1, nxt[bitL][bitR][p]);
				if (p < to) {
					int cl = p, cr = to, mx = p - 1;
					for (int i = 0; i < 22; ++i) {
						int cm = (cl + cr) >> 1;
						int curL = std::min((long long)posL.size() - 1, L + sumL[bitL][cm] - sumL[bitL][p - 1]);
						int curR = std::min((long long)posR.size() - 1, R + sumR[bitR][cm] - sumR[bitR][p - 1]);
						if (posL[curL] + 1 >= posR[curR]) cr = cm;
						else cl = cm, mx = cm;
					}
					L = std::min((long long)posL.size() - 1, L + sumL[bitL][mx] - sumL[bitL][p - 1]);
					R = std::min((long long)posR.size() - 1, R + sumR[bitR][mx] - sumR[bitR][p - 1]);
					if (mx != to - 1) return st.Query(1, 1, M, mx + 2, br, GetR(L, R, A[mx + 1]));
					p = to;
				}
				int curR = GetR(L, R, -1), isit = 0;
				if (p == br + 1) return curR;
				if (posR[R] <= A[p] || (posL[L] < A[p] && S[A[p]] == 'B')) isit = 1;
				if (N - curR >= A[p]) L += A[p] + isit;
				else R += N + 1 - A[p] - isit;
				if (posL[std::min((int)posL.size() - 1, L)] + 1 >= posR[std::min((int)posR.size() - 1, R)])
					return st.Query(1, 1, M, p + 1, br, (curR + A[p] + isit) % (N + 1));
				p += 1, bitL = std::min(T, lg[posL[L]]), bitR = std::min(T, lg[N + 1 - posR[R]]);
			}
		}() << '\n';
	}
	return 0;
}