// Source : https://oj.vnoi.info/problem/shhv
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

const int N = 12 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, a[N];
int pos;

int fact[N];

int ans[N];
bool dd[N];

int calc(int i){
	if (i == n) return 0;
	
	int cnt = a[i] - 1;
	FOR(k, 1, i - 1) cnt -= (a[k] < a[i]);
	return cnt * fact[n - i] + calc(i + 1);
}
void create(int i, int p){
	if (i == n + 1) return;

	FORD(num, n, 1) if (!dd[num]){
		int cnt = num - 1;
		FOR(k, 1, i - 1) cnt -= (ans[k] < num);

		if (cnt * fact[n - i] >= p) continue;

		ans[i] = num; dd[num] = 1;
		create(i + 1, p - cnt * fact[n - i]); 
		break;
	}
}
void solve(){
	fact[0] = 1;
	FOR(i, 1, 12) fact[i] = fact[i - 1] * i;

	cout << calc(1) + 1 << endl;

	create(1, pos);
	FOR(i, 1, n) cout << ans[i] << " ";
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
		int x;
		while(cin >> x) a[++n] = x;

		pos = a[n]; n--;

		solve();
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}