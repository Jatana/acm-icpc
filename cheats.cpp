
========== FFTNum ==========

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define sz(a) int((a).size())
typedef long long ll;
typedef vector<int> vi;
const int MOD = 119 << 23 | 1;
const int FFTMOD = 119 << 23 | 1;
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

struct NTT {
    static const int MAXF = 1 << 20;
    int pr;
    int rts[MAXF + 1];
    int bitrev[MAXF];
    int iv[MAXF + 1];

    int fpow(int a, int k, int p) {
        if (!k) return 1;
        int res = a, tmp = a;
        k--;
        while (k) {
            if (k & 1) {
                res = (long long) res * tmp % p;
            }
            tmp = (long long) tmp * tmp % p;
            k >>= 1;
        }
        return res;
    }
    void init(int pr, int pw) {
        this->pr = pr;
        int k = 0; while ((1 << k) < MAXF) k++;
        bitrev[0] = 0;
        for (int i = 1; i < MAXF; i++) {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << k - 1);
        }
        pw = fpow(pw, (pr - 1) / MAXF, pr);
        rts[0] = 1;
        for (int i = 1; i <= MAXF; i++) {
            rts[i] = (long long) rts[i - 1] * pw % pr;
        }
        for (int i = 1; i <= MAXF; i <<= 1) {
            iv[i] = fpow(i, pr - 2, pr);
        }
    }
    void dft(int a[], int n, int sign) {
        int d = 0; while ((1 << d) * n != MAXF) d++;
        for (int i = 0; i < n; i++) {
            if (i < (bitrev[i] >> d)) {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int len = 2; len <= n; len <<= 1) {
            int delta = MAXF / len * sign;
            for (int i = 0; i < n; i += len) {
                int *w = sign > 0 ? rts : rts + MAXF;
                for (int k = 0; k + k < len; k++) {
                    int &a1 = a[i + k + (len >> 1)], &a2 = a[i + k];
                    int t = (long long) *w * a1 % pr;
                    a1 = a2 - t;
                    a2 = a2 + t;
                    a1 += a1 < 0 ? pr : 0;
                    a2 -= a2 >= pr ? pr : 0;
                    w += delta;
                }
            }
        }
        if (sign < 0) {
            int in = iv[n];
            for (int i = 0; i < n; i++) {
                a[i] = (long long) a[i] * in % pr;
            }
        }
    }
    void multiply(int a[], int b[], int na, int nb, int c[]) {
        static int fa[MAXF], fb[MAXF];
        int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = 0;
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        dft(fa, n, 1), dft(fb, n, 1);
        for (int i = 0; i < n; i++) fa[i] = (long long) fa[i] * fb[i] % pr;
        dft(fa, n, -1);
        for (int i = 0; i < n; i++) c[i] = fa[i];
    }
    vector<int> multiply(vector<int> a, vector<int> b) {
        static int fa[MAXF], fb[MAXF], fc[MAXF];
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        multiply(fa, fb, na, nb, fc);
        int k = na + nb - 1;
        vector<int> res(k);
        for (int i = 0; i < k; i++) res[i] = fc[i];
        return res;
    }
} ntt;

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    vector<int> A = {1, 1, 2};
    vector<int> B = {9, 1, 3};
    ntt.init(MOD, 3);
    vector<int> rez = ntt.multiply(A, B); 
    for (int x : rez) {
        cout << x << " ";
    }
}

========== FFTSolver ==========

namespace FFTSolver {
	typedef complex<ld> plex;

	vector<vector<plex>> W;

	int __get_log(int N) {
		return 31 - __builtin_clz(N);
	}

	void construct_roots(int N) {
		int n = __get_log(N);
		while (len(W) < n) {
			int layer_log = len(W);
			int k = (1 << layer_log);		
			W.pb(vector<plex>());
			W.back().resize(k);
			for (int j = 0; j < k; j++) {
				W.back()[j] = (plex(cos((2 * M_PI * (ld)j) / (ld)(2 * k)), sin((2 * M_PI * (ld)j) / (ld)(2 * k))));
			}
		}
	}

