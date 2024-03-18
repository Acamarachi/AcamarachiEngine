#include "vector.hpp"
#include "matrix.hpp"

namespace Acamarachi::Maths
{
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