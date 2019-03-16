vector<int> equal_prefix(const string &s, const vector<int> &pr) {
	ll MOD1 = 1e9 + 7;
	ll MOD2 = 1e9 + 9;
	ll base1 = 1009;
	ll base2 = 53;
	vector<ll> h1(len(s));
	vector<ll> h2(len(s));
	vector<ll> pow1(len(s) + 1, 1);
	vector<ll> pow2(len(s) + 1, 1);
	for (int i = 1; i < len(s) + 1; i++) {
		pow1[i] = (pow1[i - 1] * base1) % MOD1;
		pow2[i] = (pow2[i - 1] * base2) % MOD2;
	}
	h1[0] = s[0];
	h2[0] = s[0];
	for (int i = 1; i < len(s); i++) {
		h1[i] = (h1[i - 1] * base1 + s[i]) % MOD1;
		h2[i] = (h2[i - 1] * base2 + s[i]) % MOD2;
	}
	auto get_hash = [](const vector<ll> &h, const vector<ll> &pow, const ll &MOD,
			const int &l, const int &r) {
		ll rez = h[r - 1];
		if (l > 0) rez -= h[l - 1] * pow[r - l];
		return floor_mod(rez, MOD);
	};
	vector<int> eq;
	f(i, len(pr) - 1) {
		int l = 0;
		int r = min(len(s) - pr[i], len(s) - pr[i + 1]) + 1;
		while (r - l > 1) {
			int m = (l + r) / 2;
			if (get_hash(h1, pow1, MOD1, pr[i], pr[i] + m)
					== get_hash(h1, pow1, MOD1, pr[i + 1], pr[i + 1] + m)
				&& get_hash(h2, pow2, MOD2, pr[i], pr[i] + m)
					== get_hash(h2, pow2, MOD2, pr[i + 1], pr[i + 1] + m)) {
				l = m;
			} else {
				r = m;
			}
		}
		eq.pb(l);
	}
	return eq;
}
