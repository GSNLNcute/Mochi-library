// Source : https://oj.vnoi.info/problem/lqdrace
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

const int N = 2e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, k;
ve <pii> g[N];

int sz[N], big[N];
int h[N];
ll f[N];

unordered_map <ll, int> near;
int ans = inf;

void predfs(int u, int par){
	sz[u] = 1; big[u] = 0;
	for(const pii& child : g[u]){
		int v = child.fi, w = child.se;
		if (v == par) continue;

		f[v] = f[u] + w; h[v] = h[u] + 1;
		predfs(v, u); sz[u] += sz[v];

		if (sz[big[u]] < sz[v]) big[u] = v;
	}
}
void add(int u, int par){
	if (!near[f[u]]) near[f[u]] = inf; minimize(near[f[u]], h[u]);
	for(const pii& child : g[u]) if (child.fi != par) add(child.fi, u);
}
void del(int u, int par){
	near[f[u]] = inf;
	for(const pii& child : g[u]) if (child.fi != par) del(child.fi, u);
}
void update(int u, int par, int root){
	ll val = k - (f[u] - f[root]) + f[root];
	if (val >= 0){
		if (!near[val]) near[val] = inf;
		minimize(ans, near[val] + h[u] - 2 * h[root]);
	} 

	for(const pii& child : g[u]) if (child.fi != par) update(child.fi, u, root);
}
void dfs(int u, int par){
	for(const pii& child : g[u]){
		int v = child.fi;
		if (v == par || v == big[u]) continue;
		dfs(v, u); del(v, u);
	}

	if (big[u]) dfs(big[u], u);
	if (!near[f[u] + k]) near[f[u] + k] = inf;
    ans = min(ans, near[f[u] + k] - h[u]);

    if (!near[f[u]]) near[f[u]] = inf; 
    minimize(near[f[u]], h[u]); 

	for(const pii& child : g[u]){
		int v = child.fi;
		if (v == par || v == big[u]) continue;
		update(v, u, u);
		add(v, u);
	}
}
void solve(){
	predfs(1, 0);
	dfs(1, 0);
	cout << (ans >= n ? -1 : ans);
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
		FOR(i, 1, n - 1){
			int u, v, w; cin >> u >> v >> w;
			u++; v++;
			g[u].pb(mp(v, w));
			g[v].pb(mp(u, w));
		}

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}