/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include <math.h>

#if !defined (M_PI)
#define M_PI    (3.14159265358979323846f)
#endif //M_PI

#if !defined (M_PIBY4)
#define M_PIBY4    (3.14159265358979323846f / 4)
#endif //M_PI

#if !defined (M_1BYPI)
#define M_1BYPI (1.0f / M_PI)
#endif //M_1BYPI

#if !defined (TORADIAN)
#define TORADIAN(degree) ((degree) * (M_PI / 180.0f))
#endif //TORADIAN

#if !defined (TODEGREE)
#define TODEGREE(radian) ((radian) * (180.0f / M_PI))
#endif //TODEGREE

////
template<class _Gen>
float fast_generate_canonical(_Gen& _Gx)
{
    // 공용체를 이용해 정수 u를 수정하면 
    // 부동소수점 f도 수정되도록 해보겠습니다.
    union
    {
        float f;
        uint32_t u;
    };
 
    // 먼저 랜덤 비트를 잔뜩 생성합니다.
    u = _Gx();
    // 하위 23비트만 그대로 남기고
    // 지수부는 127로 설정합니다.
    u = (127 << 23) | (u & 0x7FFFFF);
    // f에서 1을 빼면 원하는 범위인 [0, 1)의 난수가 생성됩니다.
    return f - 1;
}

/**
 * @brief 
 * 
 */
namespace GL {

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "quat.h"

#include "mat4.h"

///
using int2 = vec2<int>;
using int4 = vec4<int>;

using float2 = vec2<float>;
using float3 = vec3<float>;
using float4 = vec4<float>;


///
using point = int2;
using rect = int4;

using size = vec2<size_t>;

using float3x3 = mat4<int>;

using float4x4 = mat4<float>;
using transform = float4x4;

};//GL

