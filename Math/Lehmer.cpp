#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define ll   long long
#define pb   push_back
#define mp   make_pair
#define pii  pair<int,int>
#define fi   first
#define se   second
#define ve   vector
#define vi   ve<int>
#define vll  ve<ll>
#define el   '\n'
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define __builtin_popcount __builtin_popcountll
template<class T> bool minimize(T &a, T b){ return (a > (b) ? a = (b), 1 : 0); }
template<class T> bool maximize(T &a, T b){ return (a < (b) ? a = (b), 1 : 0); }
template<class T> T Abs(const T &x) { return (x<0?-x:x);}

const int N = 1e6 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;


// Đặt S(v, p): số các số trên sàng eratosthenes sau khi đã áp dụng sàng với các số nguyên tố nhỏ hơn hoặc bằng p
// Vậy S(v, p): số các số hoặc là số nguyên tố hoặc là hợp số nhưng các ước của nó lớn hơn p
//
// Phân tích:
// + Nếu p là hợp số hoặc v < p*p: không cần xóa thêm số nào ~~> S(v, p) = S(v, p-1)
// + Nếu p là số nguyên tố và v >= p*p:
//   - Cần xóa các bội số của p dạng p*r, trong đó r là tích của các số nguyên tố từ p trở lên
//   - Lý do là nếu r là bội của một số nguyên tố nhỏ hơn p thì p*r đã được xóa trong lần sàng trước đó
//   - Số các r = S(v/p, p-1) - S(p-1, p-1)
//   - Giải thích:
//     + S(p-1, p-1) ~ Số các số nguyên tố từ 1 đến p-1
//     + S(v/p, p-1) ~ Số các số nguyên tố từ 1 đến v/p hoặc số là tích các số nguyên tố từ p trở lên
//     + S(v/p, p-1) - S(p-1, p-1) ~ Số các số nguyên tố từ p đến v/p hoặc tích của chúng
//   - Vậy ta có công thức: S(v, p) = S(v, p-1) - (S(v/p, p-1) - S(p-1, p-1))
// + Tuy dùng quy hoạch động, không nhất thiết phải duy trì toàn bộ các giá trị S(v, p) trong quá trình tính toán
// + Quá trình tính toán sẽ tăng dần theo p, ta sẽ dựa trên các S(v, p-1) để tính các S(v, p)
// + Để tính giá trị S(v, p), ta chỉ cần một số các giá trị trước đó của S(x, p) chứ không cần tất cả mọi giá trị trước đó
// + Cụ thể:
//   - Các S(1, p), S(2, p),..., S(p, p) <~~ được lưu trong mảng A
//   - Các S(v/1, p), S(v/2, p),..., S(v/p, p) <~~ được lưu trong mảng B

ll a[N + 5], b[N + 5];

ll Lehmer(ll n){
    ll r = (ll) sqrt(n);
    for (ll i = 1; i <= r; i++) {
        a[i] = i - 1;
        b[i] = n / i - 1;
    }
    for (ll p = 2; p <= r; p++)
        if (a[p] > a[p - 1]) {
            ll sp = a[p - 1];
            ll p2 = p * p;
            ll to = min(r, n / p2);
            for (ll i = 1; i <= to; i++) {
                ll vp = i * p;
                if (vp <= r) vp = b[vp];
                else vp = a[n / vp];
                b[i] -= (vp - sp);
            }
            for (ll v = r; v >= p2; v--)
                a[v] -= (a[v / p] - sp);
        }
    return b[1];
}

signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	#define NAME "TASK"
	if (fopen(NAME".inp", "r")){
		freopen(NAME".inp", "r", stdin);
   		freopen(NAME".out", "w", stdout);
	}

	bool multiTest = 0;
	int numTest = 1;

	if (multiTest) cin >> numTest;
	while(numTest--){
		
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}