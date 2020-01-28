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