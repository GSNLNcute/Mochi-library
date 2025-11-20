// Source : https://cses.fi/problemset/task/1705
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
const int LG = 18;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, m, q;
vi g[N];

int num[N], low[N];
bool cutpoint[N];
stack <int> st;
int timeDfs = 0;
ve <vi> comps;

int id[N];
vi G[2 * N];
int h[2 * N], up[2 * N][LG + 1];

void DFS_tarjan(int u, int par){
	num[u] = low[u] = ++timeDfs;
	st.push(u);

	for(const int& v : g[u]) if (v != par){
		if (num[v]) minimize(low[u], num[v]);
		else{
			DFS_tarjan(v, u);
			minimize(low[u], low[v]);

			if (low[v] >= num[u]){
				cutpoint[u] = (num[u] > 1 || num[v] > 2);

				comps.pb({u});
				while(comps.back().back() != v){
					comps.back().pb(st.top());
					st.pop();
				} 
			}
		}
	}
}
void build_BCC(){
	int node = 0;
	FOR(u, 1, n) if (cutpoint[u]) id[u] = ++node;

	for(const vi& comp : comps){
		int block = ++node;
		for(const int& u : comp){
			if (!cutpoint[u]) id[u] = block;
			else{
				G[block].pb(id[u]);
				G[id[u]].pb(block);
			}
		}
	} 
}
void dfs(int u){
	for(const int& v : G[u]) if (v != up[u][0]){
		h[v] = h[u] + 1; up[v][0] = u;
		FOR(j, 1, LG) up[v][j] = up[up[v][j - 1]][j - 1];
		dfs(v);
	}
}
int lca(int u, int v){
	if (h[u] < h[v]) swap(u,v);
	
	FORD(j, LG, 0) if (h[u] - MASK(j) >= h[v]) u = up[u][j];

	if (u != v){
		FORD(j, LG, 0) if (up[u][j] != up[v][j]){
			u = up[u][j]; v = up[v][j];
		}
		u = up[u][0];
	} 

	return u;
}
bool on_path(int a, int b, int c){
	int ab = lca(a, b), ac = lca(a, c), bc = lca(b, c);
	return (ab == c || (ab == ac && bc == c) || (ac == c && bc == ab));
}
void solve(){
	DFS_tarjan(1, 0);
	build_BCC();

	dfs(1);

	while(q--){
		int a, b, c; cin >> a >> b >> c;
		if (a == c || b == c) cout << "NO";
		else cout << (cutpoint[c] && on_path(id[a], id[b], id[c]) ? "NO" : "YES");
		cout << el;
	}
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
		cin >> n >> m >> q;
		FOR(i, 1, m){
			int u, v; cin >> u >> v;
			g[u].pb(v); g[v].pb(u);
		}

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}