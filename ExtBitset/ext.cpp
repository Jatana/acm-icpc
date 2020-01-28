/*
	extension that supports find_next, find_prev.
*/
#include <cassert>
#define _M_w __first_
#define private public
#define protected public
#include <bitset>

using biti = typename std::remove_reference<decltype(std::bitset<400>().__first_[0])>::type;
const int SIZE = 8 * sizeof(biti);
const int LOG = ctz(SIZE);

template <size_t _Size> inline int find_next(const std::bitset<_Size> &__v, int i) {
	i++;
	assert(i >= 0);
	if (i >= _Size) return _Size;
	int b = (i >> LOG);
	int j = (i & (SIZE - 1));
	if (__v.__first_[b] >> j)
		return (b << LOG) + ctz(__v.__first_[b] >> j) + j;
	for (b++; (b << LOG) < _Size; b++)
		if (__v.__first_[b])
			return (b << LOG) + ctz(__v.__first_[b]);
	return _Size;
}

template <size_t _Size> inline int find_prev(const std::bitset<_Size> &__v, int i) {
	if (i < 0) return -1;
	assert(i <= _Size);
	int start = i >> LOG;
	int first_bits = i & (SIZE - 1);
	if (first_bits) {
		biti curr = __v.__first_[start];
		curr = curr << (SIZE - first_bits) >> (SIZE - first_bits);
		if (curr)
			return start << LOG | (SIZE - clz(curr) - 1);
	}
	for (int i = start - 1; i >= 0; i--) {
		biti curr = __v.__first_[i];
		if (curr) return (i << LOG) | (SIZE - clz(curr) - 1);
	}
	return -1;
}
#undef private
#undef protected
#undef _M_w