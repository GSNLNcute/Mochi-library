// Source : 
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

// Giải quyết các bài toán cần nối i tới các đỉnh trong đoạn [l, r]

int n, m, S;
ve <pii> g[MASK(LG + 2) + N + 5];

int numNode = 0;

ll f[MASK(LG + 2) + N + 5];

inline void addEdge(const int& u, const int& v, const int& w){
	g[u].pb(mp(v, w));
}

struct SegTree{

	// 0 : from [L, R] to leaf
	// 1 : from leaf to [L, R]

	int nodeID[MASK(LG + 1) + 5][2];
	vi rangeID;

	int build(int type, int id = 1, int l = 1, int r = n){
		int cur = ++numNode;
		nodeID[id][type] = cur;
		if (l == r){
			if (type == 0) addEdge(cur, l, 0);
			else addEdge(l, cur, 0);
			return cur;
		}

		int mid = (l + r) >> 1;
		int L = build(type, id << 1, l, mid);
		int R = build(type, id << 1 | 1, mid + 1, r); 

		if (type == 0){
			addEdge(cur, L, 0);
			addEdge(cur, R, 0);
		} else{
			addEdge(L, cur, 0);
			addEdge(R, cur, 0);
		}
		return cur;
	}
	void findID(const int& type, const int& u, const int& v, int id = 1, int l = 1, int r = n){
		if (v < l || r < u) return;
		if (u <= l && r <= v){
			rangeID.pb(nodeID[id][type]);
			return;
		}

		int mid = (l + r) >> 1;
		findID(type, u, v, id << 1, l, mid);
		findID(type, u, v, id << 1 | 1, mid + 1, r);
	}
	vi find(const int& type, const int& L, const int& R){
		rangeID.clear();
		findID(type, L, R);
		return rangeID;
	}
} Seg;

void addGroupEdge(const int& u, const int& type, const int& L, const int& R, const int& w){
	vi id = Seg.find(type, L, R);
	for(const int& nodeid : id){
		if (type == 0) g[u].pb(mp(nodeid, w));
		else g[nodeid].pb(mp(u, w));
	}
}
void buildGraph(){	
	numNode = n;
	REP(i, 2) Seg.build(i);

	FOR(i, 1, m){
		int type; cin >> type;
		if (type == 1){
			int u, v, w; cin >> u >> v >> w;
			addEdge(u, v, w);
		} else{
			int u, l, r, w; cin >> u >> l >> r >> w;
			addGroupEdge(u, type - 2, l, r, w);
		}
	}
}
void solve(){
	buildGraph();
	
	memset(f, 0x3f, sizeof(f)); f[S] = 0;
	priority_queue <pii, vector<pii>, greater<pii>> pq; pq.push(mp(0, S));
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if (d > f[u]) continue;

		for(const pii& e : g[u]) 
			if (minimize(f[e.fi], f[u] + e.se))
				pq.push(mp(f[e.fi], e.fi));
	}

	FOR(i, 1, n) cout << (f[i] > INF ? -1 : f[i]) << " ";
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "Graph SegTree"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){
        cin >> n >> m >> S;
        solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
