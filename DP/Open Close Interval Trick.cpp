// Source : https://codeforces.com/contest/626/problem/F
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

const int N = 200 + 5;
const int K = 1000 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, k, a[N];

int dp[N][N][K];
// Xét tới người i, đang mở j đoạn, tổng giá trị là p

void add(int& cur, const int& val){
	cur += val; if (cur >= MOD) cur -= MOD;
}
void solve(){
	sort(a + 1, a + n + 1);
	// vì không cần chọn đoạn liên tiếp, không mất tính tổng quát, ta sort lại hết

	memset(dp, 0, sizeof(dp)); dp[0][0][0] = 1;
	REP(i, n) FOR(j, 0, n) FOR(t, 0, k) if (dp[i][j][t] > 0){
		int val = t + (a[i + 1] - a[i]) * j; // mỗi đoạn đang mở được cộng thêm lượng (a[i + 1] - a[i])
		if (val > k) continue;

		add(dp[i + 1][j][val], dp[i][j][t]);                                      // a[i + 1] tách nhóm riêng
		add(dp[i + 1][j][val], 1ll * j * dp[i][j][t] % MOD);                    // a[i + 1] vào một đoạn đang mở bất kì
		if (j < n) add(dp[i + 1][j + 1][val], dp[i][j][t]);                       // a[i + 1] mở một đoạn
		if (j > 0) add(dp[i + 1][j - 1][val], 1ll * j * dp[i][j][t] % MOD);     // a[i + 1] đóng một đoạn bất kì
	}

	int ans = 0;
	FOR(t, 0, k) add(ans, dp[n][0][t]);
	cout << ans;
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
		cin >> n >> k;
		FOR(i, 1, n) cin >> a[i];
		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}