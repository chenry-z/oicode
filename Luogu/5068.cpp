#include <bits/stdc++.h>

class SparseTable {
  using T = int;
  using VT = std::vector<T>;
  using VVT = std::vector<VT>;
  using func_type = std::function<T(const T &, const T &)>;

  VVT ST;

  static T default_func(const T &t1, const T &t2) { return std::min(t1, t2); }

  func_type op;

 public:
  SparseTable(const std::vector<T> &v, func_type _func = default_func) {
    op = _func;
    int len = v.size(), l1 = ceil(log2(len)) + 1;
    ST.assign(len, VT(l1, 0));
    for (int i = 0; i < len; ++i) {
      ST[i][0] = v[i];
    }
    for (int j = 1; j < l1; ++j) {
      int pj = (1 << (j - 1));
      for (int i = 0; i + pj < len; ++i) {
        ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  T query(int l, int r) {
    int lt = r - l + 1;
    int q = std::__lg(lt);
    return op(ST[l][q], ST[r - (1 << q) + 1][q]);
  }
};
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
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> time(n + 1, m);
	std::vector<std::pair<int, int>> Q(m, {-1, -1});
	std::vector<std::vector<bool>> tag(n + 1);
	for (int i = 0, op, x, y; i < m; ++i) {
		std::cin >> op >> x;
		if (op == 1) time[x] == m ? time[x] = i : time[x];
		else {
			std::cin >> y;
			Q[i] = {x, y};
		}
	}
	SparseTable ST(time);
	std::vector<std::vector<std::pair<int, int>>> M(m);
	for (int d = 1; d <= n; ++d) {
		tag[d].resize(n / d + 2);
		for (int L = 1, R; L <= n; L = R + 1) {
			R = std::min(n, L + d - 1);
			int min_time = ST.query(L, R);
			if (min_time < m) M[min_time].emplace_back(d, (L - 1) / d);
		}
	}
	Fenwick<long long> bit(n);
	std::vector<int> ans(n + 1, -1);
	for (int i = 0; i < m; ++i) {
		auto [L, R] = Q[i];
		if (L != -1) std::cout << bit.Sum(L, R) + R - L + 1 << '\n';
		for (auto [d, p] : M[i]) {
			tag[d][p] = true;
			for (; tag[d][ans[d] + 1]; ++ans[d]) bit.Add(d, 1);
		}
	}
	return 0;
}