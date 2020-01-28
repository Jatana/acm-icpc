/*
	- DO NOT FORGET TO USE OPERATOR NEW!
*/
struct Matroid {
	int n;
	/*
		- n is the size of base
	*/
	Matroid(int _n) : n(_n) {}
	/*
		- Set working set as $X$
	*/
	virtual void build(const vector<int> &) {}
	/*
		- Should return any cycle that includes $i$ or empty set
	*/
	virtual vector<int> FindCircuit(const int &) {
		throw nullptr;
	}
};

/*
	- DO NOT FORGET TO USE OPERATOR NEW!
*/
struct ForestMatroid : public Matroid {
	int nvert;
	vector<pii> edges;
	vector<vector<pii>> g;
	/*
		- m is the size of base
	*/ 
	ForestMatroid(int _n, int m, vector<pii> _edges) : Matroid(m), nvert(_n), edges(_edges) {
		g.resize(nvert);
		for (int y = 0; y < m; y++) {
			g[edges[y].x].emplace_back(edges[y].y, y);
			g[edges[y].y].emplace_back(edges[y].x, y);
		}
	}
	virtual ~ForestMatroid() {}
	vector<bool> isx;
	vector<bool> used;
	vector<pii> pref;
	vector<int> depth;
	vector<int> comp;
	void dfs(int v, int _pid, int dom) {
		used[v] = true;
		comp[v] = dom;
		for (pii e : g[v]) {
			if (!isx[e.y]) continue;
			if (e.y == _pid) continue;
			if (used[e.x]) continue;
			pref[e.x] = mp(v, e.y);
			depth[e.x] = depth[v] + 1;
			dfs(e.x, e.y, dom);
		}
	}
	/*
		- Set working set as $X$
	*/
	void build(const vector<int> &X) override {
		used = vector<bool>(nvert, false);
		isx = vector<bool>(n, false);
		pref = vector<pii>(nvert, mp(-1, -1));
		depth = vector<int>(nvert, 0);
		comp = vector<int>(nvert, -1);
		for (int y : X) {
			isx[y] = true;
		}
		for (int i = 0; i < nvert; i++) {
			if (used[i]) continue;
			dfs(i, -1, i);
		}
	}
	/*
		- Should return any cycle that include $i$ or empty set
	*/
	vector<int> FindCircuit(const int &i) override {
		int a = edges[i].x, b = edges[i].y;	
		if (comp[a] == -1 || comp[b] == -1) return {};
		if (comp[a] != comp[b]) return {};
		vector<int> elems;
		while (a != b) {
			if (depth[a] < depth[b]) swap(a, b);
			elems.pb(pref[a].y);
			a = pref[a].x;
		}
		return elems;
	}
};

/*
	- The matroid intersection works as fast as possible
	- Maintains the optimal base after each iteration
*/
vector<int> IntersectMatroids(Matroid *A, Matroid *B, vector<int> W) {
	assert(A->n == B->n);
	const int n = A->n;
	vector<vector<pii>> graph;
	vector<int> X;
	while (true) {
		vector<bool> is_x(n, false), is_a(n, false), is_b(n, false);
		for (int y : X) is_x[y] = true;
		graph.clear();
		graph.resize(2 * n);
		deque<int> Q;
		vector<ll> dist(2 * n, 1e18), prv(2 * n, -1);
		A->build(X);
		B->build(X);
		for (int y = 0; y < n; y++) {
			if (is_x[y]) continue;
			auto circ_a = A->FindCircuit(y);
			if (circ_a.empty()) {
				is_a[y] = true; Q.push_back(y + n); dist[y + n] = W[y];
			} else {
				for (int x : circ_a)
					if (x != y) {
						graph[x].emplace_back(y + n, W[y]);
					}
			}
			auto circ_b = B->FindCircuit(y);
			if (circ_b.empty()) {
				is_b[y] = true;
			} else {
				for (int x : circ_b)
					if (x != y) {
						graph[y + n].emplace_back(x, -W[x]);
					}
			}
		}
		{
			while (!Q.empty()) {
				int v = Q.front(); Q.pop_front();
				for (pii e : graph[v]) {
					if (dist[e.x] > dist[v] + e.y) {
						dist[e.x] = dist[v] + e.y;
						prv[e.x] = v; Q.push_back(e.x);
					}
				}
			}
		}
		int dest = -1;
		for (int i = 0; i < n; i++) {
			if (is_b[i] && dist[i + n] < 1e18 && (dest == -1 || dist[dest + n] > dist[i + n])) {
				dest = i;
			}
		}
		if (dest == -1) break;
		dest += n;
		while (dest != -1) {
			const int p = dest % n;
			is_x[p] = !is_x[p]; dest = prv[dest];
		}
		assert(count(is_x.begin(), is_x.end(), true) == len(X) + 1);
		X.clear();
		for (int i = 0; i < n; i++) {
			if (is_x[i]) X.pb(i);
		}
		// X contains optimal pick
	}
	return X;
}

