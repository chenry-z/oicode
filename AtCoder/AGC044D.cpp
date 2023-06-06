#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::vector<std::string> s;
	constexpr int L = 128;
	auto Ask = [&](std::string s) {
		std::cout << "? " << s << std::endl;
		int x;
		return std::cin >> x, x;
	};
	int S = 0;
	for (char i = 'A'; i <= 'Z'; ++i) s.emplace_back(L - Ask(std::string(L, i)), i), S += s.back().size();
	for (char i = 'a'; i <= 'z'; ++i) s.emplace_back(L - Ask(std::string(L, i)), i), S += s.back().size();
	for (char i = '0'; i <= '9'; ++i) s.emplace_back(L - Ask(std::string(L, i)), i), S += s.back().size();
	auto Merge = [&](std::string L, std::string R) {
		if (L.empty() || R.empty()) return L + R;
		std::string res;
		for (int i = 0, j = 0, n = L.size(), m = R.size(); i < n || j < m;) {
			if (i == n) res += R[j++];
			else if (j == m) res += L[i++];
			else {
				if (Ask(res + L[i] + R.substr(j)) == S - (i + m + 1)) res += L[i++];
				else res += R[j++];
			}
		}
		return res;
	};
	std::function<std::string(std::vector<std::string>)> Build = [&](std::vector<std::string> cur) -> std::string {
		if (cur.size() == 1ull) return cur[0];
		int n = cur.size();
		decltype(cur) L, R;
		for (int i = 0; i < n / 2; ++i) L.emplace_back(cur[i]);
		for (int i = n / 2; i < n; ++i) R.emplace_back(cur[i]);
		return Merge(Build(L), Build(R));
	};
	std::cout << "! " + Build(s) << std::endl;
	return 0;
}