// Source : https://oj.vnoi.info/problem/atcoder_dp_u
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

const int N = 16;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, a[N + 5][N + 5];
ll val[MASK(N) + 5];
ll dp[MASK(N) + 5];

void calc(const int& mask){
	int tmp = mask;
	vi idx;
	while(tmp > 0){
		int j = __builtin_ctz(tmp) + 1; tmp -= MASK(j - 1);
		for(const int& p : idx) val[mask] += a[j][p];
		idx.pb(j);
	}
}
void solve(){
	int total = MASK(n) - 1;
	FOR(mask, 0, total) calc(mask);

	memset(dp, -0x3f, sizeof(dp)); dp[0] = 0;

	FOR(mask, 0, total){
		int phanbu = total ^ mask;
		for(int submask = phanbu; submask > 0; submask = (submask - 1) & phanbu)
			maximize(dp[mask | submask], dp[mask] + val[submask]);
	}

	cout << dp[total];
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
		cin >> n;
		FOR(i, 1, n) FOR(j, 1, n) cin >> a[i][j];
		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}