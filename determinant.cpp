template<class T>
T det(vector<vector<T>> v) {
	int n = len(v);
	T d = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[j][i] != T(0)) {
				swap(v[j], v[i]);
				d *= -1;
				break;
			}
		}
		if (v[i][i] == 0) return (T)0;
		d *= v[i][i];
		for (int j = i + 1; j < n; j++) {
			num coef = v[j][i] / v[i][i];
			for (int k = i; k < n; k++) {
				v[j][k] -= (v[i][k] * coef);
			}
		}
	}
	return d;
}