pii operator-(pii a, pii b) {
	return mp(a.x - b.x, a.y - b.y);
}

int operator^(pii a, pii b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(pii a, pii b) {
	return a.x * b.x + a.y * b.y;
}

struct Liner {
	vector<pii> st;
	Liner(vector<pii> lines) {
		sort(lines.rbegin(), lines.rend());
		for (pii l : lines) {
			while (len(st) >= 2) {
				pii base = st[len(st) - 2];
				pii sub = st.back();
				if (((l - base) ^ (sub - base)) >= 0) {
					st.pop_back();
				} else break;
			}
			st.pb(l);
		}
	}
	int query(int x) {
		int l = 0;
		int r = len(st) - 1;
		while (r - l > 1) {
			int m = (l + r) / 2;
			if ((mp(-1, x) ^ (st[m] - st[m - 1])) >= 0) {
				r = m;
			} else {
				l = m;
			}
		}
		int final = (st[r] * mp(x, 1));
		if (r - 1 >= 0) {
			final = max(final, st[r - 1] * mp(x, 1));
		}
		return final;
	}
};
