// Source : https://www.spoj.com/problems/MKTHNUM/
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

int n, q, a[N];

ve <pii> bit[N];

void update(int p, int val, int t){
	for(; p <= n; p += p & (-p))
		bit[p].pb(bit[p].empty() ? mp(t, val) : mp(t, val + bit[p].back().se));
}
int get(int p, int t){
	int ans = 0;
	for(; p > 0; p -= p & (-p)) if (!bit[p].empty()){
		if (bit[p].back().fi <= t) ans += bit[p].back().se;
		else{
			int j = upper_bound(bit[p].begin(), bit[p].end(), mp(t, inf)) - bit[p].begin() - 1;
			if (j >= 0) ans += bit[p][j].se;
		}
	}
	return ans;
}
int query(int l, int r, int t){
	return get(r, t) - get(l - 1, t);
}
void solve(){
	vi ord(n); iota(ord.begin(), ord.end(), 1);
	sort(ord.begin(), ord.end(), [](const int& u, const int& v){
		return a[u] < a[v];
	});
	REP(i, n) update(ord[i], 1, i); 

	while(q--){
		int l, r, k; cin >> l >> r >> k;
		assert(k <= r - l + 1);

		int lo = 0, hi = n - 1, res = -1;
		while(lo <= hi){
			int mid = (lo + hi) >> 1;
			if (query(l, r, mid) >= k) res = a[ord[mid]], hi = mid - 1;
			else lo = mid + 1; 
		}

		cout << res << el;
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