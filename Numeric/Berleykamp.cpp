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
