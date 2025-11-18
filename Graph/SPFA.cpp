// Source : https://cses.fi/problemset/task/1673
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

int n, m;
ve <pii> g[N];

ll d[N];
int cnt[N];
bool inqueue[N];
queue <int> q;

ll SPFA(){
	memset(d, -0x3f, sizeof(d));
	memset(cnt, 0, sizeof(cnt));
	memset(inqueue, false, sizeof(inqueue));

    d[1] = 0; q.push(1);
    inqueue[1] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        inqueue[u] = false;

        for (const pii& tmp : g[u]){
            int v = tmp.fi, w = tmp.se;

            if (minimize(d[v], d[u] + w)){
                if (!inqueue[v]){
                    q.push(v); inqueue[v] = true;
                    
                    cnt[v]++;
                    if (cnt[v] > n) return -1; // Negative cycle
                }
            }
        }
    }

    return d[n];
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
		cin >> n >> m;
		FOR(i, 1, m){
			int u, v, w; cin >> u >> v >> w;
			g[u].pb(mp(v, w));
		}

		cout << SPFA();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}