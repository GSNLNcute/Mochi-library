// Source : https://oj.vnoi.info/problem/votree
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
vi g[N];

int h[N];
pii rmq[2 * N][LG + 1];
int mi[N][LG + 1], ma[N][LG + 1];
int lg[2 * N];

int timedfs = 0;
void dfs(int u, int par){
	mi[u][0] = ma[u][0] = ++timedfs;
	rmq[timedfs][0] = make_pair(h[u], u);
	for(const int& v : g[u]) if (v != par){
		h[v] = h[u] + 1; dfs(v, u);
	} 
	if (par != 0) rmq[++timedfs][0] = make_pair(h[par], par);
}
void build(){
	FOR(j, 1, LG) FOR(i, 1, n - MASK(j) + 1){
		ma[i][j] = max(ma[i][j - 1], ma[i + MASK(j - 1)][j - 1]);
		mi[i][j] = min(mi[i][j - 1], mi[i + MASK(j - 1)][j - 1]);
	}
	FOR(j, 1, LG) FOR(i, 1, timedfs - MASK(j) + 1)
		rmq[i][j] = min(rmq[i][j - 1], rmq[i + MASK(j - 1)][j - 1]);
	FOR(i, 2, timedfs) lg[i] = lg[i / 2] + 1; 
}
int lca(int l, int r){
	if (l > r) swap(l, r);
	int k = lg[r - l + 1];
	int L = min(mi[l][k], mi[r - MASK(k) + 1][k]);
	int R = max(ma[l][k], ma[r - MASK(k) + 1][k]);

	int K = lg[R - L + 1];
	return min(rmq[L][K], rmq[R - MASK(K) + 1][K]).second;
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
		cin >> n >> q;
		FOR(i, 1, n - 1){
			int u, v; cin >> u >> v;
			g[u].pb(v); g[v].pb(u);
		}

		dfs(1, 0); build();
		while(q--){
			int l, r; cin >> l >> r;
			cout << lca(l, r) << '\n';
		}
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}