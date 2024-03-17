#pragma once

#include "vector.hpp"
#include "matrix.hpp"



namespace Acamarachi::Maths
{
	mat2 transpose(mat2 m);
	mat3 transpose(mat3 m);
	mat4 transpose(mat4 m);

	float dot(vec2 x, vec2 y);
	float dot(vec3 x, vec3 y);
	float dot(vec4 x, vec4 y);

	vec3 cross(vec3 x, vec3 y);

	float distance(vec2 p0, vec2 p1);
	float distance(vec3 p0, vec3 p1);
	float distance(vec4 p0, vec4 p1);

	vec2 normalize(vec2 x);
	vec3 normalize(vec3 x);
	vec4 normalize(vec4 x);
}