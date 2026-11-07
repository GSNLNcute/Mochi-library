// Source : https://www.spoj.com/problems/GCDEX/
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

const int MAXN = 1e6 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

namespace Mobius {    
    int minPrime[MAXN];     
    vector<int> primes;       
    
    int mu[MAXN];      // Hàm Mobius mu(n)
    ll phi[MAXN];      // Phi hàm Euler phi(n)
    ll sum_mu[MAXN];   // Tổng tiền tố của mu(n)
    ll sum_phi[MAXN];  // Tổng tiền tố của phi(n)

    void init(int n){
        mu[1] = phi[1] = sum_mu[1] = sum_phi[1] = 1;
        
        FOR(i, 2, n){
            if (minPrime[i] == 0) {
                minPrime[i] = i;
                primes.push_back(i);
                mu[i] = -1; phi[i] = i - 1;
            }
            
            for (const int& p : primes){
                if (p * i > n) break;
                minPrime[p * i] = p;
                if (i % p == 0) {
                    // p là ước của i -> p^2 là ước của (p * i)
                    mu[p * i] = 0;
                    phi[p * i] = phi[i] * p;
                    break; 
                } else {
                    // p và i nguyên tố cùng nhau
                    mu[p * i] = mu[i] * -1;
                    phi[p * i] = phi[i] * (p - 1);
                }
            }
            
            sum_mu[i] = sum_mu[i - 1] + mu[i];
            sum_phi[i] = sum_phi[i - 1] + phi[i];
        }
    }
}

inline int next_block(int n, int i) {
    return n / (n / i);
}
void solve() {
    int n;
    while (cin >> n && n != 0) {
        ll res = 0;
        for (int i = 1, j; i <= n; i = j + 1) {
            j = next_block(n, i);
            ll q = n / i; 
            ll numPairs = q * (q - 1) / 2;
            ll sum_f = Mobius::sum_phi[j] - Mobius::sum_phi[i - 1];
            
            res += pairs * sum_f;
        }
        
        cout << res << "\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "Mobius"
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
