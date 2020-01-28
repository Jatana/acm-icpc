struct SATSolver {
	vector<vector<int>> g, reg;

	void add(int a, int b) {
		g[a ^ 1].pb(b);
		g[b ^ 1].pb(a);
		// print a ^ 1, b;
		// print b ^ 1, a;
	}

	vector<int> topsort;
	vector<bool> used;
	vector<int> at;

	void dfs_top(int v) {
		used[v] = true;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			dfs_top(sub);
		}
		topsort.pb(v);
	}

	void add_comp(int v, int comp_id) {
		used[v] = true;
		at[v] = comp_id;
		for (int sub : reg[v]) {
			if (used[sub]) continue;
			add_comp(sub, comp_id);
		}
	}

	void solve() {
		f(i, len(g)) {
			for (int sub : g[i]) {
				reg[sub].pb(i);
			}
		}
		used = vector<bool>(len(g), false);
		f(i, len(g)) {
			if (!used[i]) {
				dfs_top(i);
			}
		}
		reverse(topsort.begin(), topsort.end());
		at.resize(len(g));
		used = vector<bool>(len(g), false);
		int cid = 0;
		for (int v : topsort) {
			if (used[v]) continue;
			add_comp(v, cid++);
		}
	}

	bool impossible() {
		for (int i = 0; i < len(g); i++) {
			if (at[i] == at[i ^ 1]) return true;
		}
		return false;
	}

	SATSolver(int n) {
		g.resize(2 * n);
		reg.resize(2 * n);
	}
};