/*
                                                                                                     
                                             `-:://:::-                                             
                                           `//:-------:/:`                                          
                                          .+:--.......--:+`                                         
                                         `+:--..`````..--//`                                        
                                         .o:--..`` ``..--:o`                                        
                                         .o:--...```..---+/`                                        
                                       `/y+o/---....---:+o.                                         
                                   `...````-os+/:---:/+o/--.`                                       
              `-/+++++/:.      `...`       :h+d+oooo+/+-`   ...                                     
            `/++//:::://++-`....`         -.`//````````:`     `..`                                  
           `o+/::------://o/`           `-` -.          -`       `..`                               
 `---.-o/:./o/::-..``..-ЗАПУСКАЕМ      ..  ..            -`        `...       ``..``                
  `....o+:-++/:--.```..-://s.        `-`  .-              -`          `-o: .-//::::/:-`             
          `:s+/:--....-::/+s-`      .-   `-                -`           -///:--------:/:`           
           ./s+//:::::://oo-``..НЕЙРОННУЮ: СЕТЬ:::::::-`РАБОТЯГИ        `+:--........--:/`          
            .:ooo+++++osso-`    `.:-...`/` ./::-------:/:`   -`         :+--..``````.--:+:...-+:-`  
             `.-/+++++/+-.-`    -.   ``:so:/:--.......--:+`  `-```````o+/+--..`````..--:o/-..:s+:.  
                 ```````:``.. `-`     -` `+:--..`````..--/+-.../.`````..-o:--.......---/o.    `     
                        `:  `:-      -.  .o:--..`` ``..--:o`   `-`      `:o+:--------:+o-`          
                         `-`-...    ..   .o/--...```..--:+/`    `-`     `oy/so/////++o/.`           
                          -/`  `-` `- ``+s/o/:---...---:++.      `-`   .-../d://///:-.`             
                `.---..``-..-    .-/..`````-oo+/:::::/+o+-        `-``-`  `-.  ````                 
             `:++++/+++++-  ..``.-/:`      /y-:/++o++/:.`..`       ./.   `-                         
            -++/::::::://+/..:-``:` ..   `-.`  ```.```    `..`   `..`-` `-                          
       ``  -o//:--....-::/++` -.-`   `-`.-`                 `..`..`  `-.-                           
  -----ss+:++/:--.```..-://s.  /.     `::                    `-:.     ./`                           
  `````/:..+o/::-..``.--:/+s. ..-`   `-``-`                 ..` `-`  `-`-`                          
          `-s+/::-----::/+oo---``-` ..    .:-    ```      .-`     .-.-  `-`                         
           `:oo+//::://+os/..:`..-/:`      :y.-:::::::.`.-`        ./-`  `-`                        
            `./+oooooooo+/.`-    .-:...`.. .//:-------://`        `- `..` `:.                       
              ``.-::::-.``-/`  `-` `-  `oo:+:--.......--:/`      `-    `.:--h.``..```               
                          -.-`.-    .-   `+:--..`````..--//`    `-       /s-//::::::::.             
                         -` `/-      ..  .o:--..`` ``..--:o.```.-        `//:--------://`           
                        -` .-`.-`     -.`-o/--...```..--:+/.``-:....``:-.+:--....`...--:+`          
                       ..`-.   `-.   ``:os:o/:---...---:++.  `-     ``///+:-..``````.--:+-````-.`   
              `.:///////.-`      .:-..` -``-+o+/:::::/+o/.  `-         `:+:-..`````..--:o/:--/ys+-  
            `-++///////+o/. ``....`-.    :` `.:++++++/:.`  .-           -o/---......---/o.   `.`    
           `++//:-----::/+o:..`     .-`   :    ```````    .-           `+so+:--------:++-`          
  `````:-``:o/::-..`..--:/+o`         -.  `-             .-          `../../+o+////+o+:.`           
  -----syo/o+/:--.```..-://s.          .-` `-           .-        `...     ``-:////:-``             
       .` `/s//:--....-::/+s.            -. `-`        .-       `..`                                
           .+o+/:::--:://+s/-..`          .::+y  ```  .-     `..`                                   
            ./oo++////+oso-`   `....       :y-+:::::::/`   ...                                      
             `.:+oooooo/-`         `....-. .//:-------:/:-.`                                        
                ``...``                 /+:+:--.......--:+`                                         
                                         `+:--..`````..--//`                                        
                                         .o:--..`` ``..--:o`                                        
                                         .+/--...```..--:+/`                                        
                                         `-o/:---...---:++.                                         
                                          `-+o+/:---:/+o/.                                          
                                            `.:+oooo+/-.`                                           
                                               ``````                                               
*/

