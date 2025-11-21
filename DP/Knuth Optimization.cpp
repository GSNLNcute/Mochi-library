// Source : http://oj.vnoi.info/problem/lehoi
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

const int N = 2e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, k, a[N];
ll sum[N];

struct Info{
	int l, r, p;
	Info(int _l = 0, int _r = 0, int _p = 0): l(_l), r(_r), p(_p) {}
};

ll f[N];
// h[i] là vị trí j nhỏ nhất thỏa f[j] + cost(j, i) đạt giá trị cực tiểu

ll cost(int l, int r){
	// hàm cost phải thỏa mãn bđt tứ giác: cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c)
	if (l >= r) return 0ll;
	l++;
	int d = (r - l + 1) / 2;
	ll R = sum[r] - sum[r - d];
	ll L = sum[l + d - 1] - sum[l - 1];
	return R - L;
}
void knuth(){
	deque <Info> dq;
  dq.push_back(Info(1, n, 0));

 	FOR(i, 1, n){
	 	f[i] = k + f[dq.front().p] + cost(dq.front().p, i);
	  // deque chỉ lưu giá trị từ h[i + 1] tới h[n]
	  ++dq.front().l;

    // nếu l > r, ta loại đoạn này khỏi deque
    if (dq.front().l > dq.front().r) dq.pop_front();

    while (!dq.empty()) {
      	auto [l, r, p] = dq.back();
      	if (f[i] + cost(i, l) < f[p] + cost(p, l)) dq.pop_back();
      	// p không còn là giá trị của h[l], h[l + 1], ..., h[r]
      	// lúc này, h[l] = h[l + 1] = ... = h[r] = i
      	else break;
    }

    if (dq.empty()) dq.push_back(Info(i + 1, n, i));
    // h[i + 1] = h[i + 2] = ... = h[n] = i
   
    else{
   		// tìm nhị phân vị trí pos nhỏ nhất thỏa mãn h[pos] = i
    	auto& [l, r, p] = dq.back();
      int low = l, high = r, pos = r + 1, mid;
      while (low <= high){
        mid = (low + high) >> 1;
        if (f[i] + cost(i, mid) < f[p] + cost(p, mid))
          pos = mid, high = mid - 1;
        else low = mid + 1;
      }

      // cập nhật đoạn (l, r, p) thành (l, pos - 1, p)
      r = pos - 1;
      if (pos <= n) dq.push_back(Info(pos, n, i));
      // h[pos] = h[pos + 1] = ... = h[n] = i
    }
  }
}
void solve(){
	FOR(i, 1, n) sum[i] = sum[i - 1] + a[i];

	memset(f, 0x3f, sizeof(f)); f[0] = 0;

	// FOR(i, 1, n) FOR(j, 0, i - 1)
	// 	minimize(f[i], k + f[j] + cost(j, i));

	knuth();
	cout << f[n];
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
		cin >> n >> k;
		FOR(i, 1, n) cin >> a[i];

		solve(); 
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}