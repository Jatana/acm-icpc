template<class T>
struct Fen {
	vector<T> v;
	Fen() {}
	Fen(int n) {
		v.resize(n);
	}
	void inc(int i, const T &d) {
		assert(i >= 0);
		for (; i < le(v); i = (i | (i + 1)))
			v[i] += d;
	}
	T get(int i) {
		assert(i < le(v));
		T r = 0;
		for (; i >= 0; i = (i & (i + 1)) - 1)
			r += v[i];
		return r;
	}
	T get(const int &l, const int &r) {
		return get(r - 1) - get(l - 1);
	}
};