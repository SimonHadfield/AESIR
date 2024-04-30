#pragma once

#ifdef AE_PLATFORM_WINDOWS
	#ifdef AE_BUILD_DLL	
		#define	AESIR_API __declspec(dllexport)
	#else
		#define	AESIR_API __declspec(dllimport)
	#endif
#else
	#error Aesir only supports Windows
#endif

#define BIT(x) (1 << x)