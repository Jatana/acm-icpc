template<class ld>
struct Simplex {	
	int n, m;
	vector<vector<ld>> v;
	vector<int> p;
	enum {
		NoSolution, Unbounded, Found
	} state;
	vector<ld> values;
	const ld EPS = 0.0000001;
	void pivot(int _x, int row) {
		ld div = v[row][_x];
		if (abs(div) > EPS) {
			for (int i = 0; i < n + 1; i++)
				v[row][i] /= div;
			for (int i = 0; i < m + 2; i++) 
				if (i != row) {
					ld coef = v[i][_x];
					for (int j = 0; j < n + 1; j++)
						v[i][j] -= coef * v[row][j];
				}
		}
		p[row] = _x;
	}
	bool simplex() {
		while (true) {
			int _x = -1;
			for (int i = 0; i < n; i++)
				if (v.back()[i] > EPS
						&& find(p.begin(), p.end(), i) == p.end())
					_x = i;
			if (_x == -1) break;
			int row = -1;
			for (int j = 0; j < m; j++) {
				if (v[j][_x] > EPS)
					if (row == -1 || v[j].back() * v[row][_x] < v[row].back() * v[j][_x])
						row = j;
			}
			if (row == -1) 
				return false;
			pivot(_x, row);
		}
		return true;
	}
	/*
		-> _v : _v[0][0] * x[0] + _v[0][1] * x[1] + ... + _v[0][n - 1] * x[n - 1] <= _v[0][n]
			  : _v[1][0] * x[0] + _v[1][1] * x[1] + ... + _v[1][n - 1] * x[n - 1] <= _v[1][n]
			  	...
			  : _v[m - 1][0] * x[0] + _v[m - 1][1] * x[1] + ... + _v[m - 1][n - 1] * x[n - 1] <= _v[m - 1][n]
			  ! _v[m][0] * x[0] + _v[m][1] * x[1] + ... + _v[m][n - 1] * x[n - 1] --> max
		-> x[i] >= 0
		-> state(NoSolution, Unbounded, Found)
		-> values[i] = x[i] 
		-> values[n] = Result 
	*/
	Simplex(vector<vector<ld>> _v) {
		for (int i = 0; i < len(_v); i++) {
			v.pb(vector<ld>(len(_v) - 1));
			if (i < len(_v) - 1)
				v.back()[i] = 1;
			v.back().insert(v.back().end(), _v[i].begin(), _v[i].end());
			v.back().insert(v.back().end() - 1, -1);
		}
		n = len(v[0]) - 1;
		m = len(v) - 1;
		p.resize(m);
		iota(p.begin(), p.end(), 0);
		v.pb(vector<ld>(n + 1));
		v.back()[n - 1] = -1;
		int mrow = 0;
		for (int i = 0; i < m; i++)
			if (v[i].back() < v[mrow].back())
				mrow = i;
		if (v[mrow].back() < -EPS)
			pivot(n - 1, mrow);
		simplex();
		if (v.back().back() > EPS) {
			state = NoSolution;
			return;
		}
		if (find(p.begin(), p.end(), n - 1) != p.end()) {
			int row = find(p.begin(), p.end(), n - 1) - p.begin();
			int _x = -1;
			for (int i = 0; i < n; i++)
				if (abs(v[row][i]) > EPS)
					if (find(p.begin(), p.end(), i) == p.end())
						_x = i;
			pivot(_x, row);
		}
		for (int i = 0; i < m + 2; i++)
			v[i][n - 1] = 0;
		swap(v[m], v[m + 1]);
		if (!simplex()) {
			state = Unbounded;
			return;
		}
		values.resize(n);	
		for (int i = 0; i < m; i++) {
			values[p[i]] = v[i].back();
		}
		state = Found;
		values = vector<ld>(values.begin() + m, values.end() - 1);
		values.pb(-v.back().back());
	}
};