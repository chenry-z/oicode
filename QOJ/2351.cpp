#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::string s;
	int T;
	std::cin >> s >> T;
	if (s == "transmit") {
		for (int n; T--;) {
			std::cin >> n;
			std::vector<int> a(n);
			for (auto &c : a) std::cin >> c;
			std::sort(a.begin(), a.end());
			std::shuffle(a.begin(), a.end(), std::mt19937(std::accumulate(a.begin(), a.end(), 0, std::bit_xor<int>())));
			for (int i = 0; i < n; ++i) std::cout << a[i] << " \n"[i == n - 1];
		}
	} else {
		for (int n; T--;) {
			std::cin >> n;
			std::vector<int> a(n);
			for (auto &c : a) std::cin >> c;
			int x = std::accumulate(a.begin(), a.end(), 0, std::bit_xor<int>());
			auto b = a;
			std::sort(b.begin(), b.end());
			std::shuffle(b.begin(), b.end(), std::mt19937(x));
			if (a == b) {
				for (int i = 0; i < n; ++i) std::cout << a[i] << " \n"[i == n - 1];
				continue;
			}
			for (int i = 0; i < n; ++i) std::cout << a[i] << ' ';
			std::sort(b.begin(), b.end());
			for (int p = 0; p < 512; ++p) {
				auto c = b;
				c.insert(std::lower_bound(c.begin(), c.end(), p ^ x), p ^ x);
				std::shuffle(c.begin(), c.end(), std::mt19937(p));
				for (auto it = c.begin(); it != c.end(); ++it) {
					if (*it == (p ^ x)) {
						c.erase(it);
						break;
					}
				}
				if (a == c) {
					std::cout << (p ^ x) << '\n';
					break;
				}
			}
		}
	}
	return 0;
}