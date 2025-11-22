// Source : https://www.codechef.com/problems/AMCS03
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
const ll INF = 2e10 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;
const double eps = 1e-9;

int n, K, s[N], d[N];

double f(double t){
	double vmax = 0, vmin = INF;
	FOR(i, 1, n){
		maximize(vmax, (double) s[i] * t + d[i]);
		minimize(vmin, (double) s[i] * t + d[i]);
	}
	return vmax - vmin;
}
void solve(){
	//return the minimum of f(x) in [l, r]
	double l = 0, r = K;
    while(r - l > eps){
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1), f2 = f(m2);     
        if (f1 > f2) l = m1;
        else r = m2;
    } 
    cout << setprecision(6) << fixed << f(l); 
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
		cin >> n >> K;
		FOR(i, 1, n) cin >> s[i] >> d[i];
		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}