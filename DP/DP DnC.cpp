// Source : https://oj.vnoi.info/problem/nkleaves
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

const int N = 1e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, k, w[N];

ll sum1[N], sum2[N];

ll dp[15][N];

inline ll cost(const ll& l, const ll& r){
	return (sum2[r] - sum2[l]) - 1ll * l * (sum1[r] - sum1[l]);
}
void compute(int t, int l, int r, int optL, int optR){
	if (l > r) return;

	int mid = (l + r) >> 1, best = -1;
	FOR(i, optL, min(mid, optR))
		if (minimize(dp[t][mid], dp[t - 1][i - 1] + cost(i, mid)))
			best = i;

	compute(t, l, mid - 1, optL, best);
	compute(t, mid + 1, r, best, optR);
}
void solve(){
	FOR(i, 1, n){
		sum1[i] = sum1[i - 1] + w[i];
		sum2[i] = sum2[i - 1] + 1ll * i * w[i];
	}

	memset(dp, 0x3f, sizeof(dp)); dp[0][0] = 0;
	// FOR(t, 1, k) FOR(i, 1, n){
	// 	FOR(j, 1, i) minimize(dp[i][t], dp[j - 1][t - 1] + cost(j, i));
	// }

	FOR(i, 1, n) dp[1][i] = cost(1, i);
	FOR(t, 2, k) compute(t, 1, n, 1, n);

	cout << dp[k][n];
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
		FOR(i, 1, n) cin >> w[i];
		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}