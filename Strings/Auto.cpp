vector<int> suffix_array(const string &s) {
    int n = s.size(), N = max(n, 257);
    vector<int> sa(n), ra(n);
    for (int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for (int k = 0; k < n; k ? k <<= 1 : k++) {
        vector<int> nsa(sa), nra(n), cnt(N);
        for (int i = 0; i < n; ++i) nsa[i] -= k - (nsa[i] < k ? n : 0);
        for (int i = 0; i < n; ++i) cnt[ra[i]]++;
        for (int i = 1; i < N; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[ra[nsa[i]]]] = nsa[i];
        int r = 0;
        for (int i = 1; i < n; ++i) {
            if (ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if (ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        swap(ra, nra);
    }
    return sa;
}

int nodes = 0;

struct Auto {
	struct Node {
		map<char, Node*> go;
		int max_len = 0;
		Node *sufflink = NULL;
		int id = 0;

		Node() {
			id = nodes++;
		}
	};

	Node *clone(Node *node) {
		Node *cl = new Node();
		cl->go = node->go;
		cl->max_len = node->max_len;
		cl->sufflink = node->sufflink;
		return cl;
	}

	Node *root = new Node();
	Node *cur = NULL;

	Auto() {
		cur = root;
	}

	void add(char c) {
		Node *_new = new Node();
		_new->max_len = cur->max_len + 1;
		_new->sufflink = root;
		while (cur && !cur->go.count(c)) {
			cur->go[c] = _new;
			cur = cur->sufflink;
		}	
		if (cur) {
			if (cur->go[c]->max_len == cur->max_len + 1) {
				_new->sufflink = cur->go[c];
			} else {
				Node *q = cur->go[c];
				Node *p = clone(cur->go[c]);
				_new->sufflink = p;
				cur->go[c]->sufflink = p;
				p->max_len = cur->max_len + 1;

				while (cur) {
					if (cur->go[c] == q) {
						cur->go[c] = p;
						cur = cur->sufflink;
					} else {
						break;
					}
				}	
			}
		}
		cur = _new;
	}

	bool check(Node *node, string &s, int i) {
		if (i >= len(s)) return true;
		if (!node->go.count(s[i])) return false;
		return check(node->go[s[i]], s, i + 1);
	}
};