#ifdef aimbot
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <ostream>
#include <istream>
#include <typeinfo>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <limits>
#include <fstream>
#include <array>
#include <list>
#include <bitset>
#include <functional>
#include <random>
#include <cstring>
#include <chrono>

#define random escape__from__random__aetuhoetnuhshe
#define mt make_tuple
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define le(v) ((int)v.size())
#define f(i, n) for (int i = 0; i < (n); i++)
#define rof(i, n) for (int i = ((n) - 1); i >= 0; i--)
#define apply(v, act) for (auto &x : v) { act; }
#define log(args...) {string s = #args;deque<string> deq;\
string buf = "";int bal = 0;for (char c : s) {\
if (c == '(' || c == '[' || c == '{') {bal++;\
} else if (c == ')' || c == ']' || c == '}') {\
bal--;} else {if (bal == 0) {if (c == ',') {\
deq.pb(buf);buf = "";} else {if (c != ' ') {\
buf += c;}}}}}if (!buf.empty()) {deq.pb(buf);}\
smart_io::precall_print();smart_io::_print(deq, args);}

inline int min(const int &x, const int &y) { return (((y-x)>>(32-1))&(x^y))^x; }
inline int max(const int &x, const int &y) { return (((y-x)>>(32-1))&(x^y))^y; }
inline long long min(const long long &x, const long long &y) { return (((y-x)>>(64-1))&(x^y))^x; }
inline long long max(const long long &x, const long long &y) { return (((y-x)>>(64-1))&(x^y))^y; }

#define print    \
smart_io::precall_print(); \
cout,

#define scan cin,

#ifdef fast_allocator
const int MAXMEM = 200 * 1000 * 1024;
char _memory[MAXMEM];
size_t _ptr = 0;
void* operator new(size_t _x) { _ptr += _x; assert(_ptr < MAXMEM); return _memory + _ptr - _x; }
void operator delete (void*) noexcept {}
#endif

using namespace std;

char string_in_buffer[(int)260];


void fast_scan(int &x) { scanf("%d", &x); }
void fast_scan(long long &x) { scanf("%lld", &x); }
void fast_scan(unsigned long long &x) { scanf("%llu", &x); }
void fast_scan(double &x) { scanf("%lf", &x); }
void fast_scan(long double &x) { scanf("%Lf", &x); }
void fast_scan(char &x) {
    scanf("%c", &x);
    if (x == '\n') {
        fast_scan(x);
    }
}
void fast_scan(string &x) {
    scanf("%s", string_in_buffer);
    x = string(string_in_buffer);
}

template<class TFirst, class TSecond>
void fast_scan(pair<TFirst, TSecond> &p) {
    fast_scan(p.first);
    fast_scan(p.second);
}

template <class T>
void fast_scan(vector<T> &v) {
    for (auto &x : v) fast_scan(x);
}

void fast_print(const int &x) { printf("%d", x); }
void fast_print(const unsigned int &x) { printf("%u", x); }
void fast_print(const long long &x) { printf("%lld", x); }
void fast_print(const unsigned long long &x) { printf("%llu", x); }
void fast_print(const char &x) { printf("%c", x); };
// void fast_print(__int128 x) {
//  if (x == 0) { fast_print('0'); return; }
//  if (x < 0) {
//      fast_print('-');
//      x = -x;
//  }
//  __int128 p = 1;
//  while (x / (p * 10)) p *= 10;
//  while (p) {
//      __int128 symb = x / p;
//      fast_print((int)symb);
//      x -= p * symb;
//      p /= 10;
//  }
// };
void fast_print(const double &x) { printf("%.15lf", x); }
void fast_print(const long double &x) { printf("%.15Lf", x); }
void fast_print(const string &x) { printf("%s", x.c_str());}
void fast_print(const char v[]) { fast_print((string)v); }

template<class TFirst, class TSecond>
void fast_print(const pair<TFirst, TSecond> &p) {
    fast_print(p.first);
    fast_print(' ');
    fast_print(p.second);
}