	void __fft(plex *a, int N, plex e, bool inv) {
		for (int k = 1, id = 0; k < N; k *= 2, id++) {
			for (int i = 0; i < N; i += k * 2) {
				for (int j = 0; j < k; j++) {
					if (!inv) {
						plex x = a[i + j], y = a[i + j + k];
						a[i + j] = x + W[id][j] * y;
						a[i + j + k] = x - W[id][j] * y;
					} else {
						plex x = a[i + j], y = a[i + j + k];
						a[i + j] = x + conj(W[id][j]) * y;
						a[i + j + k] = x - conj(W[id][j]) * y;
					}
				}
			}
		}	
	}

	template <class T>
	void reverse_permutation(T *a, int N) {
		int N_2 = (N >> 1), r = 0;
		for (int x = 1; x < N; ++ x) {
			int h = N_2;
			while (((r ^= h) & h) == 0) h >>= 1;
			if (r > x) swap(a[x], a[r]);
		}
	}

	void complex_convolution(plex *a, int N, bool inv) {
		reverse_permutation(a, N);
		construct_roots(N);
		plex e(cos(2.0 * M_PI / (ld)N), sin(2.0 * M_PI / (ld)N));
		if (inv) e = conj(e);
		__fft(a, N, e, inv);
	}

	void transform_2_convolutions(plex *a, int N) {
		plex div_x = plex(0, 1) * (4.0 * N);
		for (int i = 0; i < N / 2; i++) {
			int j = (N - i) % N;
			a[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j])) / div_x;
		}
		for (int i = N - 1; i > N / 2; i--) {
			a[i] = conj(a[N - i]);
		}
		a[N / 2] = (a[N / 2] + conj(a[N / 2])) * (a[N / 2] - conj(a[N / 2])) / div_x;
	}

	inline vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
		int N = len(a) + len(b) + 1;
		while (__builtin_popcount(N) != 1) {
			N++;
		}

		plex e(cos(2 * M_PI / (ld)N), sin(2 * M_PI / (ld)N));

		vector<plex> mvp(N);
		for (int i = 0; i < N; i++) {
			if (i < len(a)) {
				mvp[i].real(a[i]);
			}
			if (i < len(b)) {
				mvp[i].imag(b[i]);
			}
		}

		complex_convolution(mvp.data(), N, false);
		transform_2_convolutions(mvp.data(), N);
		complex_convolution(mvp.data(), N, true);


		vector<ll> final(N);
		for (int i = 0; i < N; i++) {
			final[i] = round(real(mvp[i]));	
		}

		return final;
	}

	template<class T>
	inline vector<T> multiply_high_precision(vector<ll> a, vector<ll> b) {
		int N = max(len(a), len(b));
		a.resize(N, 0);
		b.resize(N, 0);
		vector<ll> A = a;
		vector<ll> B = b;
		ll C = 0;
		f(i, N) {
			C = max(C, abs(a[i]));
			C = max(C, abs(b[i]));
		}
		C = sqrt(C);
		f(i, N) {
			A[i] /= C;
			B[i] /= C;
			a[i] %= C;
			b[i] %= C;
		}
		vector<ll> high = multiply(A, B);
		vector<ll> Ab = multiply(A, b);
		vector<ll> Ba = multiply(B, a);
		vector<ll> ab = multiply(a, b);
		vector<T> gl(len(high));

		T _C(C);

		f(i, len(gl)) {
			gl[i] = _C * _C * T(high[i]) + _C * (T(Ab[i]) + T(Ba[i])) + T(ab[i]);
		}
		return gl;
	}
};

========== Berleykamp ==========

