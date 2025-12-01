// Source : https://oj.vnoi.info/problem/match2
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

const int N = 200 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n;

int cost[N][N];

int f[N], g[N];
int p[N], way[N];
int minv[N], used[N];
int matchLeft[N];

void solve(){
   	FOR(i, 1, n){
        p[0] = i;

        FOR(tmp, 1, n) minv[tmp] = inf, used[tmp] = 0;

        int j0 = 0;
        do{
	        used[j0] = true;
	        int i0 = p[j0], j1 = 0;
	        ll delta = inf;

	       	FOR(j, 1, n){
	            if (!used[j]){
	                ll cur = cost[i0][j] - f[i0] - g[j];
	                if (cur < minv[j]){
	                    minv[j] = cur;
	                    way[j] = j0;
	                }
	                if (minv[j] < delta){
	                    delta = minv[j];
	                    j1 = j;
	                }
	            }
	        }

            FOR(j, 0, n){
                if (used[j]){
                    f[p[j]] += delta;
                    g[j] -= delta;
                } else minv[j] -= delta;
            }

            j0 = j1;
        } while (p[j0] != 0);

        // Augmentation
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    // p[j] = i means i(left) matched to j(right)
    // j = 1..n, p[0] unused

    ll ans = -g[0];

   	FOR(j, 1, n){
        int i = p[j];
        if (cost[i][j] >= inf) {
            cout << -1;
            return;
        }
    }

    cout << ans << "\n";
    FOR(j, 1, n) matchLeft[p[j]] = j;
    FOR(i, 1, n) cout << i << " " << matchLeft[i] << "\n";
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

		memset(cost, 0x3f, sizeof(cost));

		int u, v, c;
		while(cin >> u >> v >> c) minimize(cost[u][v], c);

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}