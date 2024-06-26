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

	mat4 inverse(mat4 m)
	{
		float A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		float A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
		float A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
		float A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
		float A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
		float A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
		float A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		float A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
		float A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
		float A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		float A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
		float A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		float A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
		float A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
		float A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
		float A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
		float A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
		float A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

		float inverseDet = m[0][0] * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223)
			- m[0][1] * (m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223)
			+ m[0][2] * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123)
			- m[0][3] * (m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
		inverseDet = 1 / inverseDet;


		float a = inverseDet * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223);
		float b = inverseDet * -(m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223);
		float c = inverseDet * (m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213);
		float d = inverseDet * -(m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212);

		vec4 x(a, b, c, d);

		a = inverseDet * -(m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223);
		b = inverseDet * (m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223);
		c = inverseDet * -(m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213);
		d = inverseDet * (m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212);

		vec4 y(a, b, c, d);

		a = inverseDet * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123);
		b = inverseDet * -(m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123);
		c = inverseDet * (m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113);
		d = inverseDet * -(m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112);

		vec4 z(a, b, c, d);

		a = inverseDet * -(m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
		b = inverseDet * (m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123);
		c = inverseDet * -(m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113);
		d = inverseDet * (m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112);

		vec4 w(a, b, c, d);
		
		return mat4(x, y, z, w);
	}

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
