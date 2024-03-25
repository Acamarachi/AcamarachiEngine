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

	float length(vec2 v);
	float length(vec3 v);
	float length(vec4 v);

	vec2 normalize(vec2 x);
	vec3 normalize(vec3 x);
	vec4 normalize(vec4 x);

	mat2 inverse(mat2 m);
	mat3 inverse(mat3 m);
	mat4 inverse(mat4 m);

	float determinant(mat2 m);
	float determinant(mat3 m);
	float determinant(mat4 m);
}