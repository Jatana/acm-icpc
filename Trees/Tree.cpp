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