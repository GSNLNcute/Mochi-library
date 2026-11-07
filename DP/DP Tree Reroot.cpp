// Source : https://codeforces.com/problemset/problem/1324/F
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

int n, a[N];
vi g[N];

int dp[N], ans[N];

void dfs(int u, int p){
    dp[u] = a[u];
    for(int v : g[u]) if(v != p){
        dfs(v, u);
        dp[u] += max(0, dp[v]);
    }
}
void reroot(int u, int p){
    ans[u] = dp[u];
    for(const int& v : g[u]) if (v != p){
        int old_u = dp[u], old_v = dp[v];

        dp[u] -= max(0, dp[v]);      // bỏ v ra khỏi u
        dp[v] += max(0, dp[u]);      // gắn u (đã bỏ v) vào v, coi u như con của v

        reroot(v, u);

        dp[u] = old_u;               // revert
        dp[v] = old_v;
    }
}
void solve(){
	dfs(1, 0); reroot(1, 0);
	FOR(i, 1, n) cout << ans[i] << " ";
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "DP Tree Reroot"
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
        	cin >> a[i];
        	if (a[i] == 0) a[i] = -1;
        }
        FOR(i, 1, n - 1){
        	int u, v; cin >> u >> v;
        	g[u].pb(v); g[v].pb(u);
        }
        solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
