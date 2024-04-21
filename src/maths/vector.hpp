#pragma once

namespace Acamarachi::Maths
{
	typedef struct vec2
	{
		float data[2];

		//constructor
		vec2(float x, float y) : data{ x,y } {};
		vec2(float x) : data{ x,x } {};
		vec2() : data{ 0.0f,0.0f } {};
		vec2(vec2& o) : data{ o.data[0], o.data[1] } {};
		vec2(const vec2& o) : data{ o.data[0], o.data[1] } {};

		constexpr vec2& operator=(const vec2&) = default;

		//getter with with litteral
		constexpr float x() const { return data[0]; }
		constexpr float y() const { return data[1]; }

		//swizzle
		vec2 operator[](int const arr[2])
		{
			return vec2(data[arr[0]], data[arr[1]]);
		}

		//getter with array position
		float& operator[](int index) 
		{
			return data[index];
		}

		float operator[](int index) const {
			return data[index];
		}

	} vec2;

	typedef struct vec3
	{
		float data[3];

		//constructor
		vec3(float x, float y, float z) : data{ x,y,z } {}
		vec3(float x) : data{ x,x,x } {}
		vec3() : data{ 0.0f,0.0f,0.0f } {}
		vec3(vec3& o) : data{ o.data[0],o.data[1],o.data[2] } {}
		vec3(const vec3& o) : data{ o.data[0],o.data[1],o.data[2] } {}

		constexpr vec3& operator=(const vec3&) = default;

		//vec2 to vec3
		vec3(vec2& o, float z) : data{ o.data[0], o.data[1], z } {}
		vec3(float x, vec2& o) : data{ x, o.data[0], o.data[1] } {}

		constexpr float x() const { return data[0]; }
		constexpr float y() const { return data[1]; }
		constexpr float z() const { return data[2]; }

		//swizzle
		vec3 operator[](int const arr[3])
		{
			return vec3(data[arr[0]], data[arr[1]], data[arr[2]]);
		}

		//getter with array position
		//used to modify the value 
		float& operator[](int index)
		{
			return data[index];
		}

		//used to get the value
		float operator[](int index) const {
			return data[index];
		}

	} vec3;

	typedef struct vec4
	{
		float data[4];

		//constructor
		vec4(float x, float y, float z, float w) : data{ x,y,z,w } {}
		vec4(float x) : data{ x,x,x,x } {}
		vec4() : data{ 0.0f,0.0f,0.0f,0.0f } {}
		vec4(vec4& o) : data{ o.data[0],o.data[1],o.data[2],o.data[3] } {}
		vec4(const vec4& o) : data{ o.data[0],o.data[1],o.data[2],o.data[3] } {}

		//vec2 to vec4
		vec4(vec2& o, float z, float w) : data{ o.data[0], o.data[1], z , w } {}
		vec4(float x, vec2& o, float w) : data{ x , o.data[0], o.data[1], w } {}
		vec4(float x, float y, vec2& o) : data{ x , y , o.data[0], o.data[1]} {}

		//Vec3 to vec4
		vec4(vec3& o, float w) : data{ o.data[0],o.data[1],o.data[2], w } {}
		vec4(float x, vec3& o) : data{ x ,o.data[0],o.data[1],o.data[2] } {}

		constexpr vec4& operator=(const vec4&) = default;

		constexpr float x() const { return data[0]; }
		constexpr float y() const { return data[1]; }
		constexpr float z() const { return data[2]; }
		constexpr float w() const { return data[3]; }

		//swizzle
		vec4 operator[](int const arr[3])
		{
			return vec4(data[arr[0]], data[arr[1]], data[arr[2]], data[arr[3]]);
		}

		//getter with array position
		float& operator[](int index)
		{
			return data[index];
		}

		float operator[](int index) const {
			return data[index];
		}

	} vec4;

	//vector operation

	///---		ADDITION     ---///

	//vector +=
	void operator+=(vec2& a, vec2 o);
	void operator+=(vec3& a, vec3 o);
	void operator+=(vec4& a, vec4 o);

	//vector +=
	void operator+=(vec2& a, float o);
	void operator+=(vec3& a, float o);
	void operator+=(vec4& a, float o);

	//vector + vector
	vec2 operator+(vec2 a, vec2 o);
	vec3 operator+(vec3 a, vec3 o);
	vec4 operator+(vec4 a, vec4 o);

	//Vector + float

	vec2 operator+(vec2 a, float o);
	vec3 operator+(vec3 a, float o);
	vec4 operator+(vec4 a, float o);

	///---		SUBSTRACTION     ---///

	//vector -=
	void operator-=(vec2& a, vec2 o);
	void operator-=(vec3& a, vec3 o);
	void operator-=(vec4& a, vec4 o);

	//vector -=
	void operator-=(vec2& a, float o);
	void operator-=(vec3& a, float o);
	void operator-=(vec4& a, float o);

	//vector - vector
	vec2 operator-(vec2 a, vec2 o);
	vec3 operator-(vec3 a, vec3 o);
	vec4 operator-(vec4 a, vec4 o);

	//Vector - float
	vec2 operator-(vec2 a, float o);
	vec3 operator-(vec3 a, float o);
	vec4 operator-(vec4 a, float o);

	///---		MULTIPLICATION     ---///

	//vector *=
	void operator*=(vec2& a, vec2 o);
	void operator*=(vec3& a, vec3 o);
	void operator*=(vec4& a, vec4 o);

	//vector *=
	void operator*=(vec2& a, float o);
	void operator*=(vec3& a, float o);
	void operator*=(vec4& a, float o);

	//vector * vector
	vec2 operator*(vec2 a, vec2 o);
	vec3 operator*(vec3 a, vec3 o);
	vec4 operator*(vec4 a, vec4 o);

	//Vector * float
	vec2 operator*(vec2 a, float o);
	vec3 operator*(vec3 a, float o);
	vec4 operator*(vec4 a, float o);

	///---		DIVISION     ---///

	//vector /=
	void operator/=(vec2& a, vec2 o);
	void operator/=(vec3& a, vec3 o);
	void operator/=(vec4& a, vec4 o);

	//vector /=
	void operator/=(vec2& a, float o);
	void operator/=(vec3& a, float o);
	void operator/=(vec4& a, float o);

	//vector / vector
	vec2 operator/(vec2 a, vec2 o);
	vec3 operator/(vec3 a, vec3 o);
	vec4 operator/(vec4 a, vec4 o);

	//Vector / float
	vec2 operator/(vec2 a, float o);
	vec3 operator/(vec3 a, float o);
	vec4 operator/(vec4 a, float o);

}
