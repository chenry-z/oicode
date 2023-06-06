#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int a, b;
	std::cin >> a >> b;
	std::cout << char('A' + (b + a - 1) / a - 1);
	return 0;
}