template <class T>
void fast_print(const vector<T> &v) {
    if (v.empty()) return;
    fast_print(v[0]);
    for (int i = 1; i < v.size(); i++) {
        fast_print(' ');
        fast_print(v[i]);
    }
}

template <class T>
void fast_print(const vector<vector<T>> &v) {
    if (v.empty()) return;
    fast_print(v[0]);
    for (int i = 1; i < v.size(); i++) {
        fast_print('\n');
        fast_print(v[i]);
    }
}

template <class T>
void fast_print(const T &v) {
    for (const auto &x : v) {
        fast_print(x);
        fast_print(' ');
    }
}


using namespace std;


namespace smart_io {
    string print_start = "";
    string sep = " ";
    bool first_print = false;
    
    void precall_print() {
        fast_print(print_start);
        print_start = "\n";
        first_print = true;
    }
    
    void _print(deque<string>) {}
    template<class T, class... Args>
    void _print(deque<string> names, T elem, Args... args) {
        if (!first_print) {
            fast_print("\n");
        } else {
            first_print = false;
        }
        fast_print(names.front());
        fast_print(" = ");
        fast_print(elem);
        names.pop_front();
        _print(names, args...);
    }
} //namespace smart_io


template <class T>
ostream &operator,(ostream &os, const T &object) {
    if (!smart_io::first_print) {
        fast_print(smart_io::sep);
    } else {
        smart_io::first_print = false;
    }
    fast_print(object);
    return os;
}

template <class T>
istream &operator,(istream &is, T &object) {
    fast_scan(object);
    return is;
}

namespace random {
    using namespace std::chrono;
    mt19937 rng(duration_cast< milliseconds >(
                                              system_clock::now().time_since_epoch()
                                              ).count());
    uniform_real_distribution<> prob_dist(0.0, 1.0);
};

namespace typedefs {
    typedef long long ll;
    typedef unsigned long long ull;
    typedef pair<int, int> pii;
    typedef long double ld;
}

namespace numbers_operation {
    template<class T>
    inline T floor_mod(T a, const T &b) {
        a %= b; 
        if (a < 0) a += b;
        return a;
    }
}

using namespace numbers_operation;
using namespace typedefs;
using namespace random;


template<typename cap_t, typename excess_t, bool global_relabeling = true, bool min_cut_only = false, bool shuffle_edges = false>
struct Push_Relabel {
public:
    struct Edge{
        int to, rev;
        cap_t f, pushed{0};
    };
 
    Push_Relabel(int n_):n(n_), m(0){}
 
