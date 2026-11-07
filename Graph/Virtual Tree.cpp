#include <bits/stdc++.h>
using namespace std;
#define uwu "Virtual Tree"
// Wireless: Each query give k vertices, find a node that have minimal sum distance to all vertices

typedef long long ll;
#define pb push_back
#define endl '\n'
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FORD(i, a, b) for(int i = a; i >= b; i--)
const int N = 5e5 + 3;
const ll INF = 1e18 + 7;

int n, q;
vector <pair<int,int>> g[N];
vector <int> query[N];
int h[N], up[N][20], st[N], ed[N];
ll d[N];

int num[N], par[N];
ll in[N], out[N];

int timedfs = 0;
void prepdfs(int u){
	st[u] = ++timedfs;
	for(pair<int,int> tmp : g[u]){
		int v = tmp.first, w = tmp.second;
		if (v == up[u][0]) continue;

		h[v] = h[u] + 1; d[v] = d[u] + w;
		up[v][0] = u;
		FOR(j, 1, 19) up[v][j] = up[up[v][j - 1]][j - 1];

		prepdfs(v);
	}
	ed[u] = timedfs;
}
int lca(int u, int v){
	if (h[u] < h[v]) swap(u, v);

	int tmp = h[u] - h[v];
	FOR(j, 0, 19) if (tmp & (1 << j)) u = up[u][j];
	if (u == v) return u;

	tmp = __lg(h[u]);
	FORD(j, tmp, 0) if (up[u][j] != up[v][j]) u = up[u][j], v = up[v][j];
	return up[u][0];
}
ll dist(int u, int v){
	return d[u] + d[v] - 2 * d[lca(u, v)];
}
bool cmp(int u, int v){
	return st[u] < st[v];
}
void solve(){
	while(q--){
		int len; cin >> len;

		vector <int> vertex;
		FOR(i, 1, len){
			int x; cin >> x;
			vertex.pb(x); num[x] = 1;
		}

		sort(vertex.begin(), vertex.end(), cmp);
		for(int i = 1; i < len; i++) vertex.pb(lca(vertex[i - 1], vertex[i]));

		sort(vertex.begin(), vertex.end());
		vertex.resize(unique(vertex.begin(), vertex.end()) - vertex.begin());
		sort(vertex.begin(), vertex.end(), cmp);

		stack <int> dfs;
		for(int v : vertex){
			while(!dfs.empty() && ed[dfs.top()] < st[v]){
				int u = dfs.top();
				ll w = dist(u, par[u]);
				num[par[u]] += num[u];
				in[par[u]] += in[u] + 1ll * num[u] * w;

				dfs.pop();
			} 

			if (!dfs.empty()) par[v] = dfs.top();
			dfs.push(v);
		}
		while(!dfs.empty()){
			int u = dfs.top();
			ll w = dist(u, par[u]);
			num[par[u]] += num[u];
			in[par[u]] += in[u] + 1ll * num[u] * w;

			dfs.pop();
		}
		
		for(int v : vertex){
			while(!dfs.empty() && ed[dfs.top()] < st[v]) dfs.pop();
			if (!dfs.empty()){
				int u = dfs.top(); ll w = dist(u, v); 
				out[v] = out[u] + 1ll * (len - num[v]) * w + in[u] - in[v] - 1ll * num[v] * w;
			}

			dfs.push(v);
		}

		ll ans = INF;
		for(int v : vertex){
			ans = min(ans, in[v] + out[v]);
			num[v] = in[v] = out[v] = par[v] = 0;
		}
		cout << ans << endl;
	}
}
signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	if(fopen(uwu".inp","r")){
		freopen(uwu".inp","r",stdin);
		freopen(uwu".out","w",stdout);
	}

	cin >> n >> q;
	FOR(i, 1, n - 1){
		int u, v, w; cin >> u >> v >> w;
		g[u].pb(make_pair(v, w));
		g[v].pb(make_pair(u, w));
	}

	prepdfs(1);
	solve();

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}