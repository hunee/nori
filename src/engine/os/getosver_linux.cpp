/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#if defined (_LINUX)
const char* getosversion()
{
	static char strOperatingSystem[MAX_PATH];

	int vidModeMajorVersion, vidModeMinorVersion;
	XF86VidModeQueryVersion(, &vidModeMajorVersion, &vidModeMinorVersion);
	sprintf("Linux/X11 version %d %d\n", vidModeMajorVersion, vidModeMinorVersion);

	return strOperatingSystem;
}
#endif