    void add_edge(int u, int v, cap_t c, cap_t c_rev = 0){
        edge_pool.emplace_back(u, v, c, c_rev);
        ++m;
    }
    excess_t max_flow(int s_, int t_){
        s = s_; t = t_;
        run_pr();
        return excess[t]-1;
    }
 
private:
    void compile_g(){
        g_pos.resize(n+1);
        if(shuffle_edges) random_shuffle(edge_pool.begin(), edge_pool.end());
        for(auto &e:edge_pool){
            ++g_pos[get<0>(e)];
            ++g_pos[get<1>(e)];
        }
        for(int i=0;i<n;++i){
            g_pos[i+1]+=g_pos[i];
        }
        g.resize(g_pos.back());
        for(auto &e:edge_pool){
            int u, v; cap_t c, c_rev;
            tie(u, v, c, c_rev) = e;
            const int i = --g_pos[u], j = --g_pos[v];
            g[i] = Edge{v, j, c, 0};
            g[j] = Edge{u, i, c_rev, 0};
        }
    }
    void global_relabel(){
        q.reserve(n);
        fill(h.begin(), h.end(), n);
        fill(h_cnt.begin(), h_cnt.end(), 0);
        h_cnt[n] = 1;
        q.push_back(t);
        h[t] = 0;
        for(auto &e:buck) e.clear();
        for(auto &e:buck_all) e.clear();
        for(auto it = q.begin();it<q.end();++it){
            const int u = *it;
            if(u != t && excess[u]){
                hi = h[u];
                buck[h[u]].push_back(u);
            }
            if(u != t) buck_all[h[u]].push_back(u);
            ++h_cnt[h[u]];
            for(int i = g_pos[u],i_end = g_pos[u+1];i < i_end;++i){
                Edge const&e = g[i];
                if(g[e.rev].f && h[e.to] == n){
                    h[e.to] = h[u]+1;
                    q.push_back(e.to);
                }
            }
        }
        hi_all = h[q.back()];
        assert(h[s] == n);
        q.clear();
    }
    void push(int u, Edge &e, excess_t f){
        if(!excess[e.to]){
            buck[h[e.to]].push_back(e.to);
        }
        Edge&back = g[e.rev];
        e.f-=f;
        e.pushed += f;
        back.f+=f;
        back.pushed -= f;
        excess[e.to]+=f;
        excess[u]-=f;
    }
    void init_pr(){
        compile_g();
        cur.assign(n, 0);
        copy(g_pos.begin(), prev(g_pos.end()), cur.begin());
        h.resize(n);
        excess.assign(n, 0);
        buck.resize(2*n);
        buck_all.resize(n+1);
        h_cnt.assign(2*n, 0);
        h[s] = n;
        h_cnt[n] = 1;
        h_cnt[0] = n-1;
        excess[t] = 1;
    }
    void run_pr(){
        init_pr();
        for(int i = g_pos[s],i_end = g_pos[s+1];i < i_end;++i){
            push(s, g[i], g[i].f);
        }
        hi = hi_all = 0;
        if(global_relabeling) global_relabel();
        if(!buck[hi].empty())
            for(;hi>=0;){
                int u = buck[hi].back(); buck[hi].pop_back();
                int u_cur = cur[u];
                //discharge
                if(!min_cut_only || h[u] < n)
                    while(excess[u] > 0){
                        if(__builtin_expect(u_cur == g_pos[u+1], false)){
                            int new_h = 1e9;
                            for(int i = g_pos[u],i_end = g_pos[u+1];i < i_end;++i){
                                auto const&e = g[i];
                                if(e.f && new_h > h[e.to]+1){
                                    new_h = h[e.to]+1;
                                    u_cur = i;
                                }
                            }
                            ++h_cnt[new_h];
                            h[u] = new_h;
                            if(__builtin_expect(!--h_cnt[hi] && hi < n, false)){
                                // gap relabel
                                for(int j = hi;j <= hi_all;++j){
                                    for(auto &f:buck_all[j]) if(!min_cut_only || h[f] < n){
                                            --h_cnt[h[f]];
                                            h[f] = n+1;
                                        }
                                    buck_all[j].clear();
                                }
                            }
                            hi = h[u];
                        } else {
                            Edge &e_cur = g[u_cur];
                            if(e_cur.f && h[u] == h[e_cur.to]+1){
                                push(u, e_cur, min<excess_t>(excess[u], e_cur.f));
                            } else ++u_cur;
                        }
                    }
                if(h[u] < n) {
                    hi_all = max(hi_all, h[u]);
                    buck_all[h[u]].push_back(u);
                }
                cur[u] = u_cur;
                while(hi>=0 && buck[hi].empty()) --hi;
            }
    }
 
    int n, m, s, t, hi, hi_all;
    vector<tuple<int, int, cap_t, cap_t> > edge_pool;
    vector<int> g_pos;
    vector<Edge> g;
    vector<int> q, cur, h, h_cnt;
    vector<excess_t> excess;
    vector<vector<int> > buck, buck_all;
 
    vector<int> vct;
    vector<int> ptr;
    bool dfs(int v) {
        vct.push_back(v);
        if (v == n - 1) {
            return true;
        }
        while (ptr[v] < g_pos[v + 1]) {
            auto &e = g[ptr[v]];
            if (e.pushed > 0) {
                if (dfs(e.to)) {
                    e.pushed--;
                    g[e.rev].pushed++;
                    return true;
                }
            }
            ptr[v]++;
        }
        vct.pop_back();
        return false;
    }
 
public:
    void dump() {
        for (int i = 0; i < n; i++) {
            for (int j = g_pos[i]; j < g_pos[i + 1]; j++ ){
                auto &e = g[j];
                auto &re = g[e.rev];
                db2(i, e.to);
                db2(e.f, re.f);
            }
        }
    }
    vector<vector<int>> restore() {
 
        ptr.assign(n, 0);
        for (int i = 0; i < n; i++) ptr[i] = g_pos[i];
 
        vector<vector<int>> ans;
        while (dfs(0)) {
            ans.push_back(vct);
            vct.clear();
        }
        return ans;
    }
};
 
signed main(signed argc, char *argv[]) {
    
}