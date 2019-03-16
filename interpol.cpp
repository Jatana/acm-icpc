template<class T>
vector<T> interpol(const vector<pair<T, T>> &pts) {
	if (pts.empty()) return {};
	vector<T> holy;
	vector<T> zero = {1};
	auto calc = [](vector<T> &poly, const T &x) {
		T s = 0;
		T p = 1;
		f(j, len(poly)) {
			s += poly[j] * p;
			p *= x;
		}
		return s;
	};
	holy.emplace_back(pts[0].y);
	for (int i = 1; i < len(pts); i++) {
		zero.insert(zero.begin(), 0);
		f(j, len(zero) - 1) {
			zero[j] -= zero[j + 1] * pts[i - 1].x;
		}
		T sub = pts[i].y - calc(holy, pts[i].x);
		T coef = sub / calc(zero, pts[i].x);
		while (len(holy) < len(zero)) {
			holy.pb(0);
		}
		for (int j = 0; j < len(zero); j++) {
			holy[j] += zero[j] * coef;
		}
	}
	return holy;
}