const ll MOD = 1e9 + 7;
template<ll MOD>
struct Ring {
	ll value = 0;
	Ring() {}
	Ring(int _value) {
		value = _value;
		value = floor_mod(value, MOD);
	}
	Ring(ll _value) {
		value = _value;
		value = floor_mod(value, MOD);
	}
	Ring pow(ll p) const {
		if (p == 0) return 1;	
		if (p & 1) {
			return Ring(value).pow(p - 1) * value;
		} else {
			Ring sub = Ring(value).pow(p / 2);
			return sub * sub;
		}
	}
	Ring inv() const {
		return pow(MOD - 2);
	}
	void operator*=(const Ring<MOD> &b) {
		value *= b.value;
		value = floor_mod(value, MOD);
	}
	friend Ring operator*(Ring<MOD> a, const Ring<MOD> &b) {
		a *= b;
		return a;
	}
	void operator+=(const Ring<MOD> &b) {
		value += b.value;
		value = floor_mod(value, MOD);
	}
	friend Ring operator+(Ring a, const Ring &b) {
		a += b;
		return a;
	}
	void operator-=(const Ring<MOD> &b) {
		value -= b.value;
		value = floor_mod(value, MOD);
	}
	friend Ring operator-(Ring a, const Ring &b) {
		a -= b;
		return a;
	}
	void operator/=(const Ring<MOD> &b) {
		(*this) *= b.inv();	
	}
	friend Ring operator/(Ring a, const Ring &b) {
		a /= b;
		return a;
	}
	bool operator==(const Ring<MOD> &b) {
		return value == b.value;
	}
	friend void fast_print(const Ring<MOD> &b) {
		fast_print(b.value);
	}
};

typedef Ring<MOD> num;


template<class T>
struct Berleykamp {
	vector<T> v;
	vector<T> rec;

	Berleykamp(const vector<T> &_a) {
		v = _a;
		vector<T> cur = {1};
		vector<T> pref = {1};
		T dy = 1;
		for (int i = 0; i < len(v); i++) {
			T dx = 0;
			f(j, len(cur)) {
				dx += v[i - len(cur) + j + 1] * cur[j];
			}
			if (dx == (T)0) {
				pref.pb(0);
			} else {
				pref.pb(0);
				vector<T> _new = cur;
				while (len(_new) < len(pref)) {
					_new.insert(_new.begin(), 0);
				}
				f(j, len(pref)) {
					_new[len(_new) - len(pref) + j] -= pref[j] * (dx / dy);
				}
				pref = cur;
				cur = _new;
				dy = dx;
			}
		}
		rec = cur;
	}

	T interpolate(int n) {
		if (n < len(v)) return v[n];	
		T rez = 0;
		for (int i = 0; i < len(rec) - 1; i++) {
			rez -= interpolate(n - len(rec) + i + 1) * rec[i];
		}
		assert(len(v) == n);	
		v.pb(n);
		return v[n] = rez;
	}

	vector<T> mod(vector<T> a, vector<T> b) {
		while (!b.empty() && b.back() == 0) {
			b.pop_back();
		}
		while (len(a) >= len(b)) {
			while (!a.empty() && a.back() == 0) {
				a.pop_back();
			}
			if (len(a) < len(b)) return a;

			T factor = a.back() / b.back();

			f(i, len(b)) {
				a[len(a) - len(b) + i] -= b[i] * factor;
			}
		}
		return a;
	}

	vector<T> mul(vector<T> a, vector<T> b) {
		vector<T> c(len(a) + len(b));
		f(i, len(a)) {
			f(j, len(b)) {
				c[i + j] += a[i] * b[j];
			}
		}
		return c;
	}

	vector<T> fast_pow(vector<T> x, vector<T> M, int p) {
		if (p == 0) return {T(1)};
		if (p & 1) {
			return mod(mul(fast_pow(x, M, p - 1), x), M);
		} else {
			vector<T> sub = fast_pow(x, M, p / 2);
			return mod(mul(sub, sub), M);
		}
	}

	T interpolate__fast(int n) {
		vector<T> x = {0, 1};
		x = fast_pow(x, rec, n);
		T final = 0;
		for (int i = 0; i < len(x); i++) {
			final += x[i] * interpolate(i);
		}
		return final;
	}
};


========== HungarianDance ==========

struct Dance {
	int n, m;
	vector<vector<int>> v;
	vector<int> rez;
	vector<int> row, col;
	vector<bool> srow, scol;
	vector<int> min_value, min_pos;
	vector<pii> invoker;

