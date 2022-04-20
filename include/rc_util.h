#ifndef RC_UTIL_H_
#define RC_UTIL_H_

#include <algorithm>
#include "rc_math.h"

typedef uint32_t uint32;
typedef uint8_t uint8;

namespace rc {

	inline vec2d bound(const vec2d &v, double lb1, double lb2, double ub1, double ub2) {

		return { std::max(std::min(ub1, v.x), lb1), std::max(std::min(ub2, v.y), lb2) };
	}

	inline bool in_bound(const vec2d &v, double lb1, double lb2, double ub1, double ub2) {

		return v.x >= lb1 && v.x < ub1 && v.y >= lb2 && v.y < ub2;
	}

	inline uint32 color(uint8 r, uint8 g, uint8 b) {

		const uint8 a = 255;
		return (a << 24) | (r << 16) | (g << 8) | b;
	}
}

#endif