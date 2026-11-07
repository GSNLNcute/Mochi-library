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

int n, a[N];

// Áp dụng cho bài toán apply min/max trên 1 đoạn [l, r]

struct SegTreeBeatsMinRange{
    struct Node{
        ll sum;
        int max1, max2, cnt;
        Node(ll _sum = 0, int _m1 = -inf, int _m2 = -inf, int _cnt = 0): sum(_sum), max1(_m1), max2(_m2), cnt(_cnt) {}

        Node operator + (const Node& o) const{
            Node ans;
            ans.sum = sum + o.sum;
            if (max1 == o.max1){
                ans.max1 = max1;
                ans.max2 = max(max2, o.max2);
                ans.cnt = cnt + o.cnt;
            } else if (max1 > o.max1){
                ans.max1 = max1;
                ans.max2 = max(max2, o.max1);
                ans.cnt = cnt;
            } else {
                ans.max1 = o.max1;
                ans.max2 = max(max1, o.max2);
                ans.cnt = o.cnt;
            }
            return ans;
        }
    } node[(1 << (LG + 1)) + 5];

    void apply(int id, int val){          
        if (val >= node[id].max1) return;
        node[id].sum -= 1ll * (node[id].max1 - val) * node[id].cnt;
        node[id].max1 = val;
    }
    void down(int id){
        apply(id << 1, node[id].max1);
        apply(id << 1 | 1, node[id].max1);      
    }
    void build(int id = 1, int l = 1, int r = n){
        if (l == r){
            node[id] = Node(a[l], a[l], -inf, 1);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        node[id] = node[id << 1] + node[id << 1 | 1];
    }
    void update(int u, int v, int val, int id = 1, int l = 1, int r = n){
        if (v < l || r < u || val >= node[id].max1) return;
        if (u <= l && r <= v && node[id].max2 < val){
            apply(id, val);
            return;
        }

        down(id);
        int mid = (l + r) >> 1;
        update(u, v, val, id << 1, l, mid);
        update(u, v, val, id << 1 | 1, mid + 1, r);
        node[id] = node[id << 1] + node[id << 1 | 1];
    }
    ll get(int u, int v, int id = 1, int l = 1, int r = n){
        if (v < l || r < u) return 0;
        if (u <= l && r <= v) return node[id].sum;

        down(id);
        int mid = (l + r) >> 1;
        return get(u, v, id << 1, l, mid) + get(u, v, id << 1 | 1, mid + 1, r);
    }
} Tree;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "SegTree Beats"
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
