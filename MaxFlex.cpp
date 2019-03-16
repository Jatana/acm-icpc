mt19937 gen(1337);

namespace Flex {
	struct Node {
		Node *l = NULL, *r = NULL;
		int prior = 0;
		int value = 0;
		int mod_value = 0;
		list<int> values;

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

		push(a);
		push(b);

		if (a->prior < b->prior) {
			swap(a, b);
		}

		auto t = split(b, a->value);
		auto t2 = split(t.second, a->value + 1);

		if (t2.first) {
			a->values.splice(a->values.end(), t2.first->values);
		}

		a->l = interfere(a->l, t.first);
		a->r = interfere(a->r, t2.second);

		return a;
	}

	void push(Node *node) {
		if (!node) return;

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