/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "vec3.h"

template <typename T>
struct mat4 {
	union
	{
		struct
		{
			T _11, _12, _13, _14;
			T _21, _22, _23, _24;
			T _31, _32, _33, _34;
			T _41, _42, _43, _44;
		};
		struct
		{
			T _x1, _y1, _z1, _w1;
			T _x2, _y2, _z2, _w2;
			T _x3, _y3, _z3, _w3;
			T _x4, _y4, _z4, _w4;
		};
		struct
		{
			T x, y, z, w;
			T x2, y2, z2, w2;
			T x3, y3, z3, w3;
			T x4, y4, z4, w4;
		};
		T m[4][4];		// D3DSDK
	};

	mat4()
	{
		_11 = 1.0f; _12 = _13 = _14 = 0;
		_22 = 1.0f; _21 = _23 = _24 = 0;
		_33 = 1.0f; _31 = _32 = _34 = 0;
		_44 = 1.0f; _41 = _42 = _43 = 0;
	}
	mat4(T f11, T f12, T f13, T f14,
		T f21, T f22, T f23, T f24,
		T f31, T f32, T f33, T f34,
		T f41, T f42, T f43, T f44)
	{
		_11 = f11; _12 = f12; _13 = f13; _14 = f14;
		_21 = f21; _22 = f22; _23 = f23; _24 = f24;
		_31 = f31; _32 = f32; _33 = f33; _34 = f34;
		_41 = f41; _42 = f42; _43 = f43; _44 = f44;
	}

	/// access grants
	T& operator[](int i)
	{
		return (&_11)[i];
	}
	const T& operator[](int i) const
	{
		return (&_11)[i];
	}

	T& operator () (int row, int col)
	{
		return m[row][col];
	}
	const T& operator () (int row, int col) const
	{
		return m[row][col];
	}

	mat4 operator * (const mat4& right) const;


