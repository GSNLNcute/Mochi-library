// Source : https://lqdoj.edu.vn/problem/forest5
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

const int N = 1e3 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, m, q;

ll BIT[4][N][N]; 

void update(int u, int v, int x){
    for(int i = u; i <= n; i += i & (-i))
        for(int j = v; j <= m; j += j & (-j)){
            BIT[0][i][j] += x;
            BIT[1][i][j] += u * x;
            BIT[2][i][j] += v * x;
            BIT[3][i][j] += u * v * x;
        }
}
void add(int x, int y, int u, int v, int val){
    update(x, y, val);
    update(x, v + 1, -val);
    update(u + 1, y, -val);
    update(u + 1, v + 1, val);
}
ll get(int u, int v){
    ll a[4] = {0, 0, 0, 0};
    REP(type, 4){
        for(int i = u; i > 0; i -= i & (-i))
            for(int j = v; j > 0; j -= j & (-j))
                a[type] += BIT[type][i][j];
    }
    return 1ll * a[0] * (u + 1) * (v + 1) - a[1] * (v + 1) - a[2] * (u + 1) + a[3];
}
ll query(int x, int y, int u, int v){
	return get(u, v) - get(x - 1, v) - get(u, y - 1) + get(x - 1, y - 1) + 1ll * (u - x + 1) * (v - y + 1);
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
		cin >> n >> m >> q;
		while(q--){
			int type; cin >> type;
			if (type == 1){
				int x, y, u, v, val; cin >> x >> y >> u >> v >> val;
				add(x, y, u, v, val);
			} else{
				int x, y, u, v; cin >> x >> y >> u >> v;
				cout << query(x, y, u, v) << el;
			}
		}
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}