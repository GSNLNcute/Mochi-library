// Source : https://oj.vnoi.info/problem/mincost
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

const int N = 100 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

struct Edge{
    int u, v; 
    ll c, w;
    Edge() {}
    Edge(int _u, int _v, ll _c, ll _w) : u(_u), v(_v), c(_c), w(_w) {}
};

vi adj[N];
ve <Edge> edge; // lưu các cạnh (forward + reverse)
vi initCap;
ll pi[N];

pii pre[N];
bool vst[N];
ll d[N];

int n, m, k, S, T;
bool negCost = 0; // đồ thị có tồn tại cạnh có chi phí âm

void addEdge(int u, int v, ll c, ll w){
    // thêm cạnh xuôi và cạnh ngược (residual)
    adj[u].pb((int) edge.size()); 
    edge.pb(Edge(u, v, c, w)); // cạnh xuôi
    initCap.push_back(c); 

    adj[v].pb((int) edge.size());
    edge.pb(Edge(v, u, 0, -w)); // cạnh ngược
    initCap.push_back(0);

    negCost |= (w < 0); // kiểm tra nếu chí phí âm
}

void edgeflow(int id, ll flow){
    // flow luồng đi qua cạnh có chỉ số id
    edge[id].c -= flow; // cạnh uv
    edge[id ^ 1].c += flow; // cạnh vu
}
void bellmanford(){
    // thực hiện tiền xử lí khi mạng tồn tại cạnh có chi phí âm
    if(!negCost) return;
    
    FOR(i, 1, n) pi[i] = INF;
    pi[S] = 0;

    FOR(i, 2, n){
        bool upd = 0;
        for(const Edge& e: edge)
            if (minimize(pi[e.v], pi[e.u] + e.w)) upd = 1;
        if (!upd) break;
    }
}

pair<ll, ll> dijkstra(){
    // tìm đường tăng luồng
    FOR(i, 1, n) vst[i] = 0, d[i] = INF;
    d[S] = 0;

    priority_queue<pair<ll, int>> pq;
    pq.push(mp(0ll, S));

    int u, v; ll w, tmp;
    while (!pq.empty()) {
        tie (tmp, u) = pq.top(); pq.pop();
        if(vst[u]) continue;
        vst[u] = 1;

        for(const int id : adj[u]){
            v = edge[id].v; w = edge[id].w + pi[u] - pi[v];
            if(edge[id].c > 0 && minimize(d[v], d[u] + w)){
                pre[v] = mp(u, id);
                pq.push(mp(-d[v], v));
            }
        }
    }

    FOR(i, 1, n) pi[i] = min(pi[i] + d[i], INF); // cập nhật giá trị

    if (!vst[T]) return {-1, -1}; // không tìm thấy đường tăng luồng

    // tìm thấy đường tăng luồng
    // tìm điểm nghẽn và chi phí
    ll flow = INF, cost = 0;
    int cur = T;
    while(cur != S){
        minimize(flow, edge[pre[cur].second].c);
        cost += edge[pre[cur].second].w;
        cur = pre[cur].first;
    }
    return mp(flow, cost);
}

pair<ll, ll> MinCostMaxFlow(){
    bellmanford(); // tiền xử lí

    ll flow = 0, cost = 0, bottleneck, c;
    while((tie(bottleneck, c) = dijkstra(), bottleneck) > 0){ // tìm thấy đường tăng luồng
        // tăng luồng
        flow += bottleneck;
        cost += c * bottleneck;
        int cur = T;
        while(cur != S){
            edgeflow(pre[cur].second, bottleneck);
            cur = pre[cur].first;
        }
    }
    return mp(flow, cost); // {luồng cực đại, chi phí cực tiểu}
}
ll sendKFlow(ll k){
    bellmanford();
    ll cost = 0, bottleneck, c;
    while(k > 0 && (tie(bottleneck, c) = dijkstra(), bottleneck) > 0){ // tìm thấy đường tăng luồng
        // tăng luồng
        bottleneck = min(bottleneck, k);
        k -= bottleneck;
        cost += c * bottleneck;
        int cur = T;
        while(cur != S){
            edgeflow(pre[cur].second, bottleneck);
            cur = pre[cur].first;
        }
    }
    if (k != 0) return INF; // không thể gửi K luồng trên mạng
    return cost; // chi phí cực tiểu
}
void traceFlowEdges(){
    for (int id = 0; id < (int) edge.size(); id += 2){
        ll used = initCap[id] - edge[id].c;
        if (used > 0)
            cout << edge[id].u << " " << edge[id].v << " " << used << el;
    }
    cout << "0 0 0";
}

void solve(){
	ll ans = sendKFlow(k); if (ans == INF) return cout << -1, void();
	cout << ans << el;
	traceFlowEdges();
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
		cin >> n >> m >> k >> S >> T;
		// khởi tạo lại cấu trúc dữ liệu trước khi đọc đồ thị
		for(int i = 1; i <= n; ++i) adj[i].clear();
		edge.clear();
		
		FOR(i, 1, m){
			int u, v, c, d; cin >> u >> v >> c >> d;
			// mỗi cạnh vô hướng trong input được mô hình hoá bằng hai cạnh có hướng
			// thêm một cạnh u->v có sức chứa d và chi phí c, và ngược lại v->u
			addEdge(u, v, d, c);
			addEdge(v, u, d, c);
		}

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}
