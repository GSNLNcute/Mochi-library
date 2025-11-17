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

// Thuật toán tương tự như Lehmer, chỉ khác thay vì tính số lượng số nguyên tố thì ta tính tổng các số nguyên tố

const int LIM = 1e6;
ll a[LIM + 5], b[LIM + 5];

ll S(ll n) {
    ll r = (ll) sqrt(n);
    for (ll i = 1; i <= r; i++) {
        a[i] = i * (i + 1) / 2 - 1;
        b[i] = (n / i) * (n / i + 1) / 2 - 1;
    }
    for (ll p = 2; p <= r; p++)
        if (a[p] > a[p - 1]) {
            ll sp = a[p - 1];
            ll p2 = p * p;
            ll to = min(r, n/p2);
            for (ll i = 1; i <= to; i++) {
                ll vp = i * p;
                if (vp <= r) vp = b[vp];
                else vp = a[N / vp];
                b[i] -= p * (vp - sp);
            }
            for (ll v = r; v >= p2; v--)
                a[v] -= p * (a[v/p] - sp);
        }
    return b[1];
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
		
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}