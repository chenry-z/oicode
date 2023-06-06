#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
const double PI = acos(-1);
int main() {
	ios::sync_with_stdio(false);
	int a, b, d;
	cin >> a >> b >> d;
	double dd = d * PI / 180;
	printf("%.8lf %.8lf", a * cos(dd) - b * sin(dd), a * sin(dd) + b * cos(dd));
	return 0;
}