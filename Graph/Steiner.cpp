#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define FOR(i, a, b) for(int i = a, _b = b; i <= _b; i++)
#define FORD(i, a, b) for(int i = a, _b = b; i >= _b; i--)
const int N = 1e4 + 1;
const int K = 256;
const ll INF = 1e15 + 7;

#define MASK(x) (1 << x)
#define BIT(x, i) ((x >> i) & 1)

int n, m, k, T, a[N];
vector <pair<int,int>> g[N];

ll d[N][K]; bool dd[N];
pair<int,int> trace[N][K];

queue <int> q;

struct KQ{
	int mask, u, v;
};
vector <KQ> ans;

inline bool mini(ll& cur, const ll& val){
	return cur > val ? cur = val, 1 : 0;
}
void go(int u, int mask){
    if (u == 0 || mask == 0) return;

    int v = trace[u][mask].first;
    int pre = trace[u][mask].second;

    if (v != u and v != 0) ans.push_back({pre, v, u});
    go(v, pre); go(u, mask ^ pre);
}
void solve(){
	memset(d, 0x3f, sizeof(d));
	FOR(i, 1, n){
		d[i][a[i]] = 0;
		if (a[i] > 0) trace[i][a[i]] = make_pair(0, a[i]);
	}

	int all = MASK(k) - 1;

	FOR(mask, 0, all){
		for(int submask = mask; submask > 0; submask = (submask - 1) & mask){
			FOR(u, 1, n) if (mini(d[u][mask], d[u][submask] + d[u][mask ^ submask]))
				trace[u][mask] = make_pair(u, submask);	
		}

		FOR(u, 1, n){
			if (d[u][mask] < INF) q.push(u);
			dd[u] = 0;
		} 

		while(!q.empty()){
			int u = q.front(); q.pop(); dd[u] = 0;
			for(const pair<int,int>& nxt : g[u]){
				const int& v = nxt.first, w = nxt.second;
				if (mini(d[v][mask], d[u][mask] + w)){
	                q.push(v); dd[v] = 1;
					trace[v][mask] = make_pair(u, mask);
	            } 
			}
		}
	}

	cout << d[T][all] << '\n';
    go(T, all);

    cout << ans.size() << '\n';
    reverse(ans.begin(), ans.end());
    for(const KQ& tmp : ans){
        const int& mask = tmp.mask;
        FOR(i, 1, k) cout << BIT(mask, i - 1); cout << " ";
        cout << tmp.u << " " << tmp.v << '\n';
    }
}
signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("TAXI.inp", "r", stdin);
	freopen("TAXI.out", "w", stdout);

	cin >> n >> m >> k >> T;
	FOR(i, 1, k){
		int u; cin >> u;
		a[u] |= MASK(i - 1);
	} 
	FOR(i, 1, m){
		int u, v, w; cin >> u >> v >> w;
		g[u].push_back(make_pair(v, w));
		g[v].push_back(make_pair(u, w));
	}

	solve();

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}
