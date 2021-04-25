/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#if defined (_WIN32)

#if defined (_MSC_VER)
#pragma comment(lib, "version.lib")
#endif

const TCHAR* getosversion()
{
	static TCHAR strOperatingSystem[MAX_PATH];

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof (OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if (!GetVersionEx((OSVERSIONINFO *) &osvi))
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *) &osvi))
			return NULL;
	}

	switch (osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		// Test for the product.
		if (osvi.dwMajorVersion <= 4)
			lstrcpy(strOperatingSystem, _T("Microsoft Windows NT "));
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			lstrcpy(strOperatingSystem, _T("Microsoft Windows 2000 "));
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
			lstrcpy(strOperatingSystem, _T("Microsoft Windows XP "));
		if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
			lstrcpy(strOperatingSystem, _T("Microsoft Windows Vista "));
		if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
			lstrcpy(strOperatingSystem, _T("Microsoft Windows 7 "));

		// Test for product type.
		HKEY hKey;
		TCHAR szProductType[80];
		DWORD dwSize;
		LONG lResult;

		// Query the registry to retrieve information.
		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			_T("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"),
			0,
			KEY_QUERY_VALUE,
			&hKey);
		if (lResult != ERROR_SUCCESS)
			return NULL;

		lResult = RegQueryValueEx(hKey,
			_T("ProductType"),
			NULL,
			NULL,
			(LPBYTE) szProductType,
			&dwSize);
		RegCloseKey(hKey);

		if (lResult != ERROR_SUCCESS)
			return NULL;

		if (lstrcmpi(_T("WINNT"), szProductType) == 0)
			lstrcat(strOperatingSystem, _T("Professional "));
		if (lstrcmpi(_T("LANMANNT"), szProductType) == 0)
		{
			// Decide between Windows 2000 Advanced Server and Windows .NET Enterprise Server.
			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
				lstrcat(strOperatingSystem, _T("Standard Server "));
			else
				lstrcat(strOperatingSystem, _T("Server "));
		}
		if (lstrcmpi(_T("SERVERNT"), szProductType) == 0)
		{
			// Decide between Windows 2000 Advanced Server and Windows .NET Enterprise Server.
			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
				lstrcat(strOperatingSystem, _T("Enterprise Server "));
			else
				lstrcat(strOperatingSystem, _T("Advanced Server "));
		}

		// Display version, service pack (if any), and build number.
		if (osvi.dwMajorVersion <= 4)
		{
			// NB: NT 4.0 and earlier.
			wsprintf(strOperatingSystem, _T("%sversion %d.%d %s (Build %d)"),
				strOperatingSystem,
				osvi.dwMajorVersion,
				osvi.dwMinorVersion,
				osvi.szCSDVersion,
				osvi.dwBuildNumber & 0xFFFF);
		}
		else if ((osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 ) ||
			(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0))
		{
			// Windows XP and .NET server.
			typedef BOOL (CALLBACK* LPFNPROC)(HANDLE, BOOL *);

			BOOL bIsWindows64Bit;

			// Load the Kernel32 DLL.
			HINSTANCE hKernelDLL = LoadLibraryA("kernel32");
			if (hKernelDLL != NULL)
			{
				// Only XP and .NET Server support IsWOW64Process so... Load dynamically!
				LPFNPROC DLLProc = (LPFNPROC) GetProcAddress(hKernelDLL, "IsWow64Process");

				// If the function address is valid, call the function.
				if (DLLProc != NULL)
					(DLLProc) (GetCurrentProcess(), &bIsWindows64Bit);
				else
					bIsWindows64Bit = false;

				// Free the DLL module.
				FreeLibrary(hKernelDLL);
			}

			// IsWow64Process ();
			if (bIsWindows64Bit)
				lstrcat(strOperatingSystem, _T("64-Bit "));
			else
				lstrcat(strOperatingSystem, _T("32-Bit "));
		}

		//else
		{
			// Windows 2000 and everything else.
			wsprintf(strOperatingSystem, _T("%s%s (Build %d)"),
				strOperatingSystem,
				osvi.szCSDVersion,
				osvi.dwBuildNumber & 0xFFFF);
		}
		break;

	case VER_PLATFORM_WIN32_WINDOWS:
		// Test for the product.
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
		{
			lstrcpy(strOperatingSystem, _T("Microsoft Windows 95 "));
			if (osvi.szCSDVersion[1] == 'C')
				lstrcat(strOperatingSystem, _T("OSR 2.5 "));
			else if (osvi.szCSDVersion[1] == 'B')
				lstrcat(strOperatingSystem, _T("OSR 2 "));
		}

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
		{
			lstrcpy(strOperatingSystem, _T("Microsoft Windows 98 "));
			if (osvi.szCSDVersion[1] == 'A')
				lstrcat(strOperatingSystem, _T("SE "));
		}

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
		{
			lstrcpy(strOperatingSystem, _T("Microsoft Windows Me "));
		}
		break;

	case VER_PLATFORM_WIN32s:
		lstrcpy(strOperatingSystem, _T("Microsoft Win32s "));
		break;

	default:
		lstrcpy(strOperatingSystem, _T("Unknown Windows "));
		break;
	}
	
	return strOperatingSystem;
}

#endif

