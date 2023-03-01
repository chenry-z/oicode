#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
struct Node {
	Node *ch[2];
	int val, sz, tag[2], id, cnt;
	Node(int val = 0, int id = -1, int cnt = 0) : val(val), sz(1), id(id), cnt(cnt) {
		tag[0] = tag[1] = 0;
		ch[0] = ch[1] = nullptr;
	}
	void upd() {
		sz = (ch[0] == nullptr ? 0 : ch[0] -> sz) + (ch[1] == nullptr ? 0 : ch[1] -> sz) + 1;
	}
	void push() {
		if (tag[0]) {
			if (ch[0] != nullptr) ch[0] -> tag[0] += tag[0], ch[0] -> val -= tag[0];
			if (ch[1] != nullptr) ch[1] -> tag[0] += tag[0], ch[1] -> val -= tag[0];
			tag[0] = 0;
		}
		if (tag[1]) {
			if (ch[0] != nullptr) ch[0] -> tag[1] += tag[1], ch[0] -> cnt += tag[1];
			if (ch[1] != nullptr) ch[1] -> tag[1] += tag[1], ch[1] -> cnt += tag[1];
			tag[1] = 0;
		}
	}
};
struct BST {
	Node *root;
	std::array<Node*, 2> Split(Node *cur, int key) {
		if (cur == nullptr) return {nullptr, nullptr};
		cur -> push();
		if (cur -> val <= key) {
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
		u -> push(), v -> push();
		if (int(rng() % (u -> sz + v -> sz)) < u -> sz) {
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
	std::cin >> n;
	std::vector<std::pair<int, int>> a(n);
	for (auto &[c, q] : a) std::cin >> c >> q;
	std::sort(a.begin(), a.end(), [](auto x, auto y) {
		if (x.second == y.second) return x.first < y.first;
		return x.second > y.second;
	});
	std::cin >> m;
	std::vector<int> b(m), id(m), ans(m);
	std::iota(id.begin(), id.end(), 0);
	for (auto &c : b) std::cin >> c;
	std::sort(id.begin(), id.end(), [&](int x, int y) {
		return b[x] < b[y];
	});
	for (int i = 0; i < m; ++i) tr.root = tr.Merge(tr.root, new Node(b[id[i]], id[i]));
	for (auto [c, _] : a) {
		auto [l, r] = tr.Split(tr.root, c - 1);
		auto [l1, r1] = tr.Split(r, c * 2 - 1);
		if (r1 != nullptr) {
			r1 -> val -= c;
			r1 -> tag[0] += c;
			++r1 -> cnt;
			++r1 -> tag[1];
		}
		std::queue<Node*> q;
		q.emplace(l1);
		while (q.size()) {
			Node *u = q.front(); q.pop();
			if (u == nullptr) continue;
			u -> push();
			q.emplace(u -> ch[0]);
			q.emplace(u -> ch[1]);
			auto [L, R] = tr.Split(l, u -> val - c);
			l = tr.Merge(L, tr.Merge(new Node(u -> val - c, u -> id, u -> cnt + 1), R));
			delete u;
		}
		tr.root = tr.Merge(l, r1);
	}
	std::function<void(Node*)> DFS = [&](Node *u) {
		if (u == nullptr) return;
		u -> push();
		ans[u -> id] = u -> cnt;
		DFS(u -> ch[0]), DFS(u -> ch[1]);
	};
	DFS(tr.root);
	for (int i = 0; i < m; ++i) std::cout << ans[i] << " \n"[i == m - 1];
	return 0;
}