/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

/**
  * gettimeofday
 */
#if defined (_WIN32)
struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

extern int gettimeofday(struct timeval *, struct timezone *);

#endif

extern double gettickcount();


