template<const ull MODO = (ull(1) << 61) - 1>
struct Hash {
	ull value = 0;
	ull reduction(const ull &a) {
		// Given 0 <= a < 2^64. Need to get sum of digits in base 2^61.
		return (a & MODO) + (a >> 61);
	}
	ull mod(const ull &a) {
		// Given 0 <= a < 2^64. Need to calculate a % MOD
		return reduction(reduction(a)+1)-1;
	}
	Hash() {}
	Hash(int _value) {
		value = mod((ull)_value);
	}
	Hash(ull _value) {
		value = mod(_value);
	}
	void operator+=(const Hash &b) {
		value += b.value;
		value -= (value >= MODO) * MODO;
	}
	friend Hash operator+(Hash a, const Hash &b) {
		a += b;
		return a;
	}
	void operator-=(const Hash &b) {
		value -= b.value;
		value += (value < 0) * MODO;
	}
	friend Hash operator-(Hash a, const Hash &b) {
		a -= b;
		return a;
	}
	void operator*=(const Hash &b) {
		const ull a0 = value & ~0u, a1 = value >> 32;
		const ull b0 = b.value & ~0u, b1 = b.value >> 32;
		const ull mid = a0 * b1 + a1 * b0;
		value = mod(reduction(a0 * b0) + (a1 * b1 << 3) + (mid >> 29) + (mid << 32 & MODO));
	}
	friend Hash operator*(Hash a, const Hash &b) {
		a *= b;
		return a;
	}
	Hash pow(ll p) const {
		Hash r = 1;
		Hash x; x.value = value;
		while (p) {
			if (p & 1) r *= x;
			x *= x;
			p /= 2;
		}
		return r;
	}
	Hash inv() const {
		return pow(MODO - 2);
	}
	void operator/=(const Hash &b) {
		(*this) *= b.inv();
	}
	friend Hash operator/(Hash a, const Hash &b) {
		a /= b;
		return a;
	}
	bool operator==(const Hash &b) {
		return value == b.value;
	}
	bool operator!=(const Hash &b) {
		return value != b.value;
	}
	friend void fast_print(const Hash &b) {
		fast_print(b.value);
	}
};