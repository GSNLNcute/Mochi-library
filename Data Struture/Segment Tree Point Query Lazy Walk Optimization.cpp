// Source : https://cses.fi/problemset/task/1651/
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

ll lazy[4 * N];

void update(int u, int v, int val, int id = 1, int l = 1, int r = n){
	if (v < l || r < u) return;
	if (u <= l && r <= v){
		lazy[id] += val; return;
	}

	int mid = (l + r) >> 1;
	update(u, v, val, id << 1, l, mid);
	update(u, v, val, (id << 1) + 1, mid + 1, r);
}
ll get(int i){
	int id = 1, l = 1, r = n;
	ll sum = 0;
	while(1){
		sum += lazy[id];
		if (l == r) break;
	
		int mid = (l + r) >> 1;
		if (i <= mid) id = id << 1, r = mid;
		else id = (id << 1) + 1, l = mid + 1;
	}

	return sum + a[i];
}
void solve(){
	while(q--){
		int t; cin >> t;
		if (t == 1){
			int l, r, val; cin >> l >> r >> val;
			update(l, r, val);
		} else{
			int u; cin >> u;
			cout << get(u) << el;
		}
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