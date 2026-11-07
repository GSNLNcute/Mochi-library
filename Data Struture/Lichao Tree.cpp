// Source : https://oj.vnoi.info/problem/vomario
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

const int ST = (1 << 18) + 7;

// Tìm cực trị của các đường thẳng bậc 1 (ax + b) tại một hoành độ x truy vấn

// Bài toán: Có n đồ vật xuất hiện ở n thời điểm tuyến tính, mang cân nặng w[i] và giá trị e[i]
// Có thể chọn hoặc bỏ đồ vật thứ i
// Nếu chọn: cân nặng thành w[i], năng lượng là e[i]
// Di chuyển tới vật j: mất chi phí w * [x[i] - x[j]]
// Ban đầu đứng ở 0, cân nặng 0, năng lượng 0
// Di chuyển để không âm năng lượng
// Cần quản lý cây Li Chao ĐOẠN thẳng, không phải đường thẳng

vector <int> pos;
int sz = 0;

struct line{
	ll a, b;

	line() {
		a = 0; b = 0;
	}
	line (ll _a, ll _b) {
		a = _a; b = _b; 
	}
	ll operator () (int x){
		return 1ll * a * pos[x - 1] + b;
	}
} it[ST];

ll dp[N];

inline int getID(int val){
	return upper_bound(pos.begin(), pos.end(), val) - pos.begin();
}
void compress(){
	pos.pb(0); pos.pb(-INF); pos.pb(INF);
	FOR(i, 1, n) pos.pb(x[i]);

	sort(pos.begin(), pos.end());
	pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
	sz = N;
}
// Maximum Lichao
// Với Lichao đường thẳng, không cần truyền u, v
void update(int id, int l, int r, int u, int v, line L){
	if (v < l || r < u) return;
	if (l == r){
		if (it[id](l) < L(l)) it[id] = L;
		return;
	}

	int mid = l + r >> 1;
	if (u <= l && r <= v){
		if (it[id].a > L.a) swap(it[id], L);
		if (it[id](mid) < L(mid)){
			swap(it[id], L);
			update(id << 1, l, mid, u, v, L);
		}
		else update(id << 1 | 1, mid + 1, r, u, v, L);
		return;
	}

	update(id << 1, l, mid, u, v, L);
	update(id << 1 | 1, mid + 1, r, u, v, L);
}
ll get(int id, int l, int r, int x){
	if (l == r) return it[id](x);
	int mid = l + r >> 1;
	if (x <= mid) return max(it[id](x), get(id << 1, l, mid, x));
	else return max(it[id](x), get(id << 1 | 1, mid + 1, r, x));
}
void solve(){
	compress();

	FOR(i, 1, n) 

	ll res = 0;
	FOR(i, 1, n){

		// FOR(j, 0, i - 1) if (dp[j] - w[j] * abs(x[i] - x[j]) > 0)
		//	maximize(dp[i], dp[j] - w[j] * abs(x[i] - x[j]) + e[i])

		dp[i] = get(1, 1, sz, getID(x[i])) + e[i];
		res = max(res, dp[i]);

		int L = -INF;
		int R = INF;
		update(1, 1, sz, getID(x[i]), getID(R), line(-w[i], dp[i] + 1ll * w[i] * x[i]));
		update(1, 1, sz, getID(L), getID(x[i]), line(w[i], dp[i] - 1ll * w[i] * x[i]));
	}

	cout << res;
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
        cin >> n;
		FOR(i, 1, n) cin >> x[i] >> w[i] >> e[i];

		solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
