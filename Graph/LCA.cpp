// Source : https://oj.vnoi.info/problem/lubenica
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

int n, q;
ve <pii> g[N];

int h[N], up[N][LG + 1];
int min_W[N][LG + 1], max_W[N][LG + 1]; 

void dfs(int u){
	for(const pii& child : g[u]){
		int v = child.fi, w = child.se;
		if (v == up[u][0]) continue;

		h[v] = h[u] + 1; up[v][0] = u;
		min_W[v][0] = max_W[v][0] = w;
		FOR(j, 1, LG){
			up[v][j] = up[up[v][j - 1]][j - 1];
			min_W[v][j] = min(min_W[v][j - 1], min_W[up[v][j - 1]][j - 1]);
			max_W[v][j] = max(max_W[v][j - 1], max_W[up[v][j - 1]][j - 1]);
		} 

		dfs(v);
	}
}
pii lca(int u, int v){
	if (h[u] < h[v]) swap(u,v);

	int ansmin = inf, ansmax = 0;
	
	FORD(j, LG, 0) if (h[u] - MASK(j) >= h[v]){
		minimize(ansmin, min_W[u][j]);
		maximize(ansmax, max_W[u][j]);
		u = up[u][j];
	}

	if (u != v){
		FORD(j, LG, 0) if (up[u][j] != up[v][j]){
			minimize(ansmin, min_W[u][j]);
			minimize(ansmin, min_W[v][j]);
			maximize(ansmax, max_W[u][j]);
			maximize(ansmax, max_W[u][j]);
			u = up[u][j]; v = up[v][j];
		}
		minimize(ansmin, min_W[u][0]);
		minimize(ansmin, min_W[v][0]);
		maximize(ansmax, max_W[u][0]);
		maximize(ansmax, max_W[v][0]);
	} 

	return mp(ansmin, ansmax);
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
		FOR(i, 1, n - 1){
			int u, v, w; cin >> u >> v >> w;
			g[u].pb(mp(v, w)); g[v].pb(mp(u, w));
		}

		dfs(1);

		cin >> q;
		while(q--){
			int u, v; cin >> u >> v;
			pii ans = lca(u, v);
			cout << ans.fi << " " << ans.se << el;
		}
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}