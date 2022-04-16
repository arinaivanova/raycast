#ifndef RC_UTIL_H_
#define RC_UTIL_H_

#include <algorithm>
#include "rc_math.h"

namespace rc {

	inline vec2d bound(const vec2d &v, double lb1, double lb2, double ub1, double ub2) {
		return { std::max(std::min(ub1, v.x), lb1), std::max(std::min(ub2, v.y), lb2) };
	}
}

#endif