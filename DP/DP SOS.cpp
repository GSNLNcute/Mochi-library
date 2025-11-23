// Source : https://oj.vnoi.info/problem/voi21_or
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
const int LG = 20;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, k, L, R, a[N];

int fac[N], rev[N], gt[N];

int cnt[N], f[N];

inline int pw(int u, int v){
	int ans = 1;
	while(v > 0){
		if (v & 1) ans = 1ll * ans * u % MOD;
		u = 1ll * u * u % MOD; v >>= 1;
	}
	return ans;
}
void add(int& cur, const int& val){
	cur += val; if (cur >= MOD) cur -= MOD;
}
void sub(int& cur, const int& val){
	cur -= val; if (cur < 0) cur += MOD;
}
void build(){
	fac[0] = 1;
	FOR(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % MOD;

	rev[n] = pw(fac[n], MOD - 2);
	FORD(i, n, 1) rev[i - 1] = 1ll * rev[i] * i % MOD;

	FOR(i, k, n) gt[i] = 1ll * fac[i] * rev[k] % MOD * rev[i - k] % MOD;
}
void solve(){
	build();

	FOR(i, 1, n) cnt[a[i]]++;
	FOR(i, 0, LG) FOR(mask, 0, R) if (BIT(mask, i))
		cnt[mask] += cnt[mask ^ MASK(i)];

	FOR(mask, 0, R){
		f[mask] = gt[cnt[mask]]; 
		if (__builtin_popcount(mask) & 1) f[mask] = MOD - f[mask];
	}
	FOR(i, 0, LG) FOR(mask, 0, R) if (BIT(mask, i))
		add(f[mask], f[mask ^ MASK(i)]);

	int res = 0;
	FOR(mask, L, R) if(mask % 3 == 0){
		if (__builtin_popcount(mask) & 1) sub(res, f[mask]);
		else add(res, f[mask]);
	}

	cout << res;
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
		cin >> n >> k >> L >> R;
		FOR(i, 1, n) cin >> a[i];
		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}