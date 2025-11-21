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

const int N = 1e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 142857;

const int n_primes = 4;
int primes[] = {3, 11, 13, 37};
int primes_pw[] = {27, 11, 13, 37};
// MOD = 142857 = 3^3 * 11^1 * 13^1 * 37^1 = 27 * 11 * 13 * 37

int phi[] = {18, 10, 12, 36}; // phi = prime_pw * (prime - 1)/prime
int rem[n_primes + 1];
vector<ll> fact[n_primes + 1], ifact[n_primes + 1];
int t;

ll binpow(ll a, ll n, ll mod){
    ll res = 1;
    for (; n > 0; n >>= 1){
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

void init(int x){
    fact[x].assign(primes_pw[x], 0);
    ifact[x].assign(primes_pw[x], 0);
    fact[x][0] = 1;
    FOR(i, 1, primes_pw[x] - 1){
        if (i % primes[x] != 0)
            fact[x][i] = (fact[x][i - 1] * i) % primes_pw[x];
        else
            fact[x][i] = fact[x][i - 1];
    }

    ifact[x][primes_pw[x] - 1] = binpow(fact[x][primes_pw[x] - 1],
                                        primes_pw[x] / primes[x] * (primes[x] - 1) - 1,
                                        primes_pw[x]);

    FORD(i, primes_pw[x] - 1, 1){
        if (i % primes[x] != 0)
            ifact[x][i - 1] = (ifact[x][i] * i) % primes_pw[x];
        else
            ifact[x][i - 1] = ifact[x][i];
    }
}

// i is the order of prime
ll C(ll N, ll K, ll R, int i){
    return (fact[i][N] * ifact[i][R] % primes_pw[i]) * ifact[i][K] % primes_pw[i];
}

int count_carry(ll n, ll k, ll r, ll p, ll t){
    ll res = 0;
    while (n >= t){
        res += (n / t - k / t - r / t);
        t *= p;
    }
    return res;
}

ll calc(ll N, ll K, ll R, int ord_pr){
    if (K > N) return 0;
    int prime = primes[ord_pr];
    int mod = primes_pw[ord_pr];
    ll res = 1;
    int vp = count_carry(N, K, R, prime, prime);
    int vp2 = count_carry(N, K, R, prime, mod);
    while(N > 0){
        res = (res * C(N % mod, K % mod, R % mod, ord_pr)) % mod;
        N /= prime; K /= prime; R /= prime;
    }
    res = res * binpow(prime, vp, mod) % mod;
    if ((vp2 & 1) && (prime != 2 || mod <= 4))
        res = (mod - res) % mod;

    return res;
}

ll CRT(ll N, ll K){
    ll res = 0;
   	REP(i, n_primes){
        int ans = calc(N, K, N - K, i) * rem[i] % MOD;
        res = (res + ans) % MOD;
    }
    return res;
}
signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	#define NAME "TASK"
	if (fopen(NAME".inp", "r")){
		freopen(NAME".inp", "r", stdin);
   		freopen(NAME".out", "w", stdout);
	}

	REP(i, n_primes){
        init(i);
        int tmp = MOD / primes_pw[i];
        rem[i] = tmp * binpow(tmp, phi[i] - 1, primes_pw[i]) % MOD;
    }

	bool multiTest = 0;
	int numTest = 1;

	if (multiTest) cin >> numTest;
	while(numTest--){
        ll N, K;
        cin >> N >> K;
        cout << CRT(N, K) << el;
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}