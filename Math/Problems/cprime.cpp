// Source : https://oj.vnoi.info/problem/cprime
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

const int N = 1e4 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;

ll a[N + 5], b[N + 5];

ll Lehmer(ll n){
	if (n <= 1) return 0;

    ll r = (ll) sqrt(n);
    for (ll i = 1; i <= r; i++) {
        a[i] = i - 1;
        b[i] = n / i - 1;
    }
    for (ll p = 2; p <= r; p++)
        if (a[p] > a[p - 1]) {
            ll sp = a[p - 1];
            ll p2 = p * p;
            ll to = min(r, n / p2);
            for (ll i = 1; i <= to; i++) {
                ll vp = i * p;
                if (vp <= r) vp = b[vp];
                else vp = a[n / vp];
                b[i] -= (vp - sp);
            }
            for (ll v = r; v >= p2; v--)
                a[v] -= (a[v / p] - sp);
        }
    return b[1];
}

signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	#define NAME "cprime"
	if (fopen(NAME".inp", "r")){
		freopen(NAME".inp", "r", stdin);
   		freopen(NAME".out", "w", stdout);
	}

	cout << setprecision(1) << fixed;

	int n;
	while(1){
		cin >> n; if (n == 0) break;

		ll num = Lehmer(n);
		long double k = (long double) n / log(n);
		long double ans = (long double) abs(num - k) / num;
		ans = (double) ans * 100;
		cout << ans << el;  
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}