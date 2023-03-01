#include <bits/stdc++.h>
template <unsigned Mod>
class Z {
	unsigned v_;
	static constexpr unsigned getR() {
		unsigned iv = Mod * (2 - Mod * Mod);
		iv *= 2 - Mod * iv;
		iv *= 2 - Mod * iv;
		return iv * (Mod * iv - 2);
	}
	static constexpr unsigned reduce(unsigned long long x)
		{return (x + static_cast<unsigned long long>(static_cast<unsigned>(x) * r) * Mod) >> 32;}
	static constexpr unsigned norm(unsigned x) { return x - (Mod & -((Mod - 1 - x) >> 31)); }
	static constexpr unsigned r    = getR();
	static constexpr unsigned r2   = -static_cast<unsigned long long>(Mod) % Mod;
	static constexpr unsigned mod2 = Mod << 1;
public:
	constexpr Z() : v_() {}
	template <typename Int>
	constexpr Z(Int v)
		: v_(reduce(static_cast<unsigned long long>(v % static_cast<int>(Mod) + static_cast<int>(Mod)) * r2)) {}
	static constexpr unsigned mod() { return Mod; }
	constexpr unsigned val() const { return norm(reduce(v_)); }
	template <typename Int>
	explicit constexpr operator Int() const { return static_cast<Int>(val()); }
	constexpr Z operator-() const {
		Z res;
		res.v_ = (mod2 & -(v_ != 0)) - v_;
		return res;
	}
	constexpr Z inv() const {
		int x1 = 1, x3 = 0, a = val(), b = mod();
		while (b != 0) {
		  int q = a / b, x1_old = x1, a_old = a;
		  x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
		}
		return Z(x1);
	}
	constexpr Z &operator+=(const Z &rhs) {
		v_ += rhs.v_ - mod2;
		v_ += mod2 & -(v_ >> 31);
		return *this;
	}
	constexpr Z &operator-=(const Z &rhs) {
		v_ -= rhs.v_;
		v_ += mod2 & -(v_ >> 31);
		return *this;
	}
	constexpr Z &operator*=(const Z &rhs) { return v_ = reduce(static_cast<unsigned long long>(v_) * rhs.v_), *this;}
	constexpr Z &operator/=(const Z &rhs) { return operator*=(rhs.inv()); }
	constexpr Z pow(unsigned long long e) const {
		for (Z res(1u), x(*this);; x *= x) {
		  if (e & 1) res *= x;
		  if ((e >>= 1) == 0) return res;
		}
	}
	friend constexpr Z operator+(const Z &lhs, const Z &rhs) { return Z(lhs) += rhs; }
	friend constexpr Z operator-(const Z &lhs, const Z &rhs) { return Z(lhs) -= rhs; }
	friend constexpr Z operator*(const Z &lhs, const Z &rhs) { return Z(lhs) *= rhs; }
	friend constexpr Z operator/(const Z &lhs, const Z &rhs) { return Z(lhs) /= rhs; }
	friend constexpr bool operator==(const Z &lhs, const Z &rhs) { return norm(lhs.v_) == norm(rhs.v_); }
	friend constexpr bool operator!=(const Z &lhs, const Z &rhs) { return norm(lhs.v_) != norm(rhs.v_); }
	friend std::istream &operator>>(std::istream &is, Z &rhs) {
		int x;
		is >> x;
		rhs = Z(x);
		return is;
	}
	friend std::ostream &operator<<(std::ostream &os, const Z &rhs) { return os << rhs.val(); }
};
using Int = Z<998244353>;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	std::vector<std::tuple<int, int, int>> a;
	std::vector aa(n, std::vector(m, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			std::cin >> aa[i][j];
			a.emplace_back(aa[i][j], i, j);
		}
	std::sort(a.begin(), a.end());
	{
		std::vector<std::tuple<int, int, int>> tmp;
		int r, c;
		std::cin >> r >> c;
		for (auto [x, i, j] : a)
			if (x < aa[r - 1][c - 1] || (i == r - 1 && j == c - 1))
				tmp.emplace_back(x, i, j);
		a = tmp;
	}
	n = a.size();
	std::vector<Int> sx(n), sx_2(n), sy(n), sy_2(n), sum(n), f(n);
	auto [w0, x0, y0] = a[0];
	sx[0] = x0, sy[0] = y0, sx_2[0] = x0 * x0, sy_2[0] = y0 * y0;
	for (int i = 1, j = -1; i < n; ++i) {
		auto [w, x, y] = a[i];
		if (w != std::get<0>(a[i - 1])) j = i - 1;
		if (j != -1) f[i] = Int(x) * x + Int(y) * y + Int(1) / (j + 1) * (sum[j] + sx_2[j] + sy_2[j] - Int(2) * (x * sx[j] + y * sy[j]));
		sum[i] = sum[i - 1] + f[i];
		sx[i] = sx[i - 1] + x;
		sy[i] = sy[i - 1] + y;
		sx_2[i] = sx_2[i - 1] + x * x;
		sy_2[i] = sy_2[i - 1] + y * y;
	}
	std::cout << f.back() << '\n';
	return 0;
}