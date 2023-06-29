#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::cout << ((n <= 4) ? "Bob" : "Alice") << '\n';
	}
	return 0;
}