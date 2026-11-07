const int MOD = 998244353;
NTT<MOD, 1 << 21> ntt;          // maxf >= 2 * N (xem lưu ý bên dưới)

int N;
vector<int> f, g, acc;           // acc[i] = tổng đóng góp tích lũy vào f[i]

void solve(int l, int r) {       // xử lý nửa khoảng [l, r)
    if (r - l == 1) {
        // acc[l] đã đủ mọi đóng góp từ j < l -> chốt giá trị f[l]
        if (l == 0) f[0] = 1;                 // giá trị khởi tạo
        else        f[l] = acc[l];            // hoặc biến đổi tùy bài
        return;
    }
    int mid = (l + r) / 2;
    solve(l, mid);

    // đóng góp f[l..mid) sang [mid, r)
    vector<int> A(f.begin() + l, f.begin() + mid);
    vector<int> B(g.begin(), g.begin() + (r - l));
    auto C = ntt.multiply(A, B);                // C[k] ứng với chỉ số l + k
    for (int i = mid; i < r; i++)
        acc[i] = (acc[i] + C[i - l]) % MOD;

    solve(mid, r);
}