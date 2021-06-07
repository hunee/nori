/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#if defined (_WIN32)
#include <WinSock.h>
int gettimeofday(struct timeval * val, struct timezone *)
{
    if (val)
    {
        LARGE_INTEGER liTime, liFreq;
        QueryPerformanceFrequency(&liFreq);
        QueryPerformanceCounter(&liTime);
        val->tv_sec = (long)(liTime.QuadPart / liFreq.QuadPart);
        val->tv_usec = (long)(liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0);
    }
    return 0;
}
#endif

#if defined(__APPLE__) || defined(_LINUX)
#include <sys/time.h>
#endif //_LINUX

double gettickcount()
{
    //get the current number of microseconds since january 1st 1970
    timeval ts;
    gettimeofday(&ts,0);
    return (ts.tv_sec * 1000 + (ts.tv_usec / 1000));
}

