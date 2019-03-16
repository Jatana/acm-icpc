template<class Value, class Mod, class Magic, class ApplyMod, class MergeMods>
struct TreeSegment {
	struct Node {
		bool have_mod = false;
		Value value;
		Mod mod;
	};	

	Magic magic;
	ApplyMod apply_mod;
	MergeMods merge_mods;

	vector<Node> S;
	int n;

	bool __intersects(const int &tl, const int &tr, const int &ql, const int &qr) {
		return !(tr <= ql || qr <= tl);
	}

	Value __get_value(const int &i, const int &tl, const int &tr) {
		if (!S[i].have_mod) return S[i].value;
		return apply_mod(S[i].value, S[i].mod, tl, tr);
	}

	void __recalc_value(const int &i, const int &tl, const int &tr) {
		if (tl + 1 != tr) {
			int mid = (tl + tr) / 2;
			S[i].value = magic(
				__get_value(i + 1, tl, mid),
				__get_value(i + (mid - tl) * 2, mid, tr)
			);
		}
	}

	void __add_mod(const int &i, const int &tl, const int &tr, const Mod &sub) {
		if (S[i].have_mod) {
			S[i].mod = merge_mods(S[i].mod, sub, tl, tr);
		} else {
			S[i].mod = sub;
			S[i].have_mod = true;
		}
	}

	void __push(const int &i, const int &tl, const int &tr) {
		if (S[i].have_mod) {
			S[i].value = apply_mod(S[i].value, S[i].mod, tl, tr);
			if (tl + 1 != tr) {
				int mid = (tl + tr) / 2;
				__add_mod(i + 1, tl, mid, S[i].mod);
				__add_mod(i + (mid - tl) * 2, mid, tr, S[i].mod);
			}
			S[i].have_mod = false;
		}
	}

	void init(const int &i, const int &tl, const int &tr, const vector<Value> &src) {
		if (tl + 1 == tr) {
			S[i].value = src[tl];
		} else {
			int mid = (tl + tr) / 2;
			init(i + 1, tl, mid, src);
			init(i + (mid - tl) * 2, mid, tr, src);
			__recalc_value(i, tl, tr);
		}
	}

	Value __query(const int &i, const int &tl, const int &tr,
			const int &ql, const int &qr) {
		__push(i, tl, tr);
		if (ql <= tl && tr <= qr) {
			return S[i].value;
		} else {
			int mid = (tl + tr) / 2;
			if (__intersects(tl, mid, ql, qr) && __intersects(mid, tr, ql, qr)) {
				return magic(
					__query(i + 1, tl, mid, ql, qr),
					__query(i + (mid - tl) * 2, mid, tr, ql, qr)
				);
			} else if (__intersects(tl, mid, ql, qr)) {
				return __query(i + 1, tl, mid, ql, qr);
			} else {
				return __query(i + (mid - tl) * 2, mid, tr, ql, qr);
			}
		}
	}

	void __change(const int &i, const int &tl, const int &tr,
			const int &j, const Value &_new) {
		__push(i, tl, tr);
		if (tl + 1 == tr) {
			S[i].value = _new;
		} else {
			int mid = (tl + tr) / 2;
			if (j < mid) {
				__change(i + 1, tl, mid, j, _new);
			} else {
				__change(i + (mid - tl) * 2, mid, tr, j, _new);
			}
			__recalc_value(i, tl, tr);
		}
	}

	void __update(const int &i, const int &tl, const int &tr,
			const int &ql, const int &qr, const Mod &mod) {
		__push(i, tl, tr);
		if (ql <= tl && tr <= qr) {
			__add_mod(i, tl, tr, mod);
		} else {
			int mid = (tl + tr) / 2;
			if (__intersects(tl, mid, ql, qr)) {
				__update(i + 1, tl, mid, ql, qr, mod);	
			}
			if (__intersects(mid, tr, ql, qr)) {
				__update(i + (mid - tl) * 2, mid, tr, ql, qr, mod);
			}
			__recalc_value(i, tl, tr);
		}
	}

	template<class Check>
	pair<int, Value> __find_right(const int &i, const int &tl, const int &tr,
			const int &L, const Check &checker, const Value &pref) {
		__push(i, tl, tr);
		if (tr <= L) return mp(-1, pref);
		if (tl + 1 == tr) {
			Value _this = magic(pref, __get_value(i, tl, tr));
			if (checker(_this)) {
				return mp(tl, _this);
			} else {
				return mp(-1, _this);
			}
		} else {
			int mid = (tl + tr) / 2;
			if (L <= tl) {
				Value _left = magic(pref, __get_value(i + 1, tl, mid));
				if (checker(_left)) {
					return __find_right(i + 1, tl, mid, L, checker, pref);
				} else {
					return __find_right(i + (mid - tl) * 2, mid, tr, L, checker, _left);
				}
			} else {
				auto t = __find_right(i + 1, tl, mid, L, checker, pref);
				if (t.first != -1) return t;
				return __find_right(i + (mid - tl) * 2, mid, tr, L, checker, t.second);
			}	
		}
	}

	template<class Check>
	pair<int, Value> __find_left(const int &i, const int &tl, const int &tr,
			const int &R, const Check &checker, const Value &pref) {
		__push(i, tl, tr);
		if (R < tl) return mp(-1, pref);
		if (tl + 1 == tr) {
			Value _this = magic(pref, __get_value(i, tl, tr));
			if (checker(_this)) {
				return mp(tl, _this);
			} else {
				return mp(-1, _this);
			}
		} else {
			int mid = (tl + tr) / 2;
			if (tr <= R + 1) {
				Value _right = magic(pref, __get_value(S[i].r, mid, tr));
				if (checker(_right)) {
					return __find_left(S[i].r, mid, tr, R, checker, pref);
				} else {
					return __find_left(S[i].l, tl, mid, R, checker, _right);
				}
			} else {
				auto t = __find_left(S[i].r, mid, tr, R, checker, pref);
				if (t.first != -1) return t;
				return __find_left(S[i].l, tl, mid, R, checker, t.second);
			}	
		}
	}

	void init(const vector<Value> &src) {
		n = len(src);
		S.resize(2 * n + 1);
		init(0, 0, len(src), src);
	}
	
	TreeSegment(const int &n, const Value &def,
			Magic _magic, ApplyMod _apply_mod, MergeMods _merge_mods, Mod)
			: magic(_magic), apply_mod(_apply_mod), merge_mods(_merge_mods) {
		init(vector<Value>(n, def));
	}

	TreeSegment(const vector<Value> &def,
			Magic _magic, ApplyMod _apply_mod, MergeMods _merge_mods, Mod) 
			: magic(_magic), apply_mod(_apply_mod), merge_mods(_merge_mods) {
		init(def);
	}

	Value query(const int &ql, const int &qr) {
		assert(ql < qr);
		return __query(0, 0, n, ql, qr);
	}

	void change(const int &i, const Value &value) {
		assert(0 <= i && i < n);
		__change(0, 0, n, i, value);
	}

	void update(const int &ql, const int &qr, const Mod &mod) {
		__update(0, 0, n, ql, qr, mod);
	}
	
	template<class Check>
	int find_right(const int &L, const Check &checker, const Value &start) {
		if (checker(start)) return L - 1;
		int rez = __find_right(0, 0, n, L, checker, start).first;
		return (rez == -1) ? n : rez;
	}

	template<class Check>
	int find_left(const int &R, const Check &checker, const Value &start) {
		if (checker(start)) return R + 1;
		int rez = __find_left(0, 0, n, R, checker, start).first;
		return (rez == -1) ? -1 : rez;
	}
};