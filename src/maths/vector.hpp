#pragma once


namespace Acamarachi::Maths
{



	typedef struct vec2
	{
		float x;
		float y;

		//constructor
		vec2(float x, float y) : x(x), y(y) {};
		vec2() : x(0), y(0) {}
		vec2(vec2& o) : x(o.x), y(o.y) {}

	} vec2;

	typedef struct vec3
	{
		float x;
		float y;
		float z;

		//constructor
		vec3(float x, float y, float z) : x(x), y(y), z(z) {}
		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(vec3& o) : x(o.x), y(o.y), z(o.z) {}

		//vec2 to vec3
		vec3(vec2& o, float z) : x(o.x), y(o.y), z(z) {}
		vec3(float x, vec2& o) : x(x), y(o.x), z(o.y) {}

	} vec3;

	typedef struct vec4
	{
		float x;
		float y;
		float z;
		float w;

		//constructor
		vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		vec4(vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}

		//vec2 to vec4
		vec4(vec2& o, float z, float w) : x(o.x), y(o.y), z(z), w(w) {}
		vec4(float x, vec2& o, float w) : x(x), y(o.x), z(o.y), w(w) {}
		vec4(float x, float y, vec2& o) : x(x), y(y), z(o.x), w(o.y) {}

		//Vec3 to vec4
		vec4(vec3& o, float w) : x(o.x), y(o.y), z(o.z), w(w) {}
		vec4(float x, vec3& o) : x(x), y(o.x), z(o.y), w(o.x) {}

	} vec4;


}
