const int N = 1e7;

vector<bool> is_prime(N, true);
vector<int> min_div(N, N);

vector<int> primes;
map<pair<ll, int>, int> mem;

const int A = 50000, B = 1000;
int memo[A][B];
num dp(ll n, int i) {
	if (n == 0) return num(0);
	if (i == 0) return num(n) * num(n + 1) / num(2);
	if (n < primes[i]) return (n == 0) ? num(0) : num(1);
	if (n < A && i < B) {
		if (memo[n][i] != -1) return memo[n][i];
	}
	// if (mem.count(mp(n, i))) return num(mem[mp(n, i)]);

	num val = dp(n, i - 1) - num(primes[i - 1]) * dp(n / primes[i - 1], i - 1);
	// mem[mp(n, i)] = val.value;
	if (n < A && i < B) {
		memo[n][i] = val.value;
	}
	return val;
}

num calc(ll n, ll k) {
	if (n == 0) return num(0);
	for (ll i = 2; i * i <= k; i++) {
		if (k % i == 0) return 0;
	}
	num rez = 0;
	if (k >= (ll)1e4) {
		for (ll x = 1; x * k <= n; x++) {
			if (min_div[x] >= k || x == 1) {
				rez += k * x;
			}
		}
	} else {
		int i = lower_bound(primes.begin(), primes.end(), k) - primes.begin();
		assert(primes[i] == k);
		// print i;
		rez = dp(n, i) - dp(n, i + 1);
	}
	return rez;
}

signed main(signed argc, char *argv[]) {
	memset(memo, -1, sizeof memo);
	for (int i = 2; i < N; i++) {
		if (is_prime[i]) {
			primes.pb(i);
			min_div[i] = i;
			for (int j = i + i; j < N; j += i) {
				is_prime[j] = false;
				min_div[j] = min(min_div[j], i);
			}
		}	
	}

	ll l, r, k;
	scan l, r, k;
	print calc(r, k) - calc(l - 1, k);
}