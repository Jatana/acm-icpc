namespace Flex {
	mt19937 gen(1337);

	struct Node {
		Node *l = NULL, *r = NULL, *junk = NULL;
		int prior = 0;
		int value = 0;
		int mod_value = 0;
		vector<int> values;

		Node(int _value) {
			value = _value;
			values.pb(value);
			prior = gen();
		}
	};

	pair<Node*, Node*> split(Node *node, int L);

	void push(Node *node);

	Node *interfere(Node *a, Node *b) {
		if (!a) return b;
		if (!b) return a;
		if (gen() % 2 == 0) {
			swap(a, b);
		}
		push(a);
		a->junk = b;
		return a;
	}

	void push(Node *node) {
		if (!node) return;
		if (node->junk) {
			auto t = split(node->junk, node->value);
			auto t2 = split(t.second, node->value + 1);
			node->l = interfere(node->l, t.first);
			node->r = interfere(node->r, t2.second);
			node->junk = NULL;
			if (t2.first) {
				for (int x : t2.first->values) {
					node->values.pb(x);
				}
			}
		}
		node->value += node->mod_value;
		if (node->l) {
			node->l->mod_value += node->mod_value;
		}
		if (node->r) {
			node->r->mod_value += node->mod_value;
		}
		node->mod_value = 0;
	}

	Node *merge(Node *l, Node *r) {
		if (!l) return r;
		if (!r) return l;
		push(l);
		push(r);
		if (l->prior > r->prior) {
			l->r = merge(l->r, r);
			return l;
		} else {
			r->l = merge(l, r->l);
			return r;
		}
	}

	pair<Node*, Node*> split(Node *node, int L) {
		if (!node) return mp(node, node);
		push(node);
		if (node->value >= L) {
			auto t = split(node->l, L);
			node->l = NULL;
			return mp(t.first, merge(t.second, node));
		} else {
			auto t = split(node->r, L);
			node->r = NULL;
			return mp(merge(node, t.first), t.second);
		}
	}

	pair<Node*, Node*> cut_segment(Node *node, int l, int r) {
		if (!node) return mp(node, node);
		push(node);
		auto t = split(node, l);
		auto t2 = split(t.second, r);
		return mp(merge(t.first, t2.second), t2.first);
	}

	Node *find(Node *node, int value) {
		if (!node) return node;
		push(node);
		if (node->value == value) return node;
		if (value > node->value) {
			return find(node->r, value);
		} else {
			return find(node->l, value);
		}
	}
};
