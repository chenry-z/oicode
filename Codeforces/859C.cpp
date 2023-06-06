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
	template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
	constexpr Z(Int v)
		: v_(reduce(static_cast<unsigned long long>(v % static_cast<int>(Mod) + static_cast<int>(Mod)) * r2)) {}
	static constexpr unsigned mod() { return Mod; }
	constexpr unsigned val() const { return norm(reduce(v_)); }
	template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
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
using Int = Z<1000000007>;
struct LinearBase {
	std::vector<int> v;
	LinearBase(int n) : v(n) {}
	void Insert(int x) {
		for (int i = (int)v.size(); i >= 0; --i)
			if (x >> i & 1) {
				if (v[i] != 0) x ^= v[i];
				else return v[i] = x, void();
			}
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector pri{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
	LinearBase f(20);
	for (int i = 0, c; i < n; ++i) {
		std::cin >> c;
		int t = c, ret = 0;
		for (int j = 0; j < (int)pri.size(); ++j)
			if (t % pri[j] == 0) {
				int cnt = 0;
				for (; t % pri[j] == 0; t /= pri[j]) ++cnt;
				ret |= ((cnt & 1) << j);
			}
		f.Insert(ret);
	}
	for (int i = 19; i >= 0; --i)
		if (f.v[i] != 0) --n;
	std::cout << Int(2).pow(n) - 1 << std::endl;
	return 0;
}