#include <bits/stdc++.h>
template <typename T> T inverse(T a, T m) {
	T u = 0, v = 1;
	while (a != 0) {
		T t = m / a;
		m -= t * a, std::swap(a, m);
		u -= t * v, std::swap(u, v);
	}
	assert(m == 1);
	return u;
}
template <typename T> class Modular {
public:
	using Type = typename std::decay<decltype(T::value)>::type;
	constexpr Modular() : value() {}
	template <typename U> Modular(const U& x) {value = normalize(x);}
	template <typename U> static Type normalize(const U& x) {
		Type v;
		if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
		else v = static_cast<Type>(x % mod());
		if (v < 0) v += mod();
		return v;
	}
	const Type& operator()() const { return value; }
	template <typename U> explicit operator U() const { return static_cast<U>(value); }
	constexpr static Type mod() { return T::value; }
	Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
	Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
	template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
	template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
	Modular operator-() const { return Modular(-value); }
	template <typename U = T> typename std::enable_if<std::is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
		value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
		return *this;
	}
	template <typename U = T> typename std::enable_if<std::is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
		long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
		value = normalize(value * rhs.value - q * mod());
		return *this;
	}
	template <typename U = T> typename std::enable_if<!std::is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
		value = normalize(value * rhs.value);
		return *this;
	}
	Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
	template <typename U> friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
	template <typename V, typename U> friend V& operator>>(V& stream, Modular<U>& number);
private:
	Type value;
};
template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> power(Modular<T> a, U b) {
	assert(b >= 0);
	for (Modular<T> res = 1; ; a *= a) {
		if (b & 1) res *= a;
		if ((b >>= 1) == 0) return res;
	}
}
template <typename U, typename T> U& operator<<(U& stream, const Modular<T>& number) { return stream << number(); }
template <typename U, typename T> U& operator>>(U& stream, Modular<T>& number) {
	typename std::common_type<typename Modular<T>::Type, long long>::type x;
	stream >> x;
	number.value = Modular<T>::normalize(x);
	return stream;
}
// using ModType = int;
// struct VarMod { static ModType value; };
// ModType VarMod::value;
// ModType& md = VarMod::value;
// using Mint = Modular<VarMod>;
constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<std::decay<decltype(md)>::type, md>>;
std::vector<Mint> fact{1}, inv_fact{1};
Mint C(int n, int k) {
	if (k < 0 || k > n) return 0;
	while ((int) fact.size() < n + 1) {
		fact.push_back(fact.back() * (int) fact.size());
		inv_fact.push_back(1 / fact.back());
	}
	return fact[n] * inv_fact[k] * inv_fact[n - k];
}
using Info = std::vector<Mint>;
using Matrix = std::vector<Info>;
Info operator * (const Info &lsh, const Matrix &rsh) {
	int n = lsh.size();
	Info ret(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) ret[j] += lsh[i] * rsh[i][j];
	return ret;
}
Matrix operator * (const Matrix &lsh, const Matrix &rsh) {
	int n = lsh.size();
	Matrix ret(n, Info(n));
	for (int i = 0; i < n; ++i)
		for (int k = 0; k < n; ++k)
			for (int j = 0; j < n; ++j)
				ret[i][j] += lsh[i][k] * rsh[k][j];
	return ret;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T, M, K, n = 0;
	std::cin >> T >> M >> K;
	std::map<std::vector<int>, int> f;
	for (int A = 0; A <= K; ++A)
		for (int B = 0; A + B <= K; ++B)
			for (int C = 0; A + B + C <= K; ++C) {
				if (M == 1 && (B > 0 || C > 0)) continue;
				if (M == 2 && C > 0) continue;
				f[{A, B, C}] = n++;
			}
	Matrix a(n + 1, Info(n + 1));
	for (int A = 0; A <= K; ++A)
		for (int B = 0; A + B <= K; ++B)
			for (int C = 0; A + B + C <= K; ++C) {
				if (M == 1 && (B > 0 || C > 0)) continue;
				if (M == 2 && C > 0) continue;
				int Add2 = (M == 2 && A + B < K), Add3 = (M == 3 && A + B + C < K);
				Mint V = 1 / Mint(A + B + C + 1);
				if (A > 0) a[f[{A, B, C}]][f[{A - 1, B, C}]] += A * V;
				if (B > 0) a[f[{A, B, C}]][f[{A + 1, B - 1 + Add2, C + Add3}]] += B * V;
				if (C > 0) a[f[{A, B, C}]][f[{A, B + 1, C - 1 + Add3}]] += C * V;
				a[f[{A, B, C}]][f[{A, B, C}]] += V;
				a[f[{A, B, C}]][n] += V;
			}
	a[n][n] = 1;
	std::vector<Matrix> F(60);
	F[0] = a;
	for (int i = 1; i < 60; ++i) F[i] = F[i - 1] * F[i - 1];
	for (long long N; T--;) {
		std::cin >> N;
		Info ans(n + 1);
		ans[f[{M == 1, M == 2, M == 3}]] = 1;
		for (int i = 0; i < 60; ++i)
			if (N >> i & 1) ans = ans * F[i];
		std::cout << ans[n] << '\n';
	}
	return 0;
}