	Dance(vector<vector<int>> _v) {
		v = _v;
		n = len(v);
		m = len(v[0]);

		row.resize(n, 0);
		col.resize(m, 0);
		rez.resize(m, -1);
	}

	int get(int i, int j) {
		return v[i][j] + row[i] + col[j];
	}

	pair<vector<int>, int> match() {
		f(cur, n) {
			min_value = vector<int>(m, 1e9);
			min_pos = vector<int>(m, -1);
			invoker = vector<pii>(n, mp(-1, -1));
			srow = vector<bool>(n, false);
			scol = vector<bool>(m, false);
			
			int next = cur;
			while (true) {
				srow[next] = true;
				f(j, m) {
					if (get(next, j) < min_value[j]) {
						min_value[j] = get(next, j);
						min_pos[j] = next;
					}
				}

				pii _min = mp(-1, -1);
				f(j, m) {
					if (scol[j]) continue;
					if (_min.x == -1 || get(_min.x, _min.y) > min_value[j]) {
						_min = mp(min_pos[j], j);
					}
				}

				assert(_min != mp(-1, -1));

				int d = get(_min.x, _min.y);

				f(i, n) {
					if (srow[i]) {
						row[i] -= d;
					}
				}
				f(j, m) {
					if (scol[j]) {
						col[j] += d;
					}
				}
				f(j, m) {
					min_value[j] -= d;
				}
				if (rez[_min.y] == -1) {
					int ind = _min.y;
					int p = _min.x;
					while (ind != -1) {
						rez[ind] = p;
						ind = invoker[p].y;
						p = invoker[p].x;
					}
					break;
				} else {
					scol[_min.y] = true;
					invoker[rez[_min.y]] = mp(_min.x, _min.y);
					next = rez[_min.y];
				}
			}
		}
		int total = 0;
		f(i, m) {
			total += v[rez[i]][i];
		}
		return mp(rez, total);
	}
};


========== Auto ==========

