const ll MOD = 1e9 + 7;
// const ll MOD = 998244353;
template<ll MOD>
struct Ring {
	ll value = 0;
	Ring() {}
	Ring(int _value) {
		value = _value;
		value = floor_mod(value, MOD);
	}
	Ring(ll _value) {
		value = _value;
		value = floor_mod(value, MOD);
	}
	Ring pow(ll p) const {
		Ring r = 1;
		Ring x; x.value = value;
		while (p) {
			if (p & 1) r *= x;
			x *= x;
			p /= 2;
		}
		return r;
	}
	Ring inv() const {
		return pow(MOD - 2);
	}
	void operator*=(const Ring<MOD> &b) {
		value *= b.value;
		value = floor_mod(value, MOD);
	}
	friend Ring operator*(Ring<MOD> a, const Ring<MOD> &b) {
		a *= b;
		return a;
	}
	void operator+=(const Ring<MOD> &b) {
		value += b.value;
		value -= (value >= MOD) * MOD;
	}
	friend Ring operator+(Ring a, const Ring &b) {
		a += b;
		return a;
	}
	void operator-=(const Ring<MOD> &b) {
		value -= b.value;
		value += (value < 0) ? MOD : 0;
	}
	friend Ring operator-(Ring a, const Ring &b) {
		a -= b;
		return a;
	}
	void operator/=(const Ring<MOD> &b) {
		(*this) *= b.inv();	
	}
	friend Ring operator/(Ring a, const Ring &b) {
		a /= b;
		return a;
	}
	bool operator==(const Ring<MOD> &b) {
		return value == b.value;
	}
	bool operator!=(const Ring<MOD> &b) {
		return value != b.value;
	}
	friend void fast_print(const Ring<MOD> &b) {
		fast_print(b.value);
	}
};