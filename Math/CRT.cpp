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
const int MOD = 1e9 + 7;

struct CRT{
    int res;

    // Giải hệ phương trình đồng dư tìm ẩn x
    // x % p1 = r1 
    // x % p2 = r2 
    // ...

    CRT(){
        res = 0, prd = 1;
    }
    
    // Add condition: res % p == r
    void add(int p, int r){
        res += mul(r - res % p + p, euclid(prd, p).fi + p, p) * prd;
        prd *= p;
        if (res >= prd) res -= prd;
    }

    // Add condition: res % p == r  (p KHÔNG cần nguyên tố cùng nhau)
    // Sau khi gọi, prd = lcm các p đã thêm. Nếu vô nghiệm thì ok = false.
    void _add(int p, int r){
        if (!ok) return;
        r %= p; if (r < 0) r += p;
        int g = __gcd(prd, p);
        int d = ((r - res) % p + p) % p;      // d = (r - res) mod p
        if (d % g != 0){ ok = false; return; }
        int m = p / g;                         // modulo mới sau khi chia g
        int t = 0;
        if (m > 1){
            d /= g;
            int inv = euclid((prd / g) % m, m).fi % m;
            if (inv < 0) inv += m;
            t = mul(d % m, inv, m);
        }
        res += prd * t;                        // prd * t < prd * m = lcm
        prd = prd / g * p;
        res %= prd;
    }

	private:
	    int prd;
	    int mul(int a, int b, int p) {
	        a %= p, b %= p;
	        int q = (int) ((long double) a * b / p);
	        int r = a * b - q * p;
	        while (r < 0) r += p;
	        while (r >= p) r -= p;
	        return r;
	    }
	    pii euclid(int a, int b){
	        if (!b) return make_pair(1, 0);
	        pii r = euclid(b, a % b);
	        return mp(r.se, r.fi - a / b * r.se);
	    }
};

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