vector<int> suffix_array(const string &s) {
    int n = s.size(), N = max(n, 257);
    vector<int> sa(n), ra(n);
    for (int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for (int k = 0; k < n; k ? k <<= 1 : k++) {
        vector<int> nsa(sa), nra(n), cnt(N);
        for (int i = 0; i < n; ++i) nsa[i] -= k - (nsa[i] < k ? n : 0);
        for (int i = 0; i < n; ++i) cnt[ra[i]]++;
        for (int i = 1; i < N; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[ra[nsa[i]]]] = nsa[i];
        int r = 0;
        for (int i = 1; i < n; ++i) {
            if (ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if (ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        swap(ra, nra);
    }
    return sa;
}

int nodes = 0;

struct Auto {
	struct Node {
		map<char, Node*> go;
		int max_len = 0;
		Node *sufflink = NULL;
		int id = 0;

		Node() {
			id = nodes++;
		}
	};

	Node *clone(Node *node) {
		Node *cl = new Node();
		cl->go = node->go;
		cl->max_len = node->max_len;
		cl->sufflink = node->sufflink;
		return cl;
	}

	Node *root = new Node();
	Node *cur = NULL;

	Auto() {
		cur = root;
	}

	void add(char c) {
		Node *_new = new Node();
		_new->max_len = cur->max_len + 1;
		_new->sufflink = root;
		while (cur && !cur->go.count(c)) {
			cur->go[c] = _new;
			cur = cur->sufflink;
		}	
		if (cur) {
			if (cur->go[c]->max_len == cur->max_len + 1) {
				_new->sufflink = cur->go[c];
			} else {
				Node *q = cur->go[c];
				Node *p = clone(cur->go[c]);
				_new->sufflink = p;
				cur->go[c]->sufflink = p;
				p->max_len = cur->max_len + 1;

				while (cur) {
					if (cur->go[c] == q) {
						cur->go[c] = p;
						cur = cur->sufflink;
					} else {
						break;
					}
				}	
			}
		}
		cur = _new;
	}

	bool check(Node *node, string &s, int i) {
		if (i >= len(s)) return true;
		if (!node->go.count(s[i])) return false;
		return check(node->go[s[i]], s, i + 1);
	}
};

========== z_function ==========

vector<int> z_function (string s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}


========== prefix_function ==========

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

========== BipolarDisorder ==========

struct BipolarDisorder {
	int n;
	vector<vector<int>> g;
	vector<pii> edges;
	vector<int> uptime;
	vector<int> tin;
	vector<bool> used;
	vector<int> buff;
	vector<bool> pick;
	vector<int> order;

	vector<int> at;

	int timer = 0;

	void init_time(int v) {
		used[v] = true;
		at[timer] = v; 
		tin[v] = uptime[v] = timer++;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			init_time(sub);
		}
	}

	void check(int v, int _forb) {
		used[v] = true;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			if (sub == _forb) continue;
			check(sub, _forb);
		}
	}
	bool is_critical_slow(int v) {
		used = vector<bool>(n, false);
		int cnt = 0;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			cnt++;
			check(sub, v);
		}
		return cnt >= 2;
	}
	vector<bool> crit;
	void go(int v, int _p) {
		used[v] = true;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (used[sub]) {
				uptime[v] = min(uptime[v], tin[sub]);
			} else {
				go(sub, v);
				uptime[v] = min(uptime[v], uptime[sub]);
				if (uptime[sub] >= tin[v]) {
					crit[v] = true;
				}
			}
		}
	}

	void update_critical() {
		tin = vector<int>(n, 0);
		uptime = vector<int>(n, 0);
		used = vector<bool>(n, false);
		init_time(0);
		crit = vector<bool>(n, false);
		used = vector<bool>(n, false);
		go(0, -1);
		crit[0] = is_critical_slow(0);
	}

	int A = -1;

	struct Node {
		Node *l = NULL, *r = NULL, *pref = NULL;
		int prior;
		int size = 1;

		Node() {
			prior = rng();
		} 
	};

	int get_size(Node *node) {
		return node ? node->size : 0;
	}

	void update(Node *node) {
		node->size = get_size(node->l) + get_size(node->r) + 1;
	}

	Node *merge(Node *l, Node *r) {
		if (!l) return r;
		if (!r) return l;
		if (l->prior > r->prior) {
			l->r = merge(l->r, r);
			l->r->pref = l;
			update(l);
			return l;
		} else {
			r->l = merge(l, r->l);
			r->l->pref = r;
			update(r);
			return r;
		}
	}

	pair<Node*, Node*> split(Node *node, int k) {
		if (!node) return mp(node, node);
		if (get_size(node->l) >= k) {
			if (node->l) node->l->pref = NULL;
			auto t = split(node->l, k);
			node->l = NULL;
			update(node);
			return mp(t.x, merge(t.y, node));
		} else {
			if (node->r) node->r->pref = NULL;
			auto t = split(node->r, k - get_size(node->l) - 1);
			node->r = NULL;
			update(node);
			return mp(merge(node, t.x), t.y);
		}
	}

	int get_id(Node *node) {
		int id = get_size(node->l);
		while (node->pref) {
			if (node->pref->r == node) {
				id += 1 + get_size(node->pref->l);
			}
			node = node->pref;
		}
		return id;
	}

	Node *cart = NULL;

	vector<Node*> pres;

	void dfs(int v, int _p, int end) {
		buff.pb(v);
		if (v == end) {
			for (int x : buff) {
				pres[x] = new Node();
				cart = merge(cart, pres[x]);
				pick[x] = true;
			}
		}
		at[timer] = v;
		uptime[v] = tin[v] = timer++;
		used[v] = true;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (used[sub]) {
				uptime[v] = min(uptime[v], tin[sub]);
			} else {
				dfs(sub, v, end);
				uptime[v] = min(uptime[v], uptime[sub]);
			}
		}
		buff.pop_back();
	}

	void echo(int v, int _p) {
		used[v] = true;

		if (!pick[v]) {
			buff.pb(v);
		}

		int B = at[uptime[v]];
		if (!buff.empty() && pick[B] && B != A) {
			int itA = get_id(pres[A]);
			int itB = get_id(pres[B]);
			if (itA < itB) {
				auto t = split(cart, itA + 1);
				for (int x : buff) {
					pres[x] = new Node();
					t.x = merge(t.x, pres[x]);
				}
				cart = merge(t.x, t.y);
			} else {
				reverse(buff.begin(), buff.end());
				auto t = split(cart, itB + 1);
				for (int x : buff) {
					pres[x] = new Node();	
					t.x = merge(t.x, pres[x]);
				}
				cart = merge(t.x, t.y);
			}
			for (int x : buff) {
				pick[x] = true;
			}
			buff.clear();
		}

		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (used[sub]) continue;
			if (pick[v]) {
				A = v;
			}
			echo(sub, v);
		}
	}

	set<int> finded_crit;
	void _index(int v) {
		used[v] = true;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			if (crit[sub]) {
				finded_crit.insert(sub);
			} else {
				_index(sub);
			}
		}
	}

	void init(int _n) {
		n = _n;
		g.resize(n);
		at.resize(2 * n);
		uptime.resize(n);
		tin.resize(n);
		timer = 0;
	}

	void add_edge(int a, int b) {
		g[a].pb(b);
		g[b].pb(a);
		edges.emplace_back(a, b);
	}

	vector<int> get_priors() {
		{
			used = vector<bool>(n, false);
			update_critical();
			used = vector<bool>(n, false);
			vector<int> pos;
			f(i, n) {
				if (crit[i]) continue;
				if (!used[i]) {
					if (len(g[i]) == 1) {
						pos.pb(i);
						used[i] = true;
					} else {
						finded_crit.clear();
						_index(i);
						if (len(finded_crit) <= 1) {
							pos.pb(i);
						}
					}
				}
			}
			if (len(pos) <= 1) {
				pos.pb(n - 1);
			}
			if (len(pos) != 2) {
				return {};
			}

			int start = pos[0];
			int end = pos[1];
			shuffle(pos.begin(), pos.end(), rng);

			used = vector<bool>(n, false);
			pick = vector<bool>(n, false);
			pres.resize(n, NULL);
			timer = 0;
			dfs(start, -1, end);
			buff.clear();
			used = vector<bool>(n, false);
			echo(start, -1);
			vector<int> p(n);
			f(i, n) {
				if (pres[i]) {
					p[i] = get_id(pres[i]);
				} else {
					return {};
				}
			}
			vector<int> in(n), out(n);
			for (pii edge : edges) {
				if (p[edge.x] > p[edge.y]) {
					swap(edge.x, edge.y);
				}
				in[edge.y]++;
				out[edge.x]++;
			}
			bool fail = false;
			f(i, n) {
				if (i != start && in[i] == 0) {
					fail = true;
				}
				if (i != end && out[i] == 0) {
					fail = true;
				}
			}
			if (!fail) {
				return p;
			} else {
				return {};
			}
		}
	}
};


