#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FORD(i, a, b) for(int i = a; i >= b; i--)
const int N = 1e4 + 3;
const int INF = 1e9 + 7;
const int LIM = 30000;

int n;

int kc[LIM + 3];
int sz = 0;

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
	} it[(1 << 18) + 3];
	int lazy[(1 << 18) + 3];

	void build(int id, int l, int r){
		lazy[id] = it[id].mi = 0;
		it[id].cnt = kc[r] - kc[l - 1];
		if (l == r) return;

		int mid = (l + r) / 2;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
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
	void update(int id, int l, int r, int u, int v, int val){	
		down(id, l == r);

		if (v < l || r < u) return;
		if (u <= l && r <= v){
			lazy[id] += val;
			down(id, l == r);
			return; 
		}

		int mid = l + r >> 1;
		update(id << 1, l, mid, u, v, val);
		update(id << 1 | 1, mid + 1, r, u, v, val);
		it[id] = it[id << 1] + it[id << 1 | 1];
	}
	int query(){
		return kc[sz - 1] - (it[1].mi > 0 ? 0 : it[1].cnt);
	}
} Tree;

struct Event{
	int y, l, r, val;
	bool operator < (const Event& other) const{
		return y < other.y;
	}
};
vector <Event> evt;

void compress(){
	vector <int> pos;
	for(const Event& cur : evt){
		pos.push_back(cur.l);
		pos.push_back(cur.r);
	}

	sort(pos.begin(), pos.end());
	pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
	sz = pos.size();

	FOR(i, 1, sz - 1) kc[i] = kc[i - 1] + pos[i] - pos[i - 1]; 
	for(Event& cur : evt){
		cur.l = upper_bound(pos.begin(), pos.end(), cur.l) - pos.begin();
		cur.r = lower_bound(pos.begin(), pos.end(), cur.r) - pos.begin();
	}
}
signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("area.inp", "r", stdin);
	freopen("area.ans", "w", stdout);

	cin >> n;
	FOR(i, 1, n){
		int x, y, u, v; cin >> x >> y >> u >> v;

		if (x >= u || y >= v) continue;
		evt.push_back({y, x, u, +1});
		evt.push_back({v, x, u, -1});
	}

	sort(evt.begin(), evt.end());

	compress();
	if (sz <= 1) return cout << 0, 0;

	Tree.build(1, 1, sz - 1);

	ll ans = 0;
	for(int i = 0; i < evt.size(); i++){
		if (i > 0) ans += 1ll * (evt[i].y - evt[i - 1].y) * Tree.query(); 
		Tree.update(1, 1, sz - 1, evt[i].l, evt[i].r, evt[i].val);
	}
	cout << ans;

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}
