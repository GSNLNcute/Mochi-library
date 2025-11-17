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

const int LIM = 1e6;
int min_prime[LIM + 5];
vi primes;

void sieve(){
	FOR(i, 2, LIM) if (!min_prime[i]){
		min_prime[i] = i;
		for(int j = i; 1ll * i * j <= LIM; j++)
			if (!min_prime[i * j]) min_prime[i * j] = i;
	}
}
vector<pii> small_factorization(int n){
	assert(n <= LIM);

	vector <pii> ans;
	while(n > 1){
		int p = min_prime[n];
		int cnt = 0;
		while(n % p == 0){
			cnt++; n /= p;
		}
		ans.pb(mp(p, cnt));
	}

	return ans;
}
vector<pii> large_factorization(ll n){
	assert(n <= 1ll * LIM * LIM);

	vector <pii> ans;
	for(const int& p : primes){
		if (1ll * p * p > n) break;
		int cnt = 0;
		while(n % p == 0){
			cnt++; n /= p;
		}
		ans.pb(mp(p, cnt));
	}

	return ans;
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