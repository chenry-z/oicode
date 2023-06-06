#include <bits/stdc++.h>
using namespace std;
char ch1[200005], ch2[200005];
signed main()
{
	cin >> ch1 + 1;
	cin >> ch2 + 1;
	int n = strlen(ch2 + 1);
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (ch1[i - cnt] != ch2[i])
		{
			if (ch1[i - cnt - 1] == ch2[i] && i > cnt + 2)
			{
				if (ch1[i - cnt - 1] == ch1[i - cnt - 2])
				{
					cnt++;
					continue;
				}
			}
			else
			{
				if (ch1[i - cnt + 1 == ch2[i]] && i - cnt + 2 <= n)
				{
					if (ch1[i - cnt + 1] == ch1[i - cnt + 2])
					{
						cnt++;
						continue;
					}
				}
			}
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}