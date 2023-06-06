#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
struct Node {
	int p;
	unsigned sum, tag, ssum, stag, val;
	Node *ch[2];
	Node(int p, unsigned sum, unsigned tag) : p(p), sum(sum), tag(tag), ssum(sum), stag(tag), val(rng()) {
		ch[0] = ch[1] = nullptr;
	}
	void upd() {
		ssum = (ch[0] == nullptr ? 0 : ch[0] -> ssum) + (ch[1] == nullptr ? 0 : ch[1] -> ssum) + sum;
		stag = (ch[0] == nullptr ? 0 : ch[0] -> stag) + (ch[1] == nullptr ? 0 : ch[1] -> stag) + tag;
	}
};
struct BST {
	Node *root;
	std::array<Node*, 2> Split(Node* cur, int key) {
		if (cur == nullptr) return {nullptr, nullptr};
		if (cur -> p <= key) {
			auto [l, r] = Split(cur -> ch[1], key);
			cur -> ch[1] = l;
			cur -> upd();
			return {cur, r};
		}
		auto [l, r] = Split(cur -> ch[0], key);
		cur -> ch[0] = r;
		cur -> upd();
		return {l, cur};
	}
	Node *Merge(Node *u, Node *v) {
		if (u == nullptr) return v;
		if (v == nullptr) return u;
		if (u -> val < v -> val) {
			u -> ch[1] = Merge(u -> ch[1], v);
			u -> upd();
			return u;
		}
		v -> ch[0] = Merge(u, v -> ch[0]);
		v -> upd();
		return v;
	}

	
} tr;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	unsigned x = 0;
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		unsigned p, q;
		std::cin >> p >> q;
		((p += x) %= (1 << m)) += 1, ((q += x) %= (1 << m)) += 1;
		if (p > q) std::swap(p, q);
		auto [L, R] = tr.Split(tr.root, q);
		x += (q - p + 1) * i;
		if (L != nullptr) x += L -> stag * (q + 1) - L -> ssum;
		auto [L1, R1] = tr.Split(L, p - 1);
		if (L1 != nullptr) x -= L1 -> stag * p - L1 -> ssum;
		auto _q = new Node(q + 1, -i * (q + 1), -i);
		auto _p = new Node(p, i * p, i);
		tr.root = tr.Merge(L1, tr.Merge(_p, tr.Merge(R1, tr.Merge(_q, R))));
	}
	std::cout << (x & ((1 << 30) - 1)) << '\n';
	return 0;
}