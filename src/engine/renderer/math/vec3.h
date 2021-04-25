/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

template <typename T>
struct vec3 {
	T x, y, z;

	/// Constructors
	vec3()
	{
		x = y = z = 0;
	}
	vec3(T f)
	{
		x = y = z = f;
	}
	vec3(T _x, T _y, T _z)
	{
		x = _x; y = _y; z = _z;
	}
	vec3(const T f[3])
	{
		x = f[0]; y = f[1]; z = f[2];
	}

	/// access grants
	const T& operator[](int i) const
	{
		return (&x)[i];
	}
	T& operator[](int i)
	{
		return (&x)[i];
	}

	/// assignment operators
	vec3& operator += (const vec3& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	vec3& operator -= (const vec3& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	vec3& operator *= (const vec3& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}
	vec3& operator /= (const vec3& v)
	{
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}
	vec3& operator *= (float s)
	{
		x *= s; y *= s; z *= s;
		return *this;
	}
	vec3& operator /= (float s)
	{
		x /= s; y /= s; z /= s;
		return *this;
	}
};

/// Unary operators
template <typename T>
inline vec3<T> operator + (const vec3<T>& v)
{
	return v;
}
template <typename T>
inline vec3<T> operator - (const vec3<T>& v)
{
	return vec3<T>(-v.x, -v.y, -v.z);
}


/// Addition and subtraction
template <typename T>
inline vec3<T> operator + (const vec3<T>& v1, const vec3<T>& v2)
{
	return vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
template <typename T>
inline vec3<T> operator - (const vec3<T>& v1, const vec3<T>& v2)
{
	return vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/// Memberwise multiplication and division
template <typename T>
inline vec3<T> operator * (const vec3<T>& v1, const vec3<T>& v2)
{
	return vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
template <typename T>
inline vec3<T> operator / (const vec3<T>& v1, const vec3<T>& v2)
{
	return vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

/// Vector dominance
template <typename T>
inline int operator < (const vec3<T>& v1, const vec3<T>& v2)
{
	return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}
template <typename T>
inline int operator <= (const vec3<T>& v1, const vec3<T>& v2)
{
	return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;
}

/// Scalar multiplication and division
template <typename T>
inline vec3<T> operator * (const vec3<T>& v, T s)
{
	return vec3(s * v.x, s * v.y, s * v.z);
}
template <typename T>
inline vec3<T> operator * (T s, const vec3<T>& v)
{
	return vec3(s * v.x, s * v.y, s * v.z);
}
template <typename T>
inline vec3<T> operator / (const vec3<T>& v, T s)
{
	return vec3(v.x / s, v.y / s, v.z / s);
}

/// Bitwise equality
template <typename T>
inline int operator == (const vec3<T>& v1, const vec3<T>& v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

/// Return memberwise min/max of input vectors
template <typename T>
inline vec3<T> minimize(const vec3<T>& v1, const vec3<T>& v2)
{
	return vec3(v1.x < v2.x ? v1.x : v2.x,
		v1.y < v2.y ? v1.y : v2.y,
		v1.z < v2.z ? v1.z : v2.z);
}
template <typename T>
inline vec3<T> maximize(const vec3<T>& v1, const vec3<T>& v2)
{
	return vec3(v1.x > v2.x ? v1.x : v2.x,
		v1.y > v2.y ? v1.y : v2.y,
		v1.z > v2.z ? v1.z : v2.z);
}

/// Returns vector with same direction and unit length
template <typename T>
inline vec3<T> normalize(const vec3<T>& v)
{
	float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (mag != 0)
		return v / mag;

	return v;
}

/// Dot and cross product
template <typename T>
inline vec3<T> cross_product(const vec3<T>& v1, const vec3<T>& v2)
{
	vec3<T> result;
	result.x = v1.y * v2.z - v2.y * v1.z;
	result.y = v2.x * v1.z - v1.x * v2.z;
	result.z = v1.x * v2.y - v2.x * v1.y;

	return result;
}

template <typename T>
inline T dot_product(const vec3<T>& v1, const vec3<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}



