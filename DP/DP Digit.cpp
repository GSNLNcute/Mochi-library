// Source : https://oj.vnoi.info/problem/atcoder_dp_s
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

const int N = 1e4 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

string s;
int d;

int a[N + 3];
int dp[N + 3][102][2];
// Số lượng số mà i chữ số đầu tiên tạo ra một số có số dư cho d là s, số này đã bé hơn / bằng giới hạn ban đầu 

inline void add(int& cur, const int& val){
	cur += val; if (cur >= MOD) cur -= MOD;
}
int calc(int i, int s, bool tight){
	if (i > N) return s == 0;
	if (dp[i][s][tight] != -1) return dp[i][s][tight];

	int &ans = dp[i][s][tight]; ans = 0;
	int lim = tight ? 9 : a[i];
	FOR(c, 0, lim) add(ans, calc(i + 1, (s + c) % d, tight | (c < lim)));
	return ans;
}
void solve(){
	for(int i = (int) s.size() - 1, j = N; i >= 0; i--, j--)
		a[j] = s[i] - '0';

	memset(dp, -1, sizeof(dp)); 
	cout << (calc(1, 0, 0) - 1 + MOD) % MOD;
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
		cin >> s >> d;
		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}