#pragma once
#include "vector.hpp"

namespace Acamarachi::Maths
{
	typedef struct mat2 {

		vec2 data[2];

		//constructor
		mat2(vec2 x, vec2 y) : data{ x,y } {};
		mat2() : data{vec2(),vec2()} {};
		mat2(mat2& o) : data{ o.data[0], o.data[1] } {};

		//getter with array position
		vec2& operator[](int pos)
		{
			return data[pos];
		}

		vec2 operator[](int pos) const
		{
			return data[pos];
		}

	} mat2;

	typedef struct mat3 {

		vec3 data[3];

		//constructor
		mat3(vec3 x, vec3 y, vec3 z) : data{ x,y,z } {}
		mat3() : data{ vec3(),vec3(),vec3() } {}
		mat3(mat3& o) : data{ o.data[0],o.data[1],o.data[2] } {}

		//getter with array position
		vec3& operator[](int pos)
		{
			return data[pos];
		}

		vec3 operator[](int pos) const
		{
			return data[pos];
		}

	} mat3;

	typedef struct mat4 {

		vec4 data[4];

		//constructor
		mat4(vec4 x, vec4 y, vec4 z, vec4 w) : data{ x,y,z,w } {}
		mat4() : data{ vec4(),vec4(),vec4(),vec4() } {}
		mat4(mat4& o) : data{ o.data[0],o.data[1],o.data[2],o.data[3] } {}

		//getter with array position
		vec4& operator[](int pos)
		{
			return data[pos];
		}

		vec4 operator[](int pos) const
		{
			return data[pos];
		}

	} mat4;

	///---		ADDITION     ---///
	//operator +=
	void operator+=(mat2& a, mat2 o)
	{
		a[0] += o[0];
		a[1] += o[1];
	}

	void operator+=(mat3& a, mat3 o)
	{
		a[0] += o[0];
		a[1] += o[1];
		a[2] += o[2];
	}

	void operator+=(mat4& a, mat4 o)
	{
		a[0] += o[0];
		a[1] += o[1];
		a[2] += o[2];
		a[3] += o[3];
	}

	//operator +=
	void operator+=(mat2& a, float o)
	{
		a[0] += o;
		a[1] += o;
	}

	void operator+=(mat3& a, float o)
	{
		a[0] += o;
		a[1] += o;
		a[2] += o;
	}

	void operator+=(mat4& a, float o)
	{
		a[0] += o;
		a[1] += o;
		a[2] += o;
		a[3] += o;
	}

	//matrix + matrix
	
	mat2 operator+(mat2 a, mat2 b)
	{
		return mat2(a[0] + b[0], a[1] + b[1]);
	}

	mat3 operator+(mat3 a, mat3 b)
	{
		return mat3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
	}

	mat4 operator+(mat4 a, mat4 b)
	{
		return mat4(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
	}

	//matrix + float

	mat2 operator+(mat2 a, float b)
	{
		return mat2(a[0] + b, a[1] + b);
	}

	mat3 operator+(mat3 a, float b)
	{
		return mat3(a[0] + b, a[1] + b, a[2] + b);
	}

	mat4 operator+(mat4 a, float b)
	{
		return mat4(a[0] + b, a[1] + b, a[2] + b, a[3] + b);
	}

	///---		SUBSTRACTION     ---///
	//operator -=
	void operator-=(mat2& a, mat2 o)
	{
		a[0] -= o[0];
		a[1] -= o[1];
	}

	void operator-=(mat3& a, mat3 o)
	{
		a[0] -= o[0];
		a[1] -= o[1];
		a[2] -= o[2];
	}

	void operator-=(mat4& a, mat4 o)
	{
		a[0] -= o[0];
		a[1] -= o[1];
		a[2] -= o[2];
		a[3] -= o[3];
	}

	//operator -=
	void operator-=(mat2& a, float o)
	{
		a[0] -= o;
		a[1] -= o;
	}

	void operator-=(mat3& a, float o)
	{
		a[0] -= o;
		a[1] -= o;
		a[2] -= o;
	}

	void operator-=(mat4& a, float o)
	{
		a[0] -= o;
		a[1] -= o;
		a[2] -= o;
		a[3] -= o;
	}

	//matrix - matrix

	mat2 operator-(mat2 a, mat2 b)
	{
		return mat2(a[0] - b[0], a[1] - b[1]);
	}

	mat3 operator-(mat3 a, mat3 b)
	{
		return mat3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
	}

	mat4 operator-(mat4 a, mat4 b)
	{
		return mat4(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
	}

	//matrix - float

	mat2 operator-(mat2 a, float b)
	{
		return mat2(a[0] - b, a[1] - b);
	}

	mat3 operator-(mat3 a, float b)
	{
		return mat3(a[0] - b, a[1] - b, a[2] - b);
	}

	mat4 operator-(mat4 a, float b)
	{
		return mat4(a[0] - b, a[1] - b, a[2] - b, a[3] - b);
	}
}