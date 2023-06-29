#include <bits/stdc++.h>
template<typename T>
struct Vec {
    T x, y;
    Vec(T x = 0, T y = 0) : x(x), y(y) {}
    Vec operator+(const Vec &b) const {
        return Vec(x + b.x, y + b.y);
    }
    Vec operator-(const Vec &b) const {
        return Vec(x - b.x, y - b.y);
    }
    Vec operator*(const T &b) const {
        return Vec(x * b, y * b);
    }
    T operator*(const Vec &b) const {
        return x * b.y - y * b.x;
    }
    T operator^(const Vec &b) const {
        return x * b.x + y * b.y;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using i64 = long long;
    i64 X, T;
    int N, M, W;
    std::cin >> X >> N >> M >> W >> T;
    std::vector<std::pair<i64, i64>> S(N + 1);
    for (int i = 1; i <= N; ++i) {
        i64 x;
        std::cin >> x;
        S[i] = {x % T, x};
    }
    S.emplace_back(X % T, X);
    std::vector<std::tuple<i64, int, i64>> E(M + 1);
    for (int i = 1; i <= M; ++i) {
        i64 D, C;
        std::cin >> D >> C;
        E[i] = {D, C, INT64_MAX};
    }
    E.emplace_back(T, 0, 0);
    std::sort(std::next(S.begin()), S.end());
    std::sort(std::next(E.begin()), E.end());
    std::vector<i64> sum(M + 1);
    for (int i = 1, p = 1; i <= M; ++i) {
        auto &[D, C, F] = E[i];
        sum[i] = sum[i - 1] + C;
        i64 D_ = std::get<0>(E[i + 1]);
        while (p <= N + 1 && S[p].first < D)
            ++p;
        while (p <= N + 1 && S[p].first < D_)
            F = std::min(F, S[p++].second / T);
    }
    using P = Vec<__int128>;
    std::vector<P> q(1);
    std::vector<i64> f(M + 1);
    for (int i = 1; i <= M; ++i) {
        auto [D, C, F] = E[i];
        f[i] = f[i - 1] + (X / T + (X % T >= D)) * W;
        if (F != INT64_MAX) {
            auto j = [&](__int128 k) {
                int l = 0, r = q.size();
                while (r - l > 1) {
                    int m = (l + r) >> 1;
                    if (q[m].y - k * q[m].x < q[m - 1].y - k * q[m - 1].x)
                        l = m;
                    else
                        r = m;
                }
                return q[l];
            }
            ((__int128)W * F);
            f[i] = std::min(f[i], i64(j.y - W * F * j.x + W * F * i + sum[i]));
        }
        P I = P(i, f[i] - sum[i]);
        while (q.size() > 1 && (q[q.size() - 1] - q[q.size() - 2]) * (I - q[q.size() - 1]) <= 0)
            q.pop_back();
        q.emplace_back(I);
    }
    std::cout << f[M] + (X / T + 1) * W << '\n';
    return 0;
}