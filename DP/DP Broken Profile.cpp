// Source : 
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

// Đặt k domino 2*1 sao cho tổng các ô phủ lớn nhất

int n, m, k, a[N][16];
ll sum[N][16];
ll f[N][2 * N][16];
// Nghiệm khi tới hàng i, số domino đã đặt là j, mask của domino hàng này là t

vector <int> phanbu[16];

void solve(void){
	FOR(t, 0, (1 << m) - 1) FOR(p, 0, (1 << m) - 1)
		if ((t & p) == 0) phanbu[t].pb(p);

	FOR(i, 1, n) FOR(t, 0, (1 << m) - 1) FOR(j, 1, m)
		if (BIT(t, j - 1)) sum[i][t] += a[i][j];

	memset(f, -0x3f, sizeof(f));
	f[1][0][0] = 0;

	FOR(i, 1, n) FOR(sl, 0, k) FOR(t, 0, (1 << m) - 1) if (f[i][sl][t] > -INF){
		// th1 : dat them domino o hang i (chiem 2 o lien tiep)
		if (sl < k){
			FOR(j, 1, m - 1){
				if (BIT(t, j - 1)) continue;
				if (BIT(t, j)) continue;

				int p = t | MASK(j - 1) | MASK(j);
				maximize(f[i][sl + 1][p], f[i][sl][t] + a[i][j] + a[i][j + 1]);
			}
		}
		
		// th2 : dat domino doc xuong hang i+1
		if (i < n){
			for(int p : phanbu[t]){
				int num = sl + __builtin_popcount(p);
				if (num > k) continue;

				maximize(f[i + 1][num][p], f[i][sl][t] + sum[i][p] + sum[i + 1][p]);
			}
		}
	} 

	ll res = -INF;
	FOR(t, 0, (1 << m) - 1) maximize(res, f[n][k][t]);
	cout << res;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "DP Broken Profile"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){
        cin >> n >> m >> k;
		FOR(i, 1, n) FOR(j, 1, m) cin >> a[i][j];
		solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
