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
#define ppb pop_back
#define mp make_pair
#define umap unordered_map
#define uset unordered_set
#define elif else if
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
// 	if (x == 0) { fast_print('0'); return; }
// 	if (x < 0) {
// 		fast_print('-');
// 		x = -x;
// 	}
// 	__int128 p = 1;
// 	while (x / (p * 10)) p *= 10;
// 	while (p) {
// 		__int128 symb = x / p;
// 		fast_print((int)symb);
// 		x -= p * symb;
// 		p /= 10;
// 	}
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

/*
	- LCA O(1)
	- Path Decomposition O(log)
	- Next vertex on Path O(1)!!
	- LCA O(1)!
	- JUMP O(log)
	- get_subtree_size O(1)
*/
struct Tree {
	int n;
	vector<int> _lca;
	vector<vector<int>> g, h;
	vector<int> tin, tout,
		tsize, pref, depth, head, tour;
	void dfs0(int v, int _p) {
		tsize[v] = 1;
		pref[v] = _p;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			h[v].pb(sub);
			depth[sub] = depth[v] + 1;
			dfs0(sub, v);
			tsize[v] += tsize[sub];
		}
		for (int j = 0; j < le(h[v]); j++)
			if (tsize[h[v][j]] > tsize[h[v][0]]) 
				swap(h[v][j], h[v][0]);
	}
	void dfs1(int v, int &timer, int d) {
		tin[v] = timer++, head[v] = d;
		tour.pb(v);
		if (!h[v].empty())
			dfs1(h[v][0], timer, d);
		for (int j = 1; j < le(h[v]); j++) {
			int sub = h[v][j];
			dfs1(sub, timer, sub);
		}
		tout[v] = timer;
	}
	void init(vector<vector<int>> _g) {
		g = _g;
		n = le(g);
		tin.clear(), tout.clear(),
			tsize.clear(), h.clear(),
			pref.clear(), depth.clear(),
			_lca.clear(), head.clear(), tour.clear();
		tin.resize(n), tout.resize(n), tsize.resize(n),
			h.resize(n), pref.resize(n), depth.resize(n), head.resize(n);
		dfs0(0, -1);
		int timer = 0;
		dfs1(0, timer, 0);
		int t = 31 - __builtin_clz(n) + 1;
		_lca.resize(t * n);
		for (int i = 0; i < n; i++)
			_lca[tin[i]] = i;
		for (int i = 1; i < t; i++) {
			for (int j = 0; j < n; j++) {
				_lca[i * n + j] = _lca[(i - 1) * n + j];
				int k = j + (1 << (i - 1));
				if (k < n
					&& depth[_lca[(i - 1) * n + k]] <= depth[_lca[i * n + j]])
					_lca[i * n + j] = _lca[(i - 1) * n + k];
			}
		}
	}
	/*
		returns whether v is an ancestor of u
	*/
	bool anc(int v, int u) {
		return tin[v] <= tin[u] && tout[u] <= tout[v];
	}
	/*
		returns the size of subtree of `v` (include `v` itself) if `root` is root.
	*/
	int get_subtree_size(int v, int root) {
		if (anc(v, root)) {
			return n - tsize[next(v, root)];
		} else return tsize[v];
	}
	/*
		returns range [l; r) of all subtree of v
		complexity: O(1)
	*/
	pii get_range(int v) {
		return mp(tin[v], tout[v]);
	}
	/*
		returns lca(a, b)
		complexity: O(1)!
	*/
	int lca(int a, int b) {
		if (anc(a, b)) return a;
		if (anc(b, a)) return b;
		a = tin[a], b = tin[b];
		if (a > b) swap(a, b);
		int p = 31 - __builtin_clz(b - a + 1);
		a = _lca[p * n + a];
		b = _lca[p * n + b - (1 << p) + 1];
		return pref[(depth[a] < depth[b]) ? a : b];
	}
	/*
		returns vertex on depth depth[v] - k
		complexity: O(log)
	*/
	int jump(int v, int k) {
		while (v != -1) {
			int u = head[v];
			if (k <= depth[v] - depth[u]) {
				return tour[tin[v] - k];
			} else {
				k -= depth[v] - depth[u] + 1;
				v = pref[u];
			}
		}
		assert(false);
	}
	/*
		returns next vertex on a path from a to b or a if a == b
		complexity: O(1)!!
	*/
	int next(int a, int b) {
		if (a == b) return a;
		if (anc(a, b)) {
			a = tin[a] + 1, b = tin[b];
			int p = 31 - __builtin_clz(b - a + 1);
			a = _lca[p * n + a];
			b = _lca[p * n + b - (1 << p) + 1];
			return depth[a] < depth[b] ? a : b;
		} else return pref[a];
	}
	/*
		returns distance between vertices a and b
		complexity: O(1)
	*/
	int dist(int a, int b) {
		return depth[a] + depth[b] - 2 * depth[lca(a, b)];
	}
	/*
		decomposes path
		`up` is not included!
		complexity: O(log) 
	*/
	vector<pii> decompose_up(int up, int down) {
		vector<pii> ranges;
		while (head[down] != head[up]) {
			ranges.emplace_back(tin[down], tin[head[down]]);
			down = pref[head[down]];
		}
		if (up != down)
			ranges.emplace_back(tin[down], tin[up] + 1);
		return ranges;
	}
	/* 
		decomposes path
		from a to b plus lca if include_lca is specified
		complexity: O(log)
	*/
	vector<pii> decompose(int a, int b, bool include_lca) {
		int c = lca(a, b);
		vector<pii> path = decompose_up(c, a);
		if (include_lca) path.emplace_back(tin[c], tin[c]);
		vector<pii> end = decompose_up(c, b);
		for (int i = le(end) - 1; ~i; i--)
			path.emplace_back(end[i].y, end[i].x);
		return path;
	}
};

struct CentroidTree : public Tree {
	int estimate_size(int v, int _p, const vector<bool> &used) {
		int sz = 1;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			sz += estimate_size(sub, v, used);
		}
		return sz;
	}
	int collect_centroids(int v, int _p,
			const int &N, int &C1, int &C2, const vector<bool> &used) {
		int sz = 1;
		bool centroid = true;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (!used.empty() && used[sub]) continue;
			int t = collect_centroids(sub, v, N, C1, C2, used);
			if (2 * t > N) centroid = false;
			sz += t;
		}
		if (centroid && sz * 2 >= N) {
			if (C1 == -1) C1 = v;
			else C2 = v;
		}
		return sz;
	}
	vector<int> find_centroids(int traverse, const vector<bool> &used) {
		int a = -1, b = -1;
		collect_centroids(traverse, -1, n, a, b, used);
		vector<int> rez;
		if (a != -1) rez.pb(a);
		if (b != -1) rez.pb(b);
		return rez;
	}
	vector<int> find_centroids() {
		return find_centroids(0, {});
	}
};

signed main(signed argc, char *argv[]) {
	int n;
	scan n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scan a, b;
		a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	CentroidTree tree;
	tree.init(g);
	vector<int> t = tree.find_centroids();
	sort(t.begin(), t.end());
	print t;
}
