#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		auto Add = [&](int x) {
			std::cout << "+ " << x << std::endl;
			int c;
			std::cin >> c;
			return c;
		};
		auto Query = [&](int x, int y) {
			++x, ++y;
			std::cout << "? " << x << ' ' << y << std::endl;
			int c;
			std::cin >> c;
			return c;
		};
		auto Answer = [&](std::vector<int> p1, std::vector<int> p2) {
			std::cout << '!';
			for (auto c : p1) std::cout << ' ' << c + 1;
			for (auto c : p2) std::cout << ' ' << c + 1;
			std::cout << std::endl;
			int c;
			std::cin >> c;
			return c;
		};
		std::vector<int> P(n);
		for (int i = 0, l = 0, r = n - 1; i < n; ++i) {
			if (i & 1) P[i] = r--;
			else P[i] = l++;
		}
		int root = -1;
		assert(Add(n + 1) == 1);
		assert(Add(n + 2) == 1);
		for (int i = 1, mx = 0; i < n; ++i) {
			int cur = Query(0, i);
			if (cur > mx) {
				mx = cur;
				root = i;
			}
		}
		std::vector<int> q(n), p1(n), p2(n);
		q[0] = root;
		for (int i = 0; i < n; ++i) {
			if (i != root) q[Query(root, i)] = i;
		}
		for (int i = 0; i < n; ++i) {
			p1[q[i]] = P[i];
			p2[q[i]] = P[n - 1 - i];
		}
		assert(Answer(p1, p2) == 1);
	}
	return 0;
}