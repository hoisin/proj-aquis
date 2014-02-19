#pragma once

#ifdef _WIN64
	const int g_targetPlatform = 1;
#else

#ifdef WIN32
	const int g_targetPlatform = 0;;
#endif

#endif