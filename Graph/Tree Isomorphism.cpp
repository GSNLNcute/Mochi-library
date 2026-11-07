// Source : https://cses.fi/problemset/task/1701/
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
const int MOD[2] = {1000000000 + 9, 1000000000 + 7};

int n;

int pw[2][N];

struct Tree{
	vi g[N];
	int centroid[2];
	int sz[N];
	int id[2][N];

	void reset(){
		FOR(i, 1, n) g[i].clear();
		centroid[0] = centroid[1] = -1;
	}

	void addCentroid(int u){
		REP(i, 2) if (centroid[i] == -1){
			centroid[i] = u; break;
		}
	}
	void dfs(int u, int par){
		sz[u] = 1;
		bool isCentroid = true;


		ve <pii> child[2];
		for(const int& v : g[u]) if (v != par){
			dfs(v, u); sz[u] += sz[v];
			if (sz[v] > n / 2) isCentroid = false;
			
			REP(j, 2) child[j].pb(mp(id[j][v], v));
		}

		REP(j, 2){
			sort(ALL(child[j]));

			id[j][u] = 1;
			for(const pii& cur : child[j])
				id[j][u] = (1ll * pw[j][sz[cur.se] + 1] * id[j][u] % MOD[j] + cur.fi) % MOD[j];
			id[j][u] = 1ll * id[j][u] * 2 % MOD[j];
			
		}

		if (n - sz[u] > n / 2) isCentroid = false;
		if (isCentroid) addCentroid(u);
	}
} T1, T2;

bool isIso(int root1, int root2){
	T1.dfs(root1, 0); T2.dfs(root2, 0);
	return T1.id[0][root1] == T2.id[0][root2] && T1.id[1][root1] == T2.id[1][root2];
}

void solve(){
	REP(j, 2){
		pw[j][0] = 1;
		FOR(i, 1, n) pw[j][i] = 2ll * pw[j][i - 1] % MOD[j];
	}

	T1.dfs(1, 0); T2.dfs(1, 0);

	bool hasAns = false;
	REP(i, 2) REP(j, 2) if (T1.centroid[i] != -1 && T2.centroid[j] != -1)
		if (!hasAns && isIso(T1.centroid[i], T2.centroid[j]))
			hasAns = true;

	cout << (hasAns ? "YES" : "NO") << el;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "Tree Isomorphism"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 1;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){
        cin >> n;

        T1.reset(); T2.reset();
        FOR(i, 1, n - 1){
        	int u, v; cin >> u >> v;
        	T1.g[u].pb(v);
        	T1.g[v].pb(u);
        }
        FOR(i, 1, n - 1){
        	int u, v; cin >> u >> v;
        	T2.g[u].pb(v);
        	T2.g[v].pb(u);
        }

        solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
