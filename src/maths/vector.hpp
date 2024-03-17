#pragma once

namespace Acamarachi::Maths
{
	typedef struct vec2
	{
		float data[2];

		//constructor
		vec2(float x, float y) : data{ x,y } {};
		vec2() : data{ 0.0f,0.0f } {};
		vec2(vec2& o) : data{ o.data[0], o.data[1] } {};

		//getter with with litteral
		constexpr float x() const { return data[0]; }
		constexpr float y() const { return data[1]; }

		//swizzle
		vec2 operator[](int const arr[2])
		{
			return vec2(data[arr[0]], data[arr[1]]);
		}

		//getter with array position
		float operator[](int pos)
		{
			return data[pos];
		}

	} vec2;

	typedef struct vec3
	{
		float data[3];

		//constructor
		vec3(float x, float y, float z) : data{ x,y,z } {}
		vec3() : data{ 0.0f,0.0f,0.0f } {}
		vec3(vec3& o) : data{ o.data[0],o.data[1],o.data[2] } {}

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
		float operator[](int pos)
		{
			return data[pos];
		}

	} vec3;

	typedef struct vec4
	{
		float data[4];

		//constructor
		vec4(float x, float y, float z, float w) : data{ x,y,z,w } {}
		vec4() : data{ 0.0f,0.0f,0.0f,0.0f } {}
		vec4(vec4& o) : data{ o.data[0],o.data[1],o.data[2],o.data[3] } {}

		//vec2 to vec4
		vec4(vec2& o, float z, float w) : data{ o.data[0], o.data[1], z , w } {}
		vec4(float x, vec2& o, float w) : data{ x , o.data[0], o.data[1], w } {}
		vec4(float x, float y, vec2& o) : data{ x , y , o.data[0], o.data[1]} {}

		//Vec3 to vec4
		vec4(vec3& o, float w) : data{ o.data[0],o.data[1],o.data[2], w } {}
		vec4(float x, vec3& o) : data{ x ,o.data[0],o.data[1],o.data[2] } {}

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
		float operator[](int pos)
		{
			return data[pos];
		}

	} vec4;


}
