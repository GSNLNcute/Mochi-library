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

ll binpow(ll a, ll b, ll MOD){
	ll ans = 1;
	while(b > 0){
		if (b & 1) ans = 1ll * ans * a % MOD;
		a = 1ll * a * a % MOD; b >>= 1;
	}
	return ans;
}
bool test(ll a, ll n, ll k, ll m){
	ll MOD = binpow(a, m, n);
	if (MOD == 1 || MOD == n - 1) return 1;
	FOR(i, 1, k - 1){
		MOD = (MOD * MOD) % n;
		if (MOD == n - 1) return 1;
	}
	return 0;
}
bool RabinMiller(ll n){
	if (n == 2 || n == 3 || n == 5 || n == 7) return 1;
    if (n < 11) return 0;

    ll k = 0, m = n - 1;
    while (m % 2 == 0){
        m /= 2; k++;
    }

    int tries = 3;
    REP(i, tries){
        ll a = rand() % (n - 3) + 2;
        if (!test(a, n, k, m)) return 0;
    }

    return 1;
}
bool CorrectRabinMiller(ll n){
	vi checkSet = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(const int& a : checkSet) if (n == a) return 1;
    if (n < 41) return 0;

    ll k = 0, m = n - 1;
    while (m % 2 == 0){
        m /= 2; k++;
    }

    for(const int& a : checkSet)
        if (!test(a, n, k, m)) return 0;

    return 1;
}

signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	#define NAME "TASK"
	if (fopen(NAME".inp", "r")){
		freopen(NAME".inp", "r", stdin);
   		freopen(NAME".out", "w", stdout);
	}

	bool multiTest = 1;
	int numTest = 1;

	if (multiTest) cin >> numTest;
	while(numTest--){
		ll n; cin >> n;
		cout << RabinMiller(n) << el;
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}