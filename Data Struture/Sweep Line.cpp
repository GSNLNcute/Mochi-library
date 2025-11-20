// Source : https://oj.vnoi.info/problem/area
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
#define int long long
template<class T> bool minimize(T &a, T b){ return (a > (b) ? a = (b), 1 : 0); }
template<class T> bool maximize(T &a, T b){ return (a < (b) ? a = (b), 1 : 0); }
template<class T> T Abs(const T &x) { return (x<0?-x:x);}

const int N = 1e4 + 5;
const int SZ = 3e4;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n;

struct SegmentTree{
	struct node{
		int cnt, mi;
		node(int _cnt = 0, int _mi = 0){
			cnt = 0; mi = 0; 
		}
		node operator + (const node& k) const{
			node res;
			res.mi = min(mi, k.mi);
			if (mi == res.mi) res.cnt += cnt;
			if (k.mi == res.mi) res.cnt += k.cnt;
			return res;
		}
	} it[4 * SZ];
	int lazy[4 * SZ];

	void build_it(int id = 1, int l = 1, int r = SZ){
		lazy[id] = it[id].mi = 0; it[id].cnt = r - l + 1;
		if (l == r) return;

		int mid = (l + r) / 2;
		build_it(id << 1, l, mid);
		build_it(id << 1 | 1, mid + 1, r);
	}
	void down(int id, bool leaf){
		if (lazy[id] != 0){
			it[id].mi += lazy[id];

			if (!leaf){
				lazy[id << 1] += lazy[id];
				lazy[id << 1 | 1] += lazy[id];
			}

			lazy[id] = 0;
		}	
	}
	void update(int u, int v, int val, int id = 1, int l = 1, int r = SZ){	
		down(id, l == r);

		if (v < l || r < u) return;
		if (u <= l && r <= v){
			lazy[id] += val;
			down(id, l == r);
			return; 
		}

		int mid = (l + r) >> 1;
		update(u, v, val, id << 1, l, mid);
		update(u, v, val, (id << 1) | 1, mid + 1, r);
		it[id] = it[id << 1] + it[id << 1 | 1];
	}
	int query(){
		return SZ - (it[1].mi > 0 ? 0 : it[1].cnt);
	}
} Tree;

struct Info{
	int y, l, r, val;
	bool operator < (const Info& other) const{
		return y < other.y;
	}
};
vector <Info> events;

void solve(){
	Tree.build_it();
	sort(ALL(events));

	ll ans = 0;
	int j = 0;
	FOR(i, 0, SZ){
		while(j < (int) events.size() && events[j].y <= i){
			Tree.update(events[j].l, events[j].r, events[j].val);
			j++;
		} 

		ans += Tree.query(); 
	}

	cout << ans;
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
		cin >> n;
		FOR(i, 1, n){
			int x, y, u, v; cin >> x >> y >> u >> v;

			if (x >= u || y >= v) continue;
			events.push_back({y, x + 1, u, +1});
			events.push_back({v, x + 1, u, -1});
		}

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}