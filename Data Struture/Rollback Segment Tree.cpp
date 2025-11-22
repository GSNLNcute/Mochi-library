// Source : https://www.codechef.com/problems/GERALD07
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

int n, m, k;

ve <pii> it[(1 << 18) + 3];

int par[N], sz[N];
stack <pii> st;
int cnt = 0;

map <pii, int> edge;

int find(int x){
	return par[x] == x ? x : find(par[x]);
}
void uni(int u, int v){
	u = find(u); v = find(v); if (u == v) return;
	if (sz[u] < sz[v]) swap(u, v);
	sz[u] += sz[v]; par[v] = u; 
	st.push(make_pair(u, v));
	--cnt;
}
void rollback(const int& len){
	while((int) st.size() > len){
		pii e = st.top(); st.pop();
		int u = e.fi, v = e.se;
		sz[u] -= sz[v]; par[v] = v;
		++cnt;
	}
}
void update(const int& u, const int& v, const pii& e, int id = 1, int l = 1, int r = k + 1){
	if (v < l || r < u) return;
	if (u <= l && r <= v){
		it[id].push_back(e);
		return;
	}

	int mid = (l + r) >> 1;
	update(u, v, e, id << 1, l, mid);
	update(u, v, e, id << 1 | 1, mid + 1, r);
}
void go(int id = 1, int l = 1, int r = k + 1){
	int og = (int) st.size();
	for(const pii& e : it[id]) uni(e.fi, e.se);

	if (l == r){
		cout << cnt << ' ';
		rollback(og); return;
	}

	int mid = (l + r) >> 1;
	go(id << 1, l, mid);
	go(id << 1 | 1, mid + 1, r);

	rollback(og);
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
		cin >> n >> m >> k;
		FOR(i, 1, m){
			int u, v; cin >> u >> v;
			edge[mp(u, v)] = 1;
		}
		FOR(i, 2, k + 1){
			int t, u, v; cin >> t >> u >> v;
			pii e = mp(u, v);

			if (t == 1) edge[e] = i;
			else{
				update(edge[e], i - 1, e);
				edge.erase(edge.find(e));
			} 
		}

		for(auto tmp : edge) update(tmp.second, k + 1, tmp.first);

		FOR(i, 1, n) par[i] = i, sz[i] = 1;
		cnt = n;

		go();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}