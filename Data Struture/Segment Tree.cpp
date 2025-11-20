// Source : https://cses.fi/problemset/task/1648
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

int n, q, a[N];
ll st[4 * N];

void build(int id = 1, int l = 1, int r = n){
	if (l == r){
		st[id] = a[l];
		return;
	}

	int mid = (l + r) >> 1;
	build(id << 1, l, mid); 
	build((id << 1) + 1, mid + 1, r);

	st[id] = st[id << 1] + st[(id << 1) + 1];
}
void update(int x, int val){
	int id = 1, l = 1, r = n;
	while(l < r){
		int mid = (l + r) >> 1;
		if (x <= mid) id = id << 1, r = mid;
		else id = (id << 1) + 1, l = mid + 1;
	}

	st[id] = val;
	while(id > 1){
		id >>= 1;
		st[id] = st[id << 1] + st[(id << 1) + 1];
	}
}
ll query(int u, int v, int id = 1, int l = 1, int r = n){
	if (v < l || r < u) return 0;
	if (u <= l && r <= v) return st[id];

	int mid = (l + r) >> 1;
	return query(u, v, id << 1, l, mid) + query(u, v, (id << 1) + 1, mid + 1, r);
}
void solve(){
	build();
	while(q--){
		int c, u, v;
		cin >> c >> u >> v;
		if (c == 1) update(u, v);
		else cout << query(u, v) << endl;
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
		cin >> n >> q;
		FOR(i, 1, n) cin >> a[i];

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}