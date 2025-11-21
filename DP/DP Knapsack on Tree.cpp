// Source : https://oj.vnoi.info/problem/PTREE
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
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, p, c[N];
vi g[N];

int sz[N], par[N];
int dp[N][N]; // Answer in subtree of u, choose u
int trace[N][N];
vi ans;

void dfs(int u){
	dp[u][1] = c[u]; sz[u] = 1;
	for(const int& v : g[u]) if (v != par[u]){
		par[v] = u; dfs(v);

		vi tmp(min(p, sz[u] + sz[v]) + 1, -inf);
		FOR(i, 1, min(p, sz[u])) tmp[i] = dp[u][i];

		FOR(i, 1, min(p, sz[u])) FOR(j, 1, min(p - i, sz[v])){
			if (maximize(tmp[i + j], dp[u][i] + dp[v][j]))
				trace[v][i + j] = j;
		}
		
		FOR(i, 1, min(p, sz[u] + sz[v])) dp[u][i] = tmp[i];
		sz[u] += sz[v];
	}
}
void go(int u, int j){
	cout << u << " ";
	FORD(i, g[u].size() - 1, 0){
		int v = g[u][i]; if (v == par[u]) continue;
		if (trace[v][j] != -1){
			go(v, trace[v][j]);
			j -= trace[v][j];
		}
	}
}
void solve(){
	memset(dp, -0x3f, sizeof(dp));
	memset(trace, -1, sizeof(trace));

	dfs(1);

	int res = -inf, pos = -1;
	FOR(i, 1, n) if (maximize(res, dp[i][p])) pos = i;
	go(pos, p);	
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
		cin >> n >> p;
		FOR(i, 1, n) cin >> c[i];
		FOR(i, 1, n - 1){
			int u, v; cin >> u >> v;
			g[u].pb(v); g[v].pb(u);
		}

		solve();		
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}