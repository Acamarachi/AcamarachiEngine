#include <cmath>
#include "linear.hpp"

namespace Acamarachi::Maths
{
	mat2 transpose(mat2 m)
	{
		mat2 T(	vec2(m[0][0], m[1][0]),
				vec2(m[0][1], m[1][1]));
		return T;
	}

	mat3 transpose(mat3 m)
	{
		return mat3(vec3(m[0][0], m[1][0], m[2][0]),
					vec3(m[0][1], m[1][1], m[2][1]),
					vec3(m[0][2], m[1][2], m[2][2]));
	}

	mat4 transpose(mat4 m)
	{
		return mat4(vec4(m[0][0], m[1][0], m[2][0], m[3][0]),
					vec4(m[0][1], m[1][1], m[2][1], m[3][1]),
					vec4(m[0][2], m[1][2], m[2][2], m[3][2]),
					vec4(m[0][3], m[1][3], m[2][3], m[3][3]));
	}

	float dot(vec2 x, vec2 y)
	{
		return x[0]*y[0] + x[1] * y[1];
	}

	float dot(vec3 x, vec3 y)
	{
		return x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
	}

	float dot(vec4 x, vec4 y)
	{
		return x[0] * y[0] + x[1] * y[1] + x[2] * y[2] + x[3] * y[3];
	}

	vec3 cross(vec3 x, vec3 y)
	{
		return vec3(x[1] * y[2] - y[1] * x[2],
					x[2] * y[0] - y[2] * x[0],
					x[0] * y[1] - y[0] * x[1]);
	}

	float length(vec2 v)
	{
		return sqrtf(v[0] * v[0] + v[1] * v[1]);
	}

	float length(vec3 v)
	{
		return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}

	float length(vec4 v)
	{
		return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
	}

	vec2 normalize(vec2 x)
	{
		return x / length(x);
	}

	vec3 normalize(vec3 x)
	{
		return x / length(x);
	}

	vec4 normalize(vec4 x)
	{
		return x / length(x);
	}

}
