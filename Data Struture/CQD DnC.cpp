// Source : https://codeforces.com/problemset/problem/12/D
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

const int N = 5e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

// Giải bài toán x >= x0, y >= y0, z >= z0
// Thường có chiều thứ 3 là chiều thời gian
// Để thỏa điều kiện x > x0, cần chia nhóm rồi mới chia để trị

// Đề bài: tìm số điểm i mà tồn tại điểm j sao cho
// x[i] < x[j], y[i] < y[j], z[i] < z[j]

int n, G, K;        // G = số nhóm x phân biệt, K = số giá trị z phân biệt
int st[N];          // st[g] = vị trí bắt đầu nhóm g
int cnt[N];         // cnt[id] = số điểm lớn hơn hoàn toàn điểm id

struct point {
    int x, y, z, id;
    bool operator < (const point& other){
    	return x > other.x;
    }
} a[N];

bool cmpY(const point& p, const point& q){
    return p.y > q.y;                   
}

struct BIT{
	int bit[N];

	void init(){
		FOR(i, 1, n) bit[i] = 0;
	}
	void update(int p, int val){
		for(; p <= n; p += p & (-p)) bit[p] += val;
	}
	int get(int p){
		int ans = 0;
		for(; p > 0; p -= p & (-p)) ans += bit[p];
		return ans;
	}
	int query(int l, int r){
		return get(r) - get(l - 1);
	}
} bit;

void compress(){
	vi val;
	FOR(i, 1, n) val.pb(a[i].z);
	
	sort(ALL(val));
	val.resize(unique(ALL(val)) - val.begin());
	FOR(i, 1, n) a[i].z = upper_bound(ALL(val), a[i].z) - val.begin();
}
void cdq(int L, int R){
    int lo = st[L], hi = st[R + 1] - 1;

    if (L == R){                      // cùng x: chỉ sort theo y
        sort(a + lo, a + hi + 1, cmpY);
        return;
    }

    int mid = (L + R) / 2;				 // chia theo chỉ số NHÓM
    int m = st[mid + 1] - 1;             // [l..m]: x lớn hơn, [m+1..r]: x nhỏ hơn

    cdq(L, mid);
    cdq(mid + 1, R);

    // ---- Cross: j ở trái, i ở phải ----
    int p = lo, added = 0;
    FOR(i, m + 1, hi){
        while(p <= m && a[p].y > a[i].y){
            bit.update(a[p].z, 1);
            added++; p++;
        }
        // số j đã thêm có z_j > z_i
        cnt[a[i].id] += added - bit.get(a[i].z);
    }
    // ---- Hoàn tác BIT ----
    FOR(j, lo, p - 1) bit.update(a[j].z, -1);

    inplace_merge(a + lo, a + m + 1, a + hi + 1, cmpY);
}
void solve(){
	compress();
	sort(a + 1, a + n + 1);

	bit.init();

	G = 1; st[1] = 1;
    FOR(i, 2, n) if (a[i].x != a[i - 1].x) st[++G] = i;
    st[G + 1] = n + 1;

    cdq(1, G);

    int res = 0;
    FOR(i, 1, n) res += (cnt[i] > 0);
    cout << res;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "CQD DnC"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){
        cin >> n;
        FOR(i, 1, n) a[i].id = i;
       	FOR(i, 1, n) cin >> a[i].x;
       	FOR(i, 1, n) cin >> a[i].y;
       	FOR(i, 1, n) cin >> a[i].z;
        solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
