/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


template <typename T>
struct vec2 {
	union
	{
		struct
		{
			T x, y;
		};
		struct
		{
			T width, height;
		};
	};

	//
	vec2()
	{
		x = y = 0;
	}
	vec2(T _x, T _y)
	{
		x = _x; y = _y;
	}
	vec2(const T v[2])
	{
		x = v[0]; y = v[1];
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
