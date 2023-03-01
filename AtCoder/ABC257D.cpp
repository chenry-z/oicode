#include "bits/stdc++.h"
using namespace std;
#define int long long
signed main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<tuple<int, int, int>> a(n + 1);
	for (auto &[x, y, p] : a)
		cin >> x >> y >> p;
	int l = 0, r = 10000000000;
	auto Check = [&](int xx)
	{
		for (int i = 0; i < n; ++i)
		{
			std::vector<bool> vis(n);
			vis[i] = true;
			queue<int> q;
			q.push(i);
			while (q.size())
			{
				auto &[x, y, p] = a[q.front()];
				q.pop();
				for (int j = 0; j < n; ++j)
				{
					if (vis[j])
						continue;
					auto &[nx, ny, pp] = a[j];
					if (p * xx < abs(x - nx) + abs(y - ny))
						continue;
					vis[j] = true;
					q.push(j);
				}
			}
			bool flag = true;
			for (int j = 0; j < n; ++j)
				flag &= vis[j];
			if (flag)
				return true;
		}
		return false;
	};
	while (l < r)
	{
		int mid = (l + r) >> 1ll;
		if (Check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	cout << l;
	return 0;
}