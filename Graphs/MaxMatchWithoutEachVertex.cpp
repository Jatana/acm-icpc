struct DTree {
	int n;
	vector<int> parent, label, real;
	int cnt = 0;
	vector<vector<int>> edge, succ, pred;
	vector<int> semi, idom, ancestor, best;
	vector<deque<int>> bucket;

	vector<vector<int>> tree;

	void add_edge(int a, int b) {
		edge[a + 1].pb(b + 1);
	}

	DTree(int _n) {
		n = _n;
		parent.resize(n + 1);
		label.resize(n + 1);
		real.resize(n + 1);
		tree.resize(n + 1);
		edge.resize(n + 1);
		succ.resize(n + 1);
		pred.resize(n + 1);
		semi.resize(n + 1);
		idom.resize(n + 1);
		ancestor.resize(n + 1);
		best.resize(n + 1);
		bucket.resize(n + 1);
	}

	void dfs(int u) {
		label[u] = ++cnt; real[cnt] = u;
		for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
			int v = *it;
			if (v == parent[u] || label[v] != -1) continue;
			parent[v] = u;
			dfs(v);
		}
	}

	void link(int v, int w) {
		ancestor[w] = v;
	}

	void compress(int v) {
		int a = ancestor[v];
		if (ancestor[a] == 0) return;
		compress(a);
		if (semi[best[v]] > semi[best[a]]) best[v] = best[a];
		ancestor[v] = ancestor[a];
	}

	int eval(int v) {
		if (ancestor[v] == 0) return v;
		compress(v);
		return best[v];
	}

	void dominator() { // clear succ & pred, let cnt = 0 first
		for (int i = 1; i <= n; ++i) label[i] = -1;
		dfs(n); // n is root
		for (int u = 1; u <= n; ++u) {
			for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
				int v = *it;
				if (label[u] != -1 && label[v] != -1) {
					succ[label[u]].push_back(label[v]);
					pred[label[v]].push_back(label[u]);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			semi[i] = best[i] = i;
			idom[i] = ancestor[i] = 0;
			bucket[i].clear();
		}
		for (int w = cnt; w >= 2; --w) {
			int p = label[parent[real[w]]];
			for (vector<int>::iterator it = pred[w].begin(); it != pred[w].end(); ++it) {
				int v = *it;
				int u = eval(v);
				if (semi[w] > semi[u]) semi[w] = semi[u];
			}
			bucket[semi[w]].push_back(w);
			link(p, w);
			while (!bucket[p].empty()) {
				int v = bucket[p].front();
				bucket[p].pop_front();
				int u = eval(v);
				idom[v] = (semi[u] < p ? u : p);
			}
		}
		for (int w = 2; w <= cnt; ++w) {
			if (idom[w] != semi[w]) idom[w] = idom[idom[w]];
		}
		idom[1] = 0;
		for (int i = 1; i <= cnt; ++i) {
			int u = real[idom[i]], v = real[i];
			// u is immediate dominator of v (i == 1?)
			// print u - 1, v - 1;
		}
	}
};

int n, m;

vector<vector<int>> g;
vector<bool> used;
vector<bool> R;
vector<int> rez;

bool ktun(int v) {
	used[v] = true;
	for (int sub : g[v]) {
		if (rez[sub] == -1) {
			rez[sub] = v;
			return true;
		}
	}
	for (int sub : g[v]) {
		if (used[rez[sub]]) continue;
		R[sub] = true;
		if (ktun(rez[sub])) {
			rez[sub] = v;
			return true;
		}
	}
	return false;
}

pair<int, vector<bool>> match(vector<pii> edges) {
	g.clear();
	R.clear();
	rez.clear();
	rez.resize(n, -1);
	g.resize(n);
	R.resize(n);
	for (pii e : edges) {
		g[e.x].pb(e.y);
	}
	used = vector<bool>(n, false);
	f(i, n) {
		if (ktun(i)) {
			used = vector<bool>(n, false);		
		}
	}
	DTree tree(2 * n + 1);	
	f(i, n) {
		for (int sub : g[i]) {
			if (rez[sub] == i) {
				tree.add_edge(sub + n, i);
			} else {
				tree.add_edge(i, sub + n);	
			}
		}
	}
	vector<bool> L(n);
	f(i, n) {
		if (rez[i] != -1) {
			L[rez[i]] = true;
		}
	}
	R = vector<bool>(n, false);
	used = vector<bool>(n, false);	
	f(i, n) {
		if (!L[i]) {
			tree.add_edge(2 * n, i);
			ktun(i);
		}
	}
	tree.dominator();
	vector<bool> can_del(n, false);
	f(i, n) {
		if (!L[i]) {
			can_del[i] = true;
		}
	}
	f(i, n) {
		if (rez[i] == -1) {
		} else {
			if (R[i]) {
				bool found = false;	
				int j = i + n;
				while (j != -1) {
					if (j == rez[i]) {
						found = true;
					}
					j = tree.parent[j + 1] - 1;
				}
				can_del[rez[i]] = !found;
			}
		}
	}
	int cnt = 0;
	f(i, n) {
		cnt += (rez[i] == -1);
	}
	return mp(cnt, can_del);
}

signed main(signed argc, char *argv[]) {
	scan n, m;
	vector<pii> edges, rev;
	f(i, m) {
		int a, b;
		scan a, b;
		a--;b--;
		edges.emplace_back(a, b);
		rev.emplace_back(b, a);
	}
	auto A = match(edges);
	auto B = match(rev);
	int y = min(A.x, B.x);
	vector<int> free;
	f(i, n) {
		if (A.y[i] || B.y[i]) {
			free.pb(i + 1);
		}
	}
	if (y - 1 == 0) {
		print 0;
	} else {
		print y - 1;
		print free;
	}
}