	//
	void identity()
	{
	_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
	_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
	}

//
void translation(const vec3<T>& pos)
{
	_11 = 1.0f;  _12 = 0.0f;  _13 = 0.0f;  _14 = 0.0f;
	_21 = 0.0f;  _22 = 1.0f;  _23 = 0.0f;  _24 = 0.0f;
	_31 = 0.0f;  _32 = 0.0f;  _33 = 1.0f;  _34 = 0.0f;
	_41 = pos.x; _42 = pos.y; _43 = pos.z; _44 = 1.0f;
}
void scaling(const vec3<T>& scale)
{
	_11 = scale.x; _12 = 0.0f;    _13 = 0.0f;    _14 = 0.0f;
	_21 = 0.0f;    _22 = scale.y; _23 = 0.0f;    _24 = 0.0f;
	_31 = 0.0f;    _32 = 0.0f;    _33 = scale.z; _34 = 0.0f;
	_41 = 0.0f;    _42 = 0.0f;    _43 = 0.0f;    _44 = 1.0f;
}

void rotation_x(const T angle)
{
	T _sin = (T) sin(angle);
	T _cos = (T) cos(angle);

	_11 = 1.0f; _12 =  0.0f; _13 = 0.0f; _14 = 0.0f;
	_21 = 0.0f; _22 =  _cos; _23 = _sin; _24 = 0.0f;
	_31 = 0.0f; _32 = -_sin; _33 = _cos; _34 = 0.0f;
	_41 = 0.0f; _42 =  0.0f; _43 = 0.0f; _44 = 1.0f;
}
void rotation_y(const T angle)
{
	T _sin = (T) sin(angle);
	T _cos = (T) cos(angle);

	_11 = _cos; _12 = 0.0f; _13 = -_sin; _14 = 0.0f;
	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f;  _24 = 0.0f;
	_31 = _sin; _32 = 0.0f; _33 = _cos;  _34 = 0.0f;
	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f;  _44 = 1.0f;
}
void rotation_z(const T angle)
{
	T _sin = (T) sin(angle);
	T _cos = (T) cos(angle);

	_11 = _cos;  _12 = _sin; _13 = 0.0f; _14 = 0.0f;
	_21 = -_sin; _22 = _cos; _23 = 0.0f; _24 = 0.0f;
	_31 = 0.0f;  _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
	_41 = 0.0f;  _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
}

void rotation(const T yaw, const T pitch, const T roll)
{
	T cosx = (T) cos(pitch);
	T sinx = (T) sin(pitch);
	T cosy = (T) cos(yaw);
	T siny = (T) sin(yaw);
	T cosz = (T) cos(roll);
	T sinz = (T) sin(roll);

	_11 = cosy * cosz + sinx * siny * sinz;
	_12 = -cosx * sinz;
	_13 = sinx * cosy * sinz - siny * cosz;

	_21 = cosy * sinz - sinx * siny * cosz;
	_22 = cosx * cosz;
	_23 = -siny * sinz - sinx * cosy * cosz;

	_31 = cosx * siny;
	_32 = sinx;
	_33 = cosx * cosy;

	_14 = _24 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
	_44 = 1.0f;
}

void rotation(const vec3<T>& dir, const T radius)
{
	T _cos = (T) cos(radius);
	T _sin = (T) sin(radius);
	vec3<T> v = normalize(dir);

	_11 = (v.x * v.x) * (1.0f - _cos) + _cos;
	_12 = (v.x * v.y) * (1.0f - _cos) - (v.z * _sin);
	_13 = (v.x * v.z) * (1.0f - _cos) + (v.y * _sin);

	_21 = (v.y * v.x) * (1.0f - _cos) + (v.z * _sin);
	_22 = (v.y * v.y) * (1.0f - _cos) + _cos ;
	_23 = (v.y * v.z) * (1.0f - _cos) - (v.x * _sin);

	_31 = (v.z * v.x) * (1.0f - _cos) - (v.y * _sin);
	_32 = (v.z * v.y) * (1.0f - _cos) + (v.x * _sin);
	_33 = (v.z * v.z) * (1.0f - _cos) + _cos;

	_14 = _24 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
	_44 = 1.0f;
}

void translate(const vec3<T>&v)
{
	_14 += (v.x * _11 + v.y * _12 + v.z * _13);
	_24 += (v.x * _21 + v.y * _22 + v.z * _23);
	_34 += (v.x * _31 + v.y * _32 + v.z * _33);
	_44 += (v.x * _41 + v.y * _42 + v.z * _43);
}

void billboard(const vec3<T>& from, const vec3<T>& to, const vec3<T>& up)
{
	vec3<T> z = normalize(from - to);
	vec3<T> y = normalize(up);
	vec3<T> x = (y * z);
	z = x * y;

	_11 = x.x; _12 = x.y; _13 = x.z; _14 = 0.0f;
	_21 = y.x; _22 = y.y; _23 = y.z; _24 = 0.0f;
	_31 = z.x; _32 = z.y; _33 = z.z; _34 = 0.0f;
	_41 = _42 = _43 = 0; /*x.z;*/ _44 = 1.0f;
}


mat4 inverse() const
{
  T m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
  T m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
  T m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
  T m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

  T v0 = m20 * m31 - m21 * m30;
  T v1 = m20 * m32 - m22 * m30;
  T v2 = m20 * m33 - m23 * m30;
  T v3 = m21 * m32 - m22 * m31;
  T v4 = m21 * m33 - m23 * m31;
  T v5 = m22 * m33 - m23 * m32;

  T t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
  T t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
  T t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
  T t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

  T invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

  T d00 = t00 * invDet;
  T d10 = t10 * invDet;
  T d20 = t20 * invDet;
  T d30 = t30 * invDet;

  T d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
  T d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
  T d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
  T d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

  v0 = m10 * m31 - m11 * m30;
  v1 = m10 * m32 - m12 * m30;
  v2 = m10 * m33 - m13 * m30;
  v3 = m11 * m32 - m12 * m31;
  v4 = m11 * m33 - m13 * m31;
  v5 = m12 * m33 - m13 * m32;

  T d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
  T d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
  T d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
  T d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

  v0 = m21 * m10 - m20 * m11;
  v1 = m22 * m10 - m20 * m12;
  v2 = m23 * m10 - m20 * m13;
  v3 = m22 * m11 - m21 * m12;
  v4 = m23 * m11 - m21 * m13;
  v5 = m23 * m12 - m22 * m13;

  T d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
  T d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
  T d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
  T d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

  return mat4(
    d00, d01, d02, d03,
    d10, d11, d12, d13,
    d20, d21, d22, d23,
    d30, d31, d32, d33);
}

