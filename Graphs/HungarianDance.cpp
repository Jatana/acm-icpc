struct Dance {
	int n, m;
	vector<vector<int>> v;
	vector<int> rez;
	vector<int> row, col;
	vector<bool> srow, scol;
	vector<int> min_value, min_pos;
	vector<pii> invoker;

	Dance(vector<vector<int>> _v) {
		v = _v;
		n = le(v);
		m = le(v[0]);

		row.resize(n, 0);
		col.resize(m, 0);
		rez.resize(m, -1);
	}

	int get(int i, int j) {
		return v[i][j] + row[i] + col[j];
	}

	pair<vector<int>, int> match() {
		f(cur, n) {
			min_value = vector<int>(m, 1e9);
			min_pos = vector<int>(m, -1);
			invoker = vector<pii>(n, mp(-1, -1));
			srow = vector<bool>(n, false);
			scol = vector<bool>(m, false);
			
			int next = cur;
			while (true) {
				srow[next] = true;
				f(j, m) {
					if (get(next, j) < min_value[j]) {
						min_value[j] = get(next, j);
						min_pos[j] = next;
					}
				}

				pii _min = mp(-1, -1);
				f(j, m) {
					if (scol[j]) continue;
					if (_min.x == -1 || get(_min.x, _min.y) > min_value[j]) {
						_min = mp(min_pos[j], j);
					}
				}

				assert(_min != mp(-1, -1));

				int d = get(_min.x, _min.y);

				f(i, n) {
					if (srow[i]) {
						row[i] -= d;
					}
				}
				f(j, m) {
					if (scol[j]) {
						col[j] += d;
					}
				}
				f(j, m) {
					min_value[j] -= d;
				}
				if (rez[_min.y] == -1) {
					int ind = _min.y;
					int p = _min.x;
					while (ind != -1) {
						rez[ind] = p;
						ind = invoker[p].y;
						p = invoker[p].x;
					}
					break;
				} else {
					scol[_min.y] = true;
					invoker[rez[_min.y]] = mp(_min.x, _min.y);
					next = rez[_min.y];
				}
			}
		}
		int total = 0;
		f(i, m) {
			total += v[rez[i]][i];
		}
		return mp(rez, total);
	}
};
