// Source : 
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

const int N = 1e3 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

// Ban đầu có n nhóm, nhóm i có trọng số a[i]. 
// Mỗi lần được chọn hai nhóm liền kề để gộp thành một nhóm, chi phí bằng tổng trọng số của hai nhóm đó.
// Lặp lại đến khi còn một nhóm.

int n, a[N];

ll pre[N];
ll dp[N][N];
int opt[N][N];

inline ll cost(const int& i, const int& j){
	return pre[j] - pre[i - 1];
	// Hàm cost phải thỏa cả bất tứ giác và tính đơn điệu
	// a <= b <= c <= d
	// cost(b, c) <= cost(a, d)
	// cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c)
}
void solve(){
    FOR(i, 1, n) pre[i] = pre[i - 1] + a[i];

    // FOR(len, 2, n) FOR(i, 1, n - len + 1){
    //     int j = i + len - 1;
    //     FOR(k, i, j - 1) minimize(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, j));
    // }

    FORD(i, n, 1){
        dp[i][i] = 0; opt[i][i] = i;
        FOR(j, i + 1, n){
            dp[i][j] = INF;
            FOR(k, opt[i][j - 1], min(j - 1, opt[i + 1][j]))
                if(minimize(dp[i][j], dp[i][k] + dp[k + 1][j] + cost(i, j)))
                    opt[i][j] = k;
        }
    }

    cout << dp[1][n] << el;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "Knuth Optimization"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){
        cin >> n;
        FOR(i, 1, n) cin >> a[i];
        solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