	void look_at(const vec3<T>& eye, const vec3<T>& lookAt, const vec3<T>& up)
{
	// normalizing the viewing vector 
	vec3<T> v = normalize(lookAt - eye);

	// normalising the up vector. no need for this here if you have your 
	// up vector already normalised, which is mostly the case. 
	vec3<T> u = normalize(up);
	vec3<T> right = cross_product(v, u); 

	// Here's what the final matrix should look like:
	//
	//  |   rx     ux     lx    0 |
	//  |   ry     uy     ly    0 |
	//  |   rz     uz     lz    0 |
	//  | -(r.e) -(u.e) -(l.e)  1 |
	//
	// Where r = Right vector
	//       u = Up vector
	//       l = Look vector
	//       e = Eye position in world space
	//       . = Dot-product operation

	_11 = right.x;
	_12 = u.x;
	_13 = v.x;
	_14 = 0;

	_21 = right.y;
	_22 = u.y;
	_23 = v.y;
	_24 = 0;

	_31 = right.z;
	_32 = u.z;
	_33 = v.z;
	_34 = 0;

	_41 = -dot_product(right, eye);
	_42 = -dot_product(u, eye);
	_43 = -dot_product(v, eye);
	_44 = 1;
}

void ortho(const T left, const T right, const T bottom, const T top, const T zNear, const T zFar)
{
	// Set up the ortho matrix
	_11 = 2.0f / (right - left);
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = 2.0f / (top - bottom);
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = -2.0f / (zFar - zNear);
	_34 = 0;

	_41 = -(right + left) / (right - left);
	_42 = -(top + bottom) / (top - bottom);
	_43 = -(zFar + zNear) / (zFar - zNear);
	_44 = 1.0f;
}

//cocos2d
void ortho_(const T left, const T right, const T bottom, const T top, const T zNear, const T zFar)
{
	// Set up the ortho matrix
	_11 = 2.0f / (right - left);
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = 2.0f / (top - bottom);
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = 2.0f / (zNear - zFar);
	_34 = 0;

	_41 = (right + left) / (right - left);
	_42 = (top + bottom) / (top - bottom);
	_43 = (zNear + zFar) / (zNear - zFar);
	_44 = 1.0f;

	//// https://metashapes.com/blog/opengl-metal-projection-matrix-problem/
#ifdef USE_METAL
  _33 = 1 / (zNear - zFar);
  _43 = zNear / (zNear - zFar);
#endif

}
void perspective_fovy(const T fovy, const T aspect, const T zNear, const T zFar)
{
	//const T range = tan(TORADIAN(fovy) * 0.5f);
	const T range = tan(TORADIAN(fovy) * 0.5f) * zNear;
	const T left = -range * aspect;
	const T right = range * aspect;
	const T bottom = -range;
	const T top = range;

	// Set up the projection matrix
	_11 = (2.0f * zNear) / (right - left);
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = (2.0f * zNear) / (top - bottom);
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = -(zFar + zNear) / (zFar - zNear);
	_34 = -1.0f;

	_41 = 0;
	_42 = 0;
	_43 = -(2.0f * zFar * zNear) / (zFar - zNear); 
	_44 = 0;
}

};


/**
 * @brief 
 * 
 * @param m2 
 * @return float4x4 
 */
template <typename T>
inline mat4<T> mat4<T>::operator * (const mat4& m2) const
{
	// TODO: instead of full unroll make it partially unrolled
	mat4<T> r;

	r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
	r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
	r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
	r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

	r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
	r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
	r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
	r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

	r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
	r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
	r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
	r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

	r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
	r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
	r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
	r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

	return r;
}

