#ifndef RC_MATH_H_
#define RC_MATH_H_

namespace rc {

	struct vec2d {

		double x, y;

		vec2d operator - () {
			return { -x, -y };
		}

		vec2d operator + (const vec2d &v) const {
			return { v.x + x, v.y + y };
		}

		vec2d operator - (const vec2d &v) const {
			return { x - v.x, y - v.y };
		}

		vec2d operator * (double n) const {
			return { x*n, y*n };
		}

		void operator += (const vec2d &v) {
			x += v.x, y += v.y;
		}

		void operator -= (const vec2d &v) {
			x -= v.x, y -= v.y;
		}
	};

	vec2d rot(const vec2d &v, double theta) {
		return {
			cos(theta)*v.x-sin(theta)*v.y,
			sin(theta)*v.x+cos(theta)*v.y
		};
	}
}

#endif