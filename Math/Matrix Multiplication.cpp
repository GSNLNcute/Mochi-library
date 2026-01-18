// Source : https://oj.vnoi.info/problem/latgach4
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
const int LG = 29;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 111539786;

struct Matrix{
	int n, m, mt[3][3];

	Matrix (int _n = 0, int _m = 0){
		n = _n; m = _m;
		memset(mt, 0, sizeof(mt));
	}

	Matrix operator * (const Matrix& other) const{
		Matrix res(n, other.m);
		FOR(i, 1, n) FOR(j, 1, other.m) FOR(k, 1, m){
			res.mt[i][j] += 1ll * mt[i][k] * other.mt[k][j] % MOD;
			if (res.mt[i][j] >= MOD) res.mt[i][j] -= MOD;
		}
		return res;
	}
	Matrix operator ^ (int b){
		Matrix res(n, m), a = *this;
		res.mt[1][1] = res.mt[2][2] = 1;
		while(b > 0){
			if (b & 1) res = res * a;
			b >>= 1; a = a * a;
		}
		return res;
	}
} A[LG + 1];

void process(){
	A[0] = Matrix(2, 2);
	A[0].mt[1][2] = A[0].mt[2][1] = A[0].mt[2][2] = 1;
	FOR(j, 1, LG) A[j] = A[j - 1] * A[j - 1];
}
Matrix fastPow(int b){
	Matrix res(2, 2); res.mt[1][1] = res.mt[2][2] = 1;
	while(b > 0){
		int j = __builtin_ctz(b);
		res = res * A[j];
		b -= MASK(j);
	}
	return res;
}
void solve(int n){
	Matrix A = fastPow(n - 1);
	Matrix B(1, 2); B.mt[1][1] = B.mt[1][2] = 1;
	Matrix C = B * A;
	cout << C.mt[1][2] << el;
}
signed main(){
 	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	#define NAME "TASK"
	if (fopen(NAME".inp", "r")){
		freopen(NAME".inp", "r", stdin);
   		freopen(NAME".out", "w", stdout);
	}

	process();

	bool multiTest = 1;
	int numTest = 1;

	if (multiTest) cin >> numTest;
	while(numTest--){
		int n; cin >> n;
		solve(n);
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}