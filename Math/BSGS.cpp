// Source : https://www.spoj.com/problems/MOD/
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

namespace BSGS{
    int binpow(long long a, long long k, int mod) {
        ll res = 1;
        for (; k; k >>= 1, a = a * a % mod)
            if (k & 1) res = res * a % mod;
        return res;
    }
    // Tra ve x nho nhat thoa man a ^ x % m = b % m.
    int discrete_log_BSGS(int a, int b, int m) {
        a %= m, b %= m;
        if (m == 1) return 0;

        int n = sqrt(m) + 1;
        int k = 1, add = 0, g;
        while ((g = __gcd(a, m)) > 1) {
            if (b == k) return add;
            if (b % g) return -1;

            b /= g; m /= g;
            ++add;

            k = (k * 1ll * (a / g)) % m;
            a %= m;

            if (m == 1) return add;
        }

        unordered_map<int, int> vals;
        for (int q = 0, cur = b; q <= n; ++q){
            vals[cur] = q;
            cur = 1LL * cur * a % m;
        }

        int step = binpow(a, n, m);
        for (int p = 1, f1 = k; p <= n; p++) {
            f1 = 1LL * f1 * step % m;
            if (vals.count(f1)){
                int ans = n * p - vals[f1] + add;
                return ans;
            }
        }

        return -1;
    }
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "BSGS"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(true){
    	int x, z, k;
    	cin >> x >> z >> k;
    	if (x == 0 && z == 0 && k == 0) break; 

        int ans = BSGS::discrete_log_BSGS(x, k, z);
        if (ans == -1) cout << "No Solution";
        else cout << ans;
       	cout << el;
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
