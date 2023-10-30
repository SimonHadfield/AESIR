#pragma once

#ifdef HA_PLATFORM_WINDOWS
	#ifdef HA_BUILD_DLL	
		#define	HANA_API __declspec(dllexport)
	#else
		#define	HANA_API __declspec(dllimport)
	#endif
#else
	#error Hana only supports Windows
#endif

#define BIT(x) (1 << x)