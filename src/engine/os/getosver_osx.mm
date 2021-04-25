/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#if defined (__APPLE__)
#if defined (__MAC_OS_X_VERSION_MAX_ALLOWED)

#include <CoreServices/CoreServices.h>
#include <Foundation/NSProcessInfo.h>

const char * getosversion()
{
	static char strOperatingSystem[PATH_MAX];

    NSOperatingSystemVersion version = [[NSProcessInfo processInfo] operatingSystemVersion];
    sprintf(strOperatingSystem, "Apple macOS version %ld.%ld.%ld", version.majorVersion, version.minorVersion, version.patchVersion);
	
	return strOperatingSystem;
}

#endif //__MAC_OS_X_VERSION_MAX_ALLOWED
#endif //__APPLE__