========== MaxMatch ==========

struct MaxMatch {
	vector<vector<int>> g;
	vector<int> match;
	vector<bool> used;
	vector<int> p;

	MaxMatch(int n) {
		g.resize(n);
		match.resize(n, -1);
		p.resize(n);
		f(i, n) {
			p[i] = i;
		}
	}

	void add_edge(int a, int b) {
		g[a].pb(b);
		g[b].pb(a);
	}

	bool dfs(int v) {
		used[v] = true;
		shuffle(g[v].begin(), g[v].end(), rng);
		for (int sub : g[v]) {
			if (match[sub] == -1) {
				match[v] = sub;
				match[sub] = v;
				return true;
			}
		}
		for (int sub : g[v]) {
			int __t = match[sub];
			assert(__t != -1);
			if (used[__t]) continue;
			match[__t] = -1;
			match[sub] = v;
			match[v] = sub;
			if (dfs(__t)) {
				return true;
			} else {
				match[sub] = __t;	
				match[__t] = sub;
				match[v] = -1;
			}
		}
		return false;
	}

	void upgrade() {
		shuffle(p.begin(), p.end(), rng);
		used = vector<bool>(len(g), false);
		for (int i : p) {
			if (match[i] == -1 && !used[i]) {
				dfs(i);
			}
		}
	}

