// Source : https://oj.vnoi.info/problem/atcoder_dp_v
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

int n, MOD;
vi g[N], child[N];

int dpin[N], dpout[N];
// Answer in and out of subtree of u when u is black

vi pre[N], suf[N];

void dfsin(int u, int par){
	dpin[u] = 1;
	for(const int& v : g[u]) if (v != par){
		dfsin(v, u);
		dpin[u] = 1ll * dpin[u] * (dpin[v] + 1) % MOD;
		// Either connect u with v when v is black, or all subtree v is white
		child[u].pb(v);
	}

	int sz = (int) child[u].size();
	pre[u].assign(sz + 2, 0); suf[u].assign(sz + 2, 0);
	pre[u][0] = suf[u][sz + 1] = 1;
	FOR(i, 1, sz) pre[u][i] = 1ll * pre[u][i - 1] * (dpin[child[u][i - 1]] + 1) % MOD;
	FORD(i, sz, 1) suf[u][i] = 1ll * suf[u][i + 1] * (dpin[child[u][i - 1]] + 1) % MOD;
} 
void dfsout(int u, int par){
	REP(i, child[u].size()){
		int v = child[u][i];
		dpout[v] = (1ll * pre[u][i] * suf[u][i + 2] % MOD * dpout[u] % MOD + 1) % MOD;
		dfsout(v, u);
	}
}
void solve(){
	dfsin(1, 0);
	dpout[1] = 1; dfsout(1, 0);

	FOR(i, 1, n) cout << 1ll * dpin[i] * dpout[i] % MOD << el;		
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
		cin >> n >> MOD;
		FOR(i, 1, n - 1){
			int u, v; cin >> u >> v;
			g[u].pb(v); g[v].pb(u);
		} 

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}