#pragma once
#include "vector.hpp"

namespace Acamarachi::Maths
{
	//vector operation

	///---		ADDITION     ---///

	//vector +=
	void operator+=(vec2& a, vec2 o) {
		a = a + o;
	}

	void operator+=(vec3& a, vec3 o) {
		a = a + o;
	}

	void operator+=(vec4& a, vec4 o) {
		a = a + o;
	}

	//vector +=
	void operator+=(vec2& a, float o) {
		a = a + o;
	}

	void operator+=(vec3& a, float o) {
		a = a + o;
	}

	void operator+=(vec4& a, float o) {
		a = a + o;
	}

	//vector + vector
	vec2 operator+(vec2 a, vec2 o)
	{
		return vec2(a[0] + o[0], a[1] + o[1]);
	};

	vec3 operator+(vec3 a, vec3 o)
	{
		return vec3(a[0] + o[0], a[1] + o[1], a[2] + o[2]);
	};

	vec4 operator+(vec4 a, vec4 o)
	{
		return vec4(a[0] + o[0], a[1] + o[1], a[2] + o[2], a[3] + o[3]);
	};

	//Vector + float

	vec2 operator+(vec2 a, float o)
	{
		return vec2(a[0] + o, a[1] + o);
	};

	vec3 operator+(vec3 a, float o)
	{
		return vec3(a[0] + o, a[1] + o, a[2] + o);
	};

	vec4 operator+(vec4 a, float o)
	{
		return vec4(a[0] + o, a[1] + o, a[2] + o, a[3] + o);
	};

	///---		SUBSTRACTION     ---///

	//vector -=
	void operator-=(vec2& a, vec2 o) {
		a = a - o;
	}

	void operator-=(vec3& a, vec3 o) {
		a = a - o;
	}

	void operator-=(vec4& a, vec4 o) {
		a = a - o;
	}

	//vector -=
	void operator-=(vec2& a, float o) {
		a = a - o;
	}

	void operator-=(vec3& a, float o) {
		a = a - o;
	}

	void operator-=(vec4& a, float o) {
		a = a - o;
	}

	//vector - vector
	vec2 operator-(vec2 a, vec2 o)
	{
		return vec2(a[0] - o[0], a[1] - o[1]);
	};

	vec3 operator-(vec3 a, vec3 o)
	{
		return vec3(a[0] - o[0], a[1] - o[1], a[2] - o[2]);
	};

	vec4 operator-(vec4 a, vec4 o)
	{
		return vec4(a[0] - o[0], a[1] - o[1], a[2] - o[2], a[3] - o[3]);
	};

	//Vector - float

	vec2 operator-(vec2 a, float o)
	{
		return vec2(a[0] - o, a[1] - o);
	};

	vec3 operator-(vec3 a, float o)
	{
		return vec3(a[0] - o, a[1] - o, a[2] - o);
	};

	vec4 operator-(vec4 a, float o)
	{
		return vec4(a[0] - o, a[1] - o, a[2] - o, a[3] - o);
	};

	///---		MULTIPLICATION     ---///

	//vector *=
	void operator*=(vec2& a, vec2 o) {
		a = a * o;
	}

	void operator*=(vec3& a, vec3 o) {
		a = a * o;
	}

	void operator*=(vec4& a, vec4 o) {
		a = a * o;
	}

	//vector *=
	void operator*=(vec2& a, float o) {
		a = a * o;
	}

	void operator*=(vec3& a, float o) {
		a = a * o;
	}

	void operator*=(vec4& a, float o) {
		a = a * o;
	}

	//vector * vector
	vec2 operator*(vec2 a, vec2 o)
	{
		return vec2(a[0] * o[0], a[1] * o[1]);
	};

	vec3 operator*(vec3 a, vec3 o)
	{
		return vec3(a[0] * o[0], a[1] * o[1], a[2] * o[2]);
	};

	vec4 operator*(vec4 a, vec4 o)
	{
		return vec4(a[0] * o[0], a[1] * o[1], a[2] * o[2], a[3] * o[3]);
	};

	//Vector * float

	vec2 operator*(vec2 a, float o)
	{
		return vec2(a[0] * o, a[1] * o);
	};

	vec3 operator*(vec3 a, float o)
	{
		return vec3(a[0] * o, a[1] * o, a[2] * o);
	};

	vec4 operator*(vec4 a, float o)
	{
		return vec4(a[0] * o, a[1] * o, a[2] * o, a[3] * o);
	};

	///---		DIVISION     ---///

	//vector /=
	void operator/=(vec2& a, vec2 o) {
		a = a / o;
	}

	void operator/=(vec3& a, vec3 o) {
		a = a / o;
	}

	void operator/=(vec4& a, vec4 o) {
		a = a / o;
	}

	//vector /=
	void operator/=(vec2& a, float o) {
		a = a / o;
	}

	void operator/=(vec3& a, float o) {
		a = a / o;
	}

	void operator/=(vec4& a, float o) {
		a = a / o;
	}

	//vector / vector
	vec2 operator/(vec2 a, vec2 o)
	{
		return vec2(a[0] / o[0], a[1] / o[1]);
	};

	vec3 operator/(vec3 a, vec3 o)
	{
		return vec3(a[0] / o[0], a[1] / o[1], a[2] / o[2]);
	};

	vec4 operator/(vec4 a, vec4 o)
	{
		return vec4(a[0] / o[0], a[1] / o[1], a[2] / o[2], a[3] / o[3]);
	};

	//Vector / float

	vec2 operator/(vec2 a, float o)
	{
		return vec2(a[0] / o, a[1] / o);
	};

	vec3 operator/(vec3 a, float o)
	{
		return vec3(a[0] / o, a[1] / o, a[2] / o);
	};

	vec4 operator/(vec4 a, float o)
	{
		return vec4(a[0] / o, a[1] / o, a[2] / o, a[3] / o);
	};

}