	vector<pii> edges() {
		vector<pii> rez;
		for (int i = 0; i < len(g); i++) {
			if (match[i] != -1 && i < match[i]) {
				rez.emplace_back(i, match[i]);
			}
		}
		return rez;
	}
};

========== MaxMatchWithoutEachVertex ==========

struct DTree {
	int n;
	vector<int> parent, label, real;
	int cnt = 0;
	vector<vector<int>> edge, succ, pred;
	vector<int> semi, idom, ancestor, best;
	vector<deque<int>> bucket;

	vector<vector<int>> tree;

	void add_edge(int a, int b) {
		edge[a + 1].pb(b + 1);
	}

	DTree(int _n) {
		n = _n;
		parent.resize(n + 1);
		label.resize(n + 1);
		real.resize(n + 1);
		tree.resize(n + 1);
		edge.resize(n + 1);
		succ.resize(n + 1);
		pred.resize(n + 1);
		semi.resize(n + 1);
		idom.resize(n + 1);
		ancestor.resize(n + 1);
		best.resize(n + 1);
		bucket.resize(n + 1);
	}

	void dfs(int u) {
		label[u] = ++cnt; real[cnt] = u;
		for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
			int v = *it;
			if (v == parent[u] || label[v] != -1) continue;
			parent[v] = u;
			dfs(v);
		}
	}

	void link(int v, int w) {
		ancestor[w] = v;
	}

	void compress(int v) {
		int a = ancestor[v];
		if (ancestor[a] == 0) return;
		compress(a);
		if (semi[best[v]] > semi[best[a]]) best[v] = best[a];
		ancestor[v] = ancestor[a];
	}

	int eval(int v) {
		if (ancestor[v] == 0) return v;
		compress(v);
		return best[v];
	}

	void dominator() { // clear succ & pred, let cnt = 0 first
		for (int i = 1; i <= n; ++i) label[i] = -1;
		dfs(n); // n is root
		for (int u = 1; u <= n; ++u) {
			for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
				int v = *it;
				if (label[u] != -1 && label[v] != -1) {
					succ[label[u]].push_back(label[v]);
					pred[label[v]].push_back(label[u]);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			semi[i] = best[i] = i;
			idom[i] = ancestor[i] = 0;
			bucket[i].clear();
		}
		for (int w = cnt; w >= 2; --w) {
			int p = label[parent[real[w]]];
			for (vector<int>::iterator it = pred[w].begin(); it != pred[w].end(); ++it) {
				int v = *it;
				int u = eval(v);
				if (semi[w] > semi[u]) semi[w] = semi[u];
			}
			bucket[semi[w]].push_back(w);
			link(p, w);
			while (!bucket[p].empty()) {
				int v = bucket[p].front();
				bucket[p].pop_front();
				int u = eval(v);
				idom[v] = (semi[u] < p ? u : p);
			}
		}
		for (int w = 2; w <= cnt; ++w) {
			if (idom[w] != semi[w]) idom[w] = idom[idom[w]];
		}
		idom[1] = 0;
		for (int i = 1; i <= cnt; ++i) {
			int u = real[idom[i]], v = real[i];
			// u is immediate dominator of v (i == 1?)
			// print u - 1, v - 1;
		}
	}
};

int n, m;

vector<vector<int>> g;
vector<bool> used;
vector<bool> R;
vector<int> rez;

bool ktun(int v) {
	used[v] = true;
	for (int sub : g[v]) {
		if (rez[sub] == -1) {
			rez[sub] = v;
			return true;
		}
	}
	for (int sub : g[v]) {
		if (used[rez[sub]]) continue;
		R[sub] = true;
		if (ktun(rez[sub])) {
			rez[sub] = v;
			return true;
		}
	}
	return false;
}

