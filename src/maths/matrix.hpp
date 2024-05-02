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
		
		constexpr mat2& operator=(const mat2&) = default;

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

		constexpr mat3& operator=(const mat3&) = default;

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

		constexpr mat4& operator=(const mat4&) = default;

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
	void operator+=(mat2& a, mat2 o);
	void operator+=(mat3& a, mat3 o);
	void operator+=(mat4& a, mat4 o);

	//operator +=
	void operator+=(mat2& a, float o);
	void operator+=(mat3& a, float o);
	void operator+=(mat4& a, float o);

	//matrix + matrix
	
	mat2 operator+(mat2 a, mat2 b);
	mat3 operator+(mat3 a, mat3 b);
	mat4 operator+(mat4 a, mat4 b);

	//matrix + float

	mat2 operator+(mat2 a, float b);
	mat3 operator+(mat3 a, float b);
	mat4 operator+(mat4 a, float b);

	///---		SUBSTRACTION     ---///
	//operator -=
	void operator-=(mat2& a, mat2 o);
	void operator-=(mat3& a, mat3 o);
	void operator-=(mat4& a, mat4 o);

	//operator -=
	void operator-=(mat2& a, float o);
	void operator-=(mat3& a, float o);
	void operator-=(mat4& a, float o);

	//matrix - matrix

	mat2 operator-(mat2 a, mat2 b);
	mat3 operator-(mat3 a, mat3 b);
	mat4 operator-(mat4 a, mat4 b);

	//matrix - float

	mat2 operator-(mat2 a, float b);
	mat3 operator-(mat3 a, float b);
	mat4 operator-(mat4 a, float b);
}