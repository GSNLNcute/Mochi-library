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

const int N = 1e3 + 5;
const int LG = 10;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

int n, m, a[N][N];

int t[MASK(LG + 1) + 5][MASK(LG + 1) + 5];

void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry){
        if (lx == rx) t[vx][vy] = a[lx][ly];
        else t[vx][vy] = t[vx << 1][vy] + t[vx << 1 | 1][vy];
    } else {
        int my = (ly + ry) >> 1;
        build_y(vx, lx, rx, vy << 1, ly, my);
        build_y(vx, lx, rx, vy << 1 | 1, my + 1, ry);
        t[vx][vy] = t[vx][vy << 1] + t[vx][vy << 1 | 1];
    }
}
void build_x(int vx, int lx, int rx) {
    if (lx != rx){
        int mx = (lx + rx) >> 1;
        build_x(vx << 1, lx, mx);
        build_x(vx << 1 | 1, mx + 1, rx);
    }
    build_y(vx, lx, rx, 1, 1, m);
}
int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry) return 0;
    if (ly == tly && try_ == ry) return t[vx][vy];
    int tmy = (tly + try_) >> 1;
    return sum_y(vx, vy << 1, tly, tmy, ly, min(ry, tmy))
         + sum_y(vx, vy << 1 | 1, tmy + 1, try_, max(ly, tmy + 1), ry);
}
int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx) return 0;
    if (lx == tlx && trx == rx) return sum_y(vx, 1, 1, m, ly, ry);
    int tmx = (tlx + trx) >> 1;
    return sum_x(vx << 1, tlx, tmx, lx, min(rx, tmx), ly, ry)
         + sum_x(vx << 1 | 1, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
}
void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry){
        if (lx == rx) t[vx][vy] = new_val;
        else t[vx][vy] = t[vx << 1][vy] + t[vx << 1 | 1][vy];
    } else{
        int my = (ly + ry) >> 1;
        if (y <= my) update_y(vx, lx, rx, vy << 1, ly, my, x, y, new_val);
        else update_y(vx, lx, rx, vy << 1 | 1, my + 1, ry, x, y, new_val);
        t[vx][vy] = t[vx][vy << 1] + t[vx][vy << 1 | 1];
    }
}
void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx){
        int mx = (lx + rx) >> 1;
        if (x <= mx) update_x(vx << 1, lx, mx, x, y, new_val);
        else update_x(vx << 1 | 1, mx + 1, rx, x, y, new_val);
    }
    update_y(vx, lx, rx, 1, 1, m, x, y, new_val);
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
		
	}

	cerr << "\nTime used: " << clock() << "ms\n";
	return 0;
}