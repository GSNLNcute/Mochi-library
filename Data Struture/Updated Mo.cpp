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
const int SQRTN = 2154;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

// Với mo update, cần phải dùng SQRT là n^2/3

// Cho n phần tử có màu a[i]. Có q truy vấn
// 1 u v : đổi màu u và v
// 2 l r: đếm số màu phân biệt trong đoạn [l, r]

int n, q;

int color[N], id_block[N];

struct Query{
    int l, r, id, time_update;

    bool operator< (const Query& a)const{
        if(id_block[l] != id_block[a.l]) return l < a.l;
        if(id_block[r] != id_block[a.r]) return id_block[l] & 1 ? r < a.r : r > a.r;
        return (id_block[l] + id_block[r]) & 1 ? time_update < a.time_update : time_update > a.time_update;
    }
};

ve <Query> queries;

struct Update{
    int u, v;
};

ve <Update> updates;

int res = 0;

namespace Handle_MO{
    int cnt_color[N + 5];

    void add(int i){
        if(++cnt_color[color[i]] == 1) res++;
    }

    void del(int i){
        if(--cnt_color[color[i]] == 0) res--;
    }
}

using namespace Handle_MO;

inline void rizzler(int i, int l, int r){
	// Hàm này có thể làm 2 chiều vì swap 2 lần trở về vị trí cũ, các hàm khác có thể phải cài hàm riêng
	// Xét có trong đoạn hay không vì ngoài đoạn không ảnh hưởng res
    const int &u = updates[i].u, &v = updates[i].v;
    if(l <= u and u <= r) del(u);
    if(l <= v and v <= r) del(v);
    swap(color[u], color[v]);
    if(l <= u and u <= r) add(u);
    if(l <= v and v <= r) add(v);
}

int ans[N + 5];

void solve(){
	FOR(i, 1, q) id_block[i] = i / SQRTN;
    sort(queries.begin(), queries.end());

    int u = 1, v = 0, now = -1;
     for(const Query &x : queries){
        const int &l = x.l, &r = x.r, &id = x.id, &query_time = x.time_update;

        while(v < r) add(++v);
        while(u < l) del(u++);
        while(u > l) add(--u);
        while(v > r) del(v--);

        while(now < query_time) rizzler(++now, l, r);
        while(now > query_time) rizzler(now--, l, r);

        ans[id] = res;
    }

    FOR(i, 1, q) if(~ans[i]) cout << ans[i] << el;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "Updated Mo"
    if (fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){
    	cin >> n >> q;
        FOR(i, 1, n) cin >> color[i];

        int cnt_update = -1;	    
	    FOR(i, 1, q){
	        int type, u, v; cin >> type >> u >> v;
	        if(type == 1){
	            updates.pb(Update{u, v});
	            cnt_update++;
	            ans[i] = -1;
	        }
	        else{
	            queries.pb(Query{u, v, i, cnt_update});
	        }
	    }
	    solve();
    }

    cerr << "\nTime used: " << clock() << "ms\n";
    return 0;
}
