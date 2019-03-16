struct Node {
	Node *go[2];
	Node *pref = NULL;
	Node *mem_sufflink = NULL;
	int cur = -1;
	bool term = false;
	vector<int> mem_dp;

	Node(int _cur, Node *_pref) {
		cur = _cur;
		pref = _pref;
		go[0] = go[1] = NULL;
		mem_dp.resize(2001, -1);
	}

	Node *get_sufflink() {
		if (!pref) return this;
		if (!pref->pref) return pref;
		if (mem_sufflink) return mem_sufflink;
		return mem_sufflink = pref->get_sufflink()->get_go(cur);
	}

	Node *get_go(int c) {
		if (go[c]) return go[c];
		if (!pref) return this;
		return get_sufflink()->get_go(c);
	}

	void add(const string &s, int i) {
		if (i >= len(s)) {
			term = true;
		} else {
			int c = s[i] - '0';
			if (!go[c]) {
				go[c] = new Node(c, this);
			}
			go[c]->add(s, i + 1);
		}
	}

	num dp(int n) {
		if (n < 0) return 0;
		if (mem_dp[n] != -1) return mem_dp[n];
		if (term) {
			return num(2).pow(n);
		} else {
			num rez = 0;
			f(j, 2) {
				rez += get_go(j)->dp(n - 1);
			}
			return mem_dp[n] = rez.value;
		}
	}
};