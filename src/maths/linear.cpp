#include <cmath>
#include "linear.hpp"

#define UNUSED_PARAM(x)  (void)x

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

	mat2 inverse(mat2 x)
	{
		float inverseDet = 1.0f / determinant(x);
		mat2 m = { {x[1][1],-x[0][1]},{-x[1][0],x[0][0]} };

		return inverseDet * m;
	}

	mat3 inverse(mat3 m)
	{
		float inverseDet = 1.0f / determinant(m);

		float a = inverseDet * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
		float b = inverseDet * -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
		float c = inverseDet * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
		
		vec3 x(a, b, c);

		a = inverseDet * -(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
		b = inverseDet * (m[0][0] * m[2][2] - m[0][2] * m[2][0]);
		c = inverseDet * -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);

		vec3 y(a, b, c);

		a = inverseDet * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
		b = inverseDet * -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);
		c = inverseDet * (m[0][0] * m[1][1] - m[0][1] * m[1][0]);

		vec3 z(a, b, c);

		return mat3(x,y,z);
	}

	//mat4 inverse(mat4 m)
	//{
	//	float inverseDet = 1.0f / determinant(m);
	//	m00 = inverseDet * (m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223),
	//	m01 = inverseDet * -(m.m01 * A2323 - m.m02 * A1323 + m.m03 * A1223),
	//	m02 = inverseDet * (m.m01 * A2313 - m.m02 * A1313 + m.m03 * A1213),
	//	m03 = inverseDet * -(m.m01 * A2312 - m.m02 * A1312 + m.m03 * A1212),
	//	m10 = inverseDet * -(m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223),
	//	m11 = inverseDet * (m.m00 * A2323 - m.m02 * A0323 + m.m03 * A0223),
	//	m12 = inverseDet * -(m.m00 * A2313 - m.m02 * A0313 + m.m03 * A0213),
	//	m13 = inverseDet * (m.m00 * A2312 - m.m02 * A0312 + m.m03 * A0212),
	//	m20 = inverseDet * (m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123),
	//	m21 = inverseDet * -(m.m00 * A1323 - m.m01 * A0323 + m.m03 * A0123),
	//	m22 = inverseDet * (m.m00 * A1313 - m.m01 * A0313 + m.m03 * A0113),
	//	m23 = inverseDet * -(m.m00 * A1312 - m.m01 * A0312 + m.m03 * A0112),
	//	m30 = inverseDet * -(m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123),
	//	m31 = inverseDet * (m.m00 * A1223 - m.m01 * A0223 + m.m02 * A0123),
	//	m32 = inverseDet * -(m.m00 * A1213 - m.m01 * A0213 + m.m02 * A0113),
	//	m33 = inverseDet * (m.m00 * A1212 - m.m01 * A0212 + m.m02 * A0112),
	//}

	float determinant(mat2 m)
	{
		return m[0][0]*m[1][1] - m[0][1]*m[1][0];
	}

	float determinant(mat3 m)
	{
		return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1]
			- m[0][2] * m[1][1] * m[2][0] - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];
	}

	//https://semath.info/src/determinant-four-by-four.html
	float determinant(mat4 m)
	{
		float det = 0.0f;

		det = m[0][0] * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
			- m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1])
			+ m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));

		det -= m[0][1] * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
			- m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0])
			+ m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));

		det += m[0][2] * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1])
			- m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0])
			+ m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));

		det -= m[0][3] * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
			- m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
			+ m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));

		return det;
	}


	//scalar multiplication
	mat2 operator*(float a, mat2 m)
	{
		return mat2( m[0] * a,m[1] * a );
	}

	mat3 operator*(float a, mat3 m)
	{
		return mat3(m[0] * a, m[1] * a, m[2] * a);
	}

	mat4 operator*(float a, mat4 m)
	{
		return mat4(m[0] * a, m[1] * a, m[2] * a, m[3] * a);
	}

	void operator*=(mat2& m, float a)
	{
		m = a * m;
	}

	void operator*=(mat3& m, float a)
	{
		m = a * m;
	}

	void operator*=(mat4& m, float a)
	{
		m = a * m;
	}


	//vector matrix multiplication
	vec2 operator*(mat2 m, vec2 v)
	{
		return vec2(dot(m[0], v), dot(m[1], v));
	}
	vec3 operator*(mat3 m, vec3 v)
	{
		return vec3(dot(m[0], v), dot(m[1], v), dot(m[2], v));
	}

	vec4 operator*(mat4 m, vec4 v)
	{
		return vec4(dot(m[0], v), dot(m[1], v), dot(m[2], v), dot(m[3], v));
	}


	//vector matrix multiplication
	mat2 operator*(mat2 a, mat2 b)
	{
		b = transpose(b);

		return {
					{dot(a[0],b[0]) , dot(a[0],b[1])},
					{dot(a[1],b[0]) , dot(a[1],b[1])}
		};
	}

	mat3 operator*(mat3 a, mat3 b)
	{
		b = transpose(b);
		return {
					{dot(a[0],b[0]) , dot(a[0],b[1]) , dot(a[0],b[2])},
					{dot(a[1],b[0]) , dot(a[1],b[1]) , dot(a[1],b[2])},
					{dot(a[2],b[0]) , dot(a[2],b[1]) , dot(a[2],b[2])}
		};
	}

	mat4 operator*(mat4 a, mat4 b)
	{
		b = transpose(b);
		return {
					{dot(a[0],b[0]) , dot(a[0],b[1]) , dot(a[0],b[2]) , dot(a[0],b[3])},
					{dot(a[1],b[0]) , dot(a[1],b[1]) , dot(a[1],b[2]) , dot(a[1],b[3])},
					{dot(a[2],b[0]) , dot(a[2],b[1]) , dot(a[2],b[2]) , dot(a[2],b[3])},
					{dot(a[3],b[0]) , dot(a[3],b[1]) , dot(a[3],b[2]) , dot(a[3],b[3])}
		};
	}

}
