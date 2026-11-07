// Source : https://oj.uz/problem/view/NOI19_feast
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

const int N = 3e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

#define pll pair<ll,ll>

int n, k, a[N];
pll dp[N][2];
// First store maximum value, second is minimum amount to achieve it

inline void calc(pll& cur, const pll& val){
	if (cur.fi < val.fi) cur = val;
	else if (cur.fi == val.fi) cur.se = min(cur.se, val.se);
}
pll process(const ll& pen){
	FOR(i, 0, n) dp[i][0] = dp[i][1] = mp(-INF, 0);
	dp[0][0] = mp(0, 0);

	FOR(i, 1, n){
		calc(dp[i][0], dp[i - 1][0]);
		calc(dp[i][0], dp[i - 1][1]);

		calc(dp[i][1], mp(dp[i - 1][0].fi + a[i] - pen, dp[i - 1][0].se + 1));
		calc(dp[i][1], mp(dp[i - 1][1].fi + a[i], dp[i - 1][1].se));
	}

	pll ans = dp[n][0]; calc(ans, dp[n][1]);
	return mp(ans.fi + ans.se * pen, ans.se);
}
void solve(){
	ll lo = 0, hi = INF, ans = 0;
	while(lo <= hi){
		ll mid = (lo + hi) >> 1;
		pll res = process(mid);
		if (res.se <= k) ans = res.fi, hi = mid - 1; // decrease pen so amount of segment go up
		else lo = mid + 1;
	}
	cout << ans;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "Alien Trick"
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
