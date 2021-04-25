/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#if defined (__APPLE__)
#if defined (__IPHONE_OS_VERSION_MAX_ALLOWED)

#import <UIKit/UIDevice.h>

const char* getosversion()
{
	static char strOperatingSystem[PATH_MAX];

	UIDevice* device = [UIDevice currentDevice];
	const char* model = [[device model] cStringUsingEncoding:NSASCIIStringEncoding];
	const char* systemName = [[device systemName] cStringUsingEncoding:NSASCIIStringEncoding];
	const char* systemVersion = [[device systemVersion] cStringUsingEncoding:NSASCIIStringEncoding];

	sprintf(strOperatingSystem, "Apple %s (%s) version %s\n", systemName, model, systemVersion);
		
	return strOperatingSystem;
}

#endif //__IPHONE_OS_VERSION_MAX_ALLOWED
#endif //__APPLE__

