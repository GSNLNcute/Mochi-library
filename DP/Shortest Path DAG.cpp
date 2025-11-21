// Source : https://gspvhcute24.contest.codeforces.com/group/QV0gWmE1IS/contest/554677/problem/I
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

const int N = 1500 + 5;
const int M = 1e4 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, m;
ve <pii> g[N];

struct Edge{
	int u, v, w;
	Edge(int _u = 0, int _v = 0, int _w = 0): u(_u), v(_v), w(_w) {}
} e[M];

struct Info{
	int u, w;
	Info(int _u = 0, int _w = 0): u(_u), w(_w) {}
	bool operator < (const Info& other) const{
		return w > other.w;
	}
};

int d[N][N], f[N][N];
pii trace[N][N];

int ans[M];

inline void dijiktras(const int& S){
	priority_queue <Info> pq; pq.push(Info(S, 0));
	d[S][S] = 0; f[S][S] = 1;

	while(!pq.empty()){
		Info cur = pq.top(); pq.pop();
		int u = cur.u; if (cur.w > d[S][u]) continue;

		for(const pii& nxt : g[u]){
			int v = nxt.fi, id = nxt.se;
			int w = e[id].w;

			if (d[S][v] > d[S][u] + w){
				d[S][v] = d[S][u] + w; f[S][v] = f[S][u];
				trace[S][v] = make_pair(u, id);

				pq.push(Info(v, d[S][v]));
			}
			else if (d[S][v] == d[S][u] + w){
				f[S][v] += f[S][u];
				if (f[S][v] >= MOD) f[S][v] -= MOD;
			}
		}
	}
}
void solve(){
	memset(d, 0x3f, sizeof(d));
	FOR(i, 1, n) dijiktras(i);

	FOR(x, 1, n) FOR(y, x + 1, n){
		int u = y;
		while(1){
			int v = trace[x][u].first, id = trace[x][u].second;

	        if(d[x][u] + e[id].w + d[v][y] == d[x][y]){
	        	if (1ll * f[x][u] * f[v][y] % MOD == f[x][y]) ans[id]++;
	        }
	        if(d[x][v] + e[id].w + d[u][y] == d[x][y]){
	        	if (1ll * f[x][v] * f[u][y] % MOD == f[x][y]) ans[id]++;
	        }	

			u = v; if (u == x) break;
		}
	}

	FOR(i, 1, m) cout << ans[i] << '\n';
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
		cin >> n >> m;
		FOR(i, 1, m){
			int u, v, w; cin >> u >> v >> w;
			g[u].pb(mp(v, i)); g[v].pb(mp(u, i));
			e[i] = Edge(u, v, w);
		}

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}