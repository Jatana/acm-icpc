namespace FFTSolver {
	typedef complex<ld> plex;

	vector<vector<plex>> W;

	int __get_log(int N) {
		return 31 - __builtin_clz(N);
	}

	void construct_roots(int N) {
		int n = __get_log(N);
		while (len(W) < n) {
			int layer_log = len(W);
			int k = (1 << layer_log);		
			W.pb(vector<plex>());
			W.back().resize(k);
			for (int j = 0; j < k; j++) {
				W.back()[j] = (plex(cos((2 * M_PI * (ld)j) / (ld)(2 * k)), sin((2 * M_PI * (ld)j) / (ld)(2 * k))));
			}
		}
	}

	void __fft(plex *a, int N, plex e, bool inv) {
		for (int k = 1, id = 0; k < N; k *= 2, id++) {
			for (int i = 0; i < N; i += k * 2) {
				for (int j = 0; j < k; j++) {
					if (!inv) {
						plex x = a[i + j], y = a[i + j + k];
						a[i + j] = x + W[id][j] * y;
						a[i + j + k] = x - W[id][j] * y;
					} else {
						plex x = a[i + j], y = a[i + j + k];
						a[i + j] = x + conj(W[id][j]) * y;
						a[i + j + k] = x - conj(W[id][j]) * y;
					}
				}
			}
		}	
	}

	template <class T>
	void reverse_permutation(T *a, int N) {
		int N_2 = (N >> 1), r = 0;
		for (int x = 1; x < N; ++ x) {
			int h = N_2;
			while (((r ^= h) & h) == 0) h >>= 1;
			if (r > x) swap(a[x], a[r]);
		}
	}

	void complex_convolution(plex *a, int N, bool inv) {
		reverse_permutation(a, N);
		construct_roots(N);
		plex e(cos(2.0 * M_PI / (ld)N), sin(2.0 * M_PI / (ld)N));
		if (inv) e = conj(e);
		__fft(a, N, e, inv);
	}

	void transform_2_convolutions(plex *a, int N) {
		plex div_x = plex(0, 1) * (4.0 * N);
		for (int i = 0; i < N / 2; i++) {
			int j = (N - i) % N;
			a[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j])) / div_x;
		}
		for (int i = N - 1; i > N / 2; i--) {
			a[i] = conj(a[N - i]);
		}
		a[N / 2] = (a[N / 2] + conj(a[N / 2])) * (a[N / 2] - conj(a[N / 2])) / div_x;
	}

	inline vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
		int N = len(a) + len(b) + 1;
		while (__builtin_popcount(N) != 1) {
			N++;
		}

		plex e(cos(2 * M_PI / (ld)N), sin(2 * M_PI / (ld)N));

		vector<plex> mvp(N);
		for (int i = 0; i < N; i++) {
			if (i < len(a)) {
				mvp[i].real(a[i]);
			}
			if (i < len(b)) {
				mvp[i].imag(b[i]);
			}
		}

		complex_convolution(mvp.data(), N, false);
		transform_2_convolutions(mvp.data(), N);
		complex_convolution(mvp.data(), N, true);


		vector<ll> final(N);
		for (int i = 0; i < N; i++) {
			final[i] = round(real(mvp[i]));	
		}

		return final;
	}

	template<class T>
	inline vector<T> multiply_high_precision(vector<ll> a, vector<ll> b) {
		int N = max(len(a), len(b));
		a.resize(N, 0);
		b.resize(N, 0);
		vector<ll> A = a;
		vector<ll> B = b;
		ll C = 0;
		f(i, N) {
			C = max(C, abs(a[i]));
			C = max(C, abs(b[i]));
		}
		C = sqrt(C);
		f(i, N) {
			A[i] /= C;
			B[i] /= C;
			a[i] %= C;
			b[i] %= C;
		}
		vector<ll> high = multiply(A, B);
		vector<ll> Ab = multiply(A, b);
		vector<ll> Ba = multiply(B, a);
		vector<ll> ab = multiply(a, b);
		vector<T> gl(len(high));

		T _C(C);

		f(i, len(gl)) {
			gl[i] = _C * _C * T(high[i]) + _C * (T(Ab[i]) + T(Ba[i])) + T(ab[i]);
		}
		return gl;
	}
};