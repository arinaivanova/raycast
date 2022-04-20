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

		vec2d operator / (double n) const {
			assert(n != 0);
			return { x / n, y / n };
		}

		bool operator == (const vec2d &v) const {
			return v.x == x && v.y == y;
		}

		void operator += (const vec2d &v) {
			x += v.x, y += v.y;
		}

		void operator -= (const vec2d &v) {
			x -= v.x, y -= v.y;
		}
	};

	vec2d rot(const vec2d &v, double theta) {

		const double c = cos(theta), s = sin(theta);
		return {
			v.x*c-v.y*s,
			v.x*s+v.y*c
		};
	}

	double mag(const vec2d &v) {

		return sqrt(v.x*v.x+v.y*v.y);
	}

	vec2d normalize(const vec2d &v) {

		return v/mag(v);
	}
}

#endif