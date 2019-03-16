struct BipolarDisorder {
	int n;
	vector<vector<int>> g;
	vector<pii> edges;
	vector<int> uptime;
	vector<int> tin;
	vector<bool> used;
	vector<int> buff;
	vector<bool> pick;
	vector<int> order;

	vector<int> at;

	int timer = 0;

	void init_time(int v) {
		used[v] = true;
		at[timer] = v; 
		tin[v] = uptime[v] = timer++;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			init_time(sub);
		}
	}

	void check(int v, int _forb) {
		used[v] = true;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			if (sub == _forb) continue;
			check(sub, _forb);
		}
	}
	bool is_critical_slow(int v) {
		used = vector<bool>(n, false);
		int cnt = 0;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			cnt++;
			check(sub, v);
		}
		return cnt >= 2;
	}
	vector<bool> crit;
	void go(int v, int _p) {
		used[v] = true;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (used[sub]) {
				uptime[v] = min(uptime[v], tin[sub]);
			} else {
				go(sub, v);
				uptime[v] = min(uptime[v], uptime[sub]);
				if (uptime[sub] >= tin[v]) {
					crit[v] = true;
				}
			}
		}
	}

	void update_critical() {
		tin = vector<int>(n, 0);
		uptime = vector<int>(n, 0);
		used = vector<bool>(n, false);
		init_time(0);
		crit = vector<bool>(n, false);
		used = vector<bool>(n, false);
		go(0, -1);
		crit[0] = is_critical_slow(0);
	}

	int A = -1;

	struct Node {
		Node *l = NULL, *r = NULL, *pref = NULL;
		int prior;
		int size = 1;

		Node() {
			prior = rng();
		} 
	};

	int get_size(Node *node) {
		return node ? node->size : 0;
	}

	void update(Node *node) {
		node->size = get_size(node->l) + get_size(node->r) + 1;
	}

	Node *merge(Node *l, Node *r) {
		if (!l) return r;
		if (!r) return l;
		if (l->prior > r->prior) {
			l->r = merge(l->r, r);
			l->r->pref = l;
			update(l);
			return l;
		} else {
			r->l = merge(l, r->l);
			r->l->pref = r;
			update(r);
			return r;
		}
	}

	pair<Node*, Node*> split(Node *node, int k) {
		if (!node) return mp(node, node);
		if (get_size(node->l) >= k) {
			if (node->l) node->l->pref = NULL;
			auto t = split(node->l, k);
			node->l = NULL;
			update(node);
			return mp(t.x, merge(t.y, node));
		} else {
			if (node->r) node->r->pref = NULL;
			auto t = split(node->r, k - get_size(node->l) - 1);
			node->r = NULL;
			update(node);
			return mp(merge(node, t.x), t.y);
		}
	}

	int get_id(Node *node) {
		int id = get_size(node->l);
		while (node->pref) {
			if (node->pref->r == node) {
				id += 1 + get_size(node->pref->l);
			}
			node = node->pref;
		}
		return id;
	}

	Node *cart = NULL;

	vector<Node*> pres;

	void dfs(int v, int _p, int end) {
		buff.pb(v);
		if (v == end) {
			for (int x : buff) {
				pres[x] = new Node();
				cart = merge(cart, pres[x]);
				pick[x] = true;
			}
		}
		at[timer] = v;
		uptime[v] = tin[v] = timer++;
		used[v] = true;
		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (used[sub]) {
				uptime[v] = min(uptime[v], tin[sub]);
			} else {
				dfs(sub, v, end);
				uptime[v] = min(uptime[v], uptime[sub]);
			}
		}
		buff.pop_back();
	}

	void echo(int v, int _p) {
		used[v] = true;

		if (!pick[v]) {
			buff.pb(v);
		}

		int B = at[uptime[v]];
		if (!buff.empty() && pick[B] && B != A) {
			int itA = get_id(pres[A]);
			int itB = get_id(pres[B]);
			if (itA < itB) {
				auto t = split(cart, itA + 1);
				for (int x : buff) {
					pres[x] = new Node();
					t.x = merge(t.x, pres[x]);
				}
				cart = merge(t.x, t.y);
			} else {
				reverse(buff.begin(), buff.end());
				auto t = split(cart, itB + 1);
				for (int x : buff) {
					pres[x] = new Node();	
					t.x = merge(t.x, pres[x]);
				}
				cart = merge(t.x, t.y);
			}
			for (int x : buff) {
				pick[x] = true;
			}
			buff.clear();
		}

		for (int sub : g[v]) {
			if (sub == _p) continue;
			if (used[sub]) continue;
			if (pick[v]) {
				A = v;
			}
			echo(sub, v);
		}
	}

	set<int> finded_crit;
	void _index(int v) {
		used[v] = true;
		for (int sub : g[v]) {
			if (used[sub]) continue;
			if (crit[sub]) {
				finded_crit.insert(sub);
			} else {
				_index(sub);
			}
		}
	}

	void init(int _n) {
		n = _n;
		g.resize(n);
		at.resize(2 * n);
		uptime.resize(n);
		tin.resize(n);
		timer = 0;
	}

	void add_edge(int a, int b) {
		g[a].pb(b);
		g[b].pb(a);
		edges.emplace_back(a, b);
	}

	vector<int> get_priors() {
		{
			used = vector<bool>(n, false);
			update_critical();
			used = vector<bool>(n, false);
			vector<int> pos;
			f(i, n) {
				if (crit[i]) continue;
				if (!used[i]) {
					if (len(g[i]) == 1) {
						pos.pb(i);
						used[i] = true;
					} else {
						finded_crit.clear();
						_index(i);
						if (len(finded_crit) <= 1) {
							pos.pb(i);
						}
					}
				}
			}
			if (len(pos) <= 1) {
				pos.pb(n - 1);
			}
			if (len(pos) != 2) {
				return {};
			}

			int start = pos[0];
			int end = pos[1];
			shuffle(pos.begin(), pos.end(), rng);

			used = vector<bool>(n, false);
			pick = vector<bool>(n, false);
			pres.resize(n, NULL);
			timer = 0;
			dfs(start, -1, end);
			buff.clear();
			used = vector<bool>(n, false);
			echo(start, -1);
			vector<int> p(n);
			f(i, n) {
				if (pres[i]) {
					p[i] = get_id(pres[i]);
				} else {
					return {};
				}
			}
			vector<int> in(n), out(n);
			for (pii edge : edges) {
				if (p[edge.x] > p[edge.y]) {
					swap(edge.x, edge.y);
				}
				in[edge.y]++;
				out[edge.x]++;
			}
			bool fail = false;
			f(i, n) {
				if (i != start && in[i] == 0) {
					fail = true;
				}
				if (i != end && out[i] == 0) {
					fail = true;
				}
			}
			if (!fail) {
				return p;
			} else {
				return {};
			}
		}
	}
};
