import sublime
import sublime_plugin
import os

# Template for normal .cpp files
TEMPLATE_CPP = """// Source : 
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
#define el   '\\n'
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define __builtin_popcount __builtin_popcountll
template<class T> bool minimize(T &a, T b){{ return (a > (b) ? a = (b), 1 : 0); }}
template<class T> bool maximize(T &a, T b){{ return (a < (b) ? a = (b), 1 : 0); }}
template<class T> T Abs(const T &x) {{ return (x<0?-x:x);}}

const int N = 1e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

signed main(){{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define NAME "{task}"
    if (fopen(NAME".inp", "r")){{
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }}

    bool multiTest = 0;
    int numTest = 1;

    if (multiTest) cin >> numTest;
    while(numTest--){{
        
    }}

    cerr << "\\nTime used: " << clock() << "ms\\n";
    return 0;
}}
"""

# Template for _sinh.cpp files
TEMPLATE_SINH = """#include <bits/stdc++.h>
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
#define el   '\\n'
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define __builtin_popcount __builtin_popcountll
template<class T> bool minimize(T &a, T b){{ return (a > (b) ? a = (b), 1 : 0); }}
template<class T> bool maximize(T &a, T b){{ return (a < (b) ? a = (b), 1 : 0); }}
template<class T> T Abs(const T &x) {{ return (x<0?-x:x); }}

#define name "{task}"

mt19937 rng((uint64_t) new char);
ll rd(ll l, ll r){{return (l > r) ? 0 : uniform_int_distribution<ll>(l, r)(rng);}}

const int N = 1e5 + 5;
const int LG = 17;
const ll INF = 1e17 + 7;
const int inf = 1e9 + 7;
const int MOD = 1e9 + 7;

void create(){{
    ofstream cout(name".inp");

    int n = rd(1, 100);
    cout << n;

    cerr << "done" << el;

    cout.close();
}}
signed main(){{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ofstream inp(name".inp"); inp.close();
    ofstream out(name".out"); out.close();
    ofstream ans(name".ans"); ans.close();

    system("g++ " name".cpp -o " name".exe");
    system("g++ " name"_trau.cpp -o " name"_trau.exe");

    int numTest = 100;
    FOR(i, 1, numTest){{
        create();

        system(name".exe");
        system(name"_trau.exe");

        cerr << "Test " << i << ": ";
        if(system("fc " name".out " name".ans")){{
            cerr << "WA" << el;
            return 0;
        }}

        cerr << "AC" << el;
    }}

    cerr << "\\nTime used: " << clock() << "ms\\n";
    return 0;
}}
"""

class AutoCppTemplate(sublime_plugin.EventListener):
    def on_post_save(self, view):
        fn = view.file_name()
        if not fn:
            return

        if not fn.endswith(".cpp"):
            return

        # Only for empty files
        if view.size() > 0:
            return

        base = os.path.basename(fn)
        task = os.path.splitext(base)[0]

        # Choose template based on filename
        if base.endswith("_sinh.cpp"):
            # Remove _sinh from task
            task = task[:-5]
            template = TEMPLATE_SINH
        else:
            template = TEMPLATE_CPP

        view.run_command("insert_cpp_template", {"task": task, "template": template})

class InsertCppTemplateCommand(sublime_plugin.TextCommand):
    def run(self, edit, task, template):
        text = template.format(task=task)
        self.view.insert(edit, 0, text)
