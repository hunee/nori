/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


template <typename T>
struct vec4 {
	union {
		struct {
			T x, y;
			
			union {
				struct {
					T z, w;
				};
				struct {
					T width, height;
				};
			};
		};
		struct {
  		vec2<T> origin;
  		vec2<T> size;
		};
		struct {
			T left, top, right, bottom;
		};
	};


	///
	vec4()
	{
		x = y = z = w = 0;
	}
	vec4(int _x, int _y, int _z, int _w)
	{
		x = _x; y = _y; z = _z; w = _w;
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
};