pair<int, vector<bool>> match(vector<pii> edges) {
	g.clear();
	R.clear();
	rez.clear();
	rez.resize(n, -1);
	g.resize(n);
	R.resize(n);
	for (pii e : edges) {
		g[e.x].pb(e.y);
	}
	used = vector<bool>(n, false);
	f(i, n) {
		if (ktun(i)) {
			used = vector<bool>(n, false);		
		}
	}
	DTree tree(2 * n + 1);	
	f(i, n) {
		for (int sub : g[i]) {
			if (rez[sub] == i) {
				tree.add_edge(sub + n, i);
			} else {
				tree.add_edge(i, sub + n);	
			}
		}
	}
	vector<bool> L(n);
	f(i, n) {
		if (rez[i] != -1) {
			L[rez[i]] = true;
		}
	}
	R = vector<bool>(n, false);
	used = vector<bool>(n, false);	
	f(i, n) {
		if (!L[i]) {
			tree.add_edge(2 * n, i);
			ktun(i);
		}
	}
	tree.dominator();
	vector<bool> can_del(n, false);
	f(i, n) {
		if (!L[i]) {
			can_del[i] = true;
		}
	}
	f(i, n) {
		if (rez[i] == -1) {
		} else {
			if (R[i]) {
				bool found = false;	
				int j = i + n;
				while (j != -1) {
					if (j == rez[i]) {
						found = true;
					}
					j = tree.parent[j + 1] - 1;
				}
				can_del[rez[i]] = !found;
			}
		}
	}
	int cnt = 0;
	f(i, n) {
		cnt += (rez[i] == -1);
	}
	return mp(cnt, can_del);
}

signed main(signed argc, char *argv[]) {
	scan n, m;
	vector<pii> edges, rev;
	f(i, m) {
		int a, b;
		scan a, b;
		a--;b--;
		edges.emplace_back(a, b);
		rev.emplace_back(b, a);
	}
	auto A = match(edges);
	auto B = match(rev);
	int y = min(A.x, B.x);
	vector<int> free;
	f(i, n) {
		if (A.y[i] || B.y[i]) {
			free.pb(i + 1);
		}
	}
	if (y - 1 == 0) {
		print 0;
	} else {
		print y - 1;
		print free;
	}
}


========== interpol ==========

template<class T>
vector<T> interpol(const vector<pair<T, T>> &pts) {
	if (pts.empty()) return {};
	vector<T> holy;
	vector<T> zero = {1};
	auto calc = [](vector<T> &poly, const T &x) {
		T s = 0;
		T p = 1;
		f(j, len(poly)) {
			s += poly[j] * p;
			p *= x;
		}
		return s;
	};
	holy.emplace_back(pts[0].y);
	for (int i = 1; i < len(pts); i++) {
		zero.insert(zero.begin(), 0);
		f(j, len(zero) - 1) {
			zero[j] -= zero[j + 1] * pts[i - 1].x;
		}
		T sub = pts[i].y - calc(holy, pts[i].x);
		T coef = sub / calc(zero, pts[i].x);
		while (len(holy) < len(zero)) {
			holy.pb(0);
		}
		for (int j = 0; j < len(zero); j++) {
			holy[j] += zero[j] * coef;
		}
	}
	return holy;
}

========== Bridges ==========

const int MAXN = ...;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v])
				IS_BRIDGE(v,to);
		}
	}
}
 
void find_bridges() {
	timer = 0;
	for (int i=0; i<n; ++i)
		used[i] = false;
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
}

========== CriticalPoints ==========

vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		IS_CUTPOINT(v);
}
 
int main() {
	int n;
	... чтение n и g ...
 
	timer = 0;
	for (int i=0; i<n; ++i)
		used[i] = false;
	dfs (0);
}

========== determinant ==========

template<class T>
T det(vector<vector<T>> v) {
	int n = len(v);
	T d = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[j][i] != T(0)) {
				swap(v[j], v[i]);
				d *= -1;
				break;
			}
		}
		if (v[i][i] == 0) return (T)0;
		d *= v[i][i];
		for (int j = i + 1; j < n; j++) {
			num coef = v[j][i] / v[i][i];
			for (int k = i; k < n; k++) {
				v[j][k] -= (v[i][k] * coef);
			}
		}
	}
	return d;
}
