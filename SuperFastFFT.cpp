#define M_PI 3.141592653589793


class Complex {
public:
	ld real = 0, image = 0;
	Complex(){real = 0, image = 0; }
	Complex(const ld &_real, const ld &_image): real(_real), image(_image) {}
};


inline Complex operator *(const Complex &a, const Complex &b) {
	return Complex(a.real * b.real - a.image * b.image, a.real * b.image + b.real * a.image);
}


inline Complex sq(const Complex &a) {
	return Complex(a.real * a.real - a.image * a.image, a.real * a.image * 2);
}


inline Complex operator -(const Complex &a, const Complex &b) {
	return Complex(a.real - b.real, a.image - b.image);
}


inline Complex operator +(const Complex &a, const Complex &b) {
	return Complex(a.real + b.real, a.image + b.image);
}


inline Complex Conj(const Complex &a) {
	return Complex(a.real, -a.image);
}


Complex operator *(const Complex &a, const ld &b) {
	return Complex(a.real * b, a.image * b);
}


inline Complex operator /(const Complex &a, const Complex &b) {
	ld d = b.real * b.real + b.image * b.image;
	return Complex((a.real * b.real + a.image * b.image) / d, (a.image * b.real - a.real * b.image) / d);
}

Complex W[1 << 19];

namespace FFTSolver {

	// vector<Complex> W[30];
	int ukw = 0;
	int __get_log(int N) {
		return 31 - __builtin_clz(N);
	}

	void construct_roots(int N) {
		int n = __get_log(N);
		while (ukw < n) {
			int layer_log = ukw;
			int k = (1 << layer_log);		
			for (int j = 0; j < k; j++) {
				W[k - 1 + j] = (Complex(cos((2 * M_PI * (ld)j) / (ld)(2 * k)), sin((2 * M_PI * (ld)j) / (ld)(2 * k))));
			}
			ukw++;
		}
	}

	void __fft(Complex *a, int N, Complex e, bool inv) {
		for (int k = 1, id = 0; k < N; k *= 2, id++) {
			for (int i = 0; i < N; i += k * 2) {
				for (int j = 0; j < k; j++) {
					if (!inv) {
						Complex x = a[i + j], y = a[i + j + k];
						auto f = W[k - 1 + j] * y;
						a[i + j] = x + f;
						a[i + j + k] = x - f;
					} else {
						Complex x = a[i + j], y = a[i + j + k];
						auto f = Conj(W[k - 1 + j]) * y;
						a[i + j] = x + f;
						a[i + j + k] = x - f;
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

	void comComplex_convolution(Complex *a, int N, bool inv) {
		reverse_permutation(a, N);
		construct_roots(N);
		Complex e(cos(2.0 * M_PI / (ld)N), sin(2.0 * M_PI / (ld)N));
		if (inv) e = Conj(e);
		__fft(a, N, e, inv);
	}

	void transform_2_convolutions(Complex *a, int N) {
		Complex div_x = Complex(0, 1) * (4.0 * N);
		for (int i = 0; i < N / 2; i++) {
			int j = (N - i) % N;
			a[i] = (sq(a[i]) - sq(Conj(a[j]))) / div_x;
		}
		for (int i = N - 1; i > N / 2; i--) {
			a[i] = Conj(a[N - i]);
		}
		a[N / 2] = (sq(a[N / 2]) - sq(Conj(a[N / 2]))) / div_x;
	}

	inline vector<int> multiply(const vector<int> &a, const vector<int> &b) {
		int N = len(a) + len(b) + 1;
		while (__builtin_popcount(N) != 1) {
			N++;
		}

		Complex e(cos(2 * M_PI / (ld)N), sin(2 * M_PI / (ld)N));

		vector<Complex> mvp(N);
		for (int i = 0; i < N; i++) {
			if (i < len(a)) {
				mvp[i].real = a[i];
			}
			if (i < len(b)) {
				mvp[i].image = b[i];
			}
		}

		comComplex_convolution(mvp.data(), N, false);
		transform_2_convolutions(mvp.data(), N);
		comComplex_convolution(mvp.data(), N, true);


		vector<int> final(N);
		for (int i = 0; i < N; i++) {
			final[i] = round(mvp[i].real);	
		}

		return final;
	}
};