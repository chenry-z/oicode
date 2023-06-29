#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::vector<int> a;
		bool flag = true;
		for (int i = 0, x; i < n; ++i) {
			std::cin >> x;
			if (a.empty()) {
				a.emplace_back(x);
				std::cout << 1;
			} else {
				if (flag && x >= a.back()) {
					a.emplace_back(x);
					std::cout << 1;
				} else if (flag) {
					if (x <= a.front()) {
						flag = false;
						std::cout << 1;
						a.emplace_back(x);
					} else std::cout << 0;
				} else {
					if (x <= a.front() && x >= a.back()) {
						std::cout << 1;
						a.emplace_back(x);
					} else std::cout << 0;
				}
			}
		}
		std::cout << '\n';
	}
	return 0;
}