struct CommandY {
	using T = pii;
	const int BAR = 1e9;
	T compose(T f1, T f2) {
		// min(f1.x, min(f2.x, x + f2.y) + f1.y)
		// == min(f1.x, min(f2.x + f1.y, x + f2.y + f1.y))
		// == min(f1.x, f2.x + f1.y, x + f2.y + f1.y)
		return mp(min(f1.x, f2.x + f1.y), f2.y + f1.y);
	}

	T smallest(T f1, T f2) {
		return mp(min(f1.x, f2.x), min(f1.y, f2.y));
	}

	vector<T> F, H;
	int n;

	CommandY() {}
	CommandY(int _n) {
		n = _n;
		F.resize(2 * n);
		H.resize(2 * n);
	}

	void push(int i, int tl, int tr) {
		if (tl + 1 != tr) {
			int m = (tl + tr) / 2;
			H[i + 1] = smallest(H[i + 1], compose(H[i], F[i + 1]));
			H[i + (m - tl) * 2] = smallest(H[i + (m - tl) * 2], compose(H[i], F[i + (m - tl) * 2]));
			F[i + 1] = compose(F[i], F[i + 1]);
			F[i + (m - tl) * 2] = compose(F[i], F[i + (m - tl) * 2]);

			F[i] = mp(BAR, 0);
			H[i] = mp(BAR, 0);
		}
	}

	void update(int i, int tl, int tr, int ql, int qr, T func) {
		if (qr <= tl || tr <= ql) return;
		if (ql <= tl && tr <= qr) {
			H[i] = smallest(H[i], compose(func, F[i]));
			F[i] = compose(func, F[i]);
		} else {
			push(i, tl, tr);
			int m = (tl + tr) / 2;
			update(i + 1, tl, m, ql, qr, func);
			update(i + (m - tl) * 2, m, tr, ql, qr, func);
		}	
	}
	void update(int ql, int qr, T func) { update(0, 0, n, ql, qr, func); }

	void extract_history(int i, int tl, int tr, vector<T> &vals) {
		if (tl + 1 == tr) {
			vals.emplace_back(H[i]);
		} else {
			push(i, tl, tr);
			int m = (tl + tr) / 2;
			extract_history(i + 1, tl, m, vals);
			extract_history(i + (m - tl) * 2, m, tr, vals);
		}
	}

	vector<T> extract_history() {
		vector<T> vals;
		extract_history(0, 0, n, vals);
		return vals;
	}
};