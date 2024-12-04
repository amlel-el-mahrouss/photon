/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

/**
@file
*/

#include <core/BaseSpecs.hpp>

static FILE* cFileLogger{nullptr};

FILE* zka_get_logger(void)
{
	return cFileLogger;
}

time_t zka_get_epoch()
{
	time_t curtime = time(nullptr);
	return curtime;
}

void zka_log(const char* msg)
{
#ifdef ZKA_DEBUG
	char buf[sizeof(time_t)];
#ifdef ZKA_WINDOWS
	snprintf(buf, sizeof(time_t), "%llu", zka_get_epoch());
#else
	snprintf(buf, sizeof(time_t), "%lu", zka_get_epoch());
#endif
	fprintf(cFileLogger, "[%s - LOG] %s", buf, msg);
#endif // ifdef ZKA_DEBUG
}

static char gDbgFilename[256] = {0};

ZKA_API bool zka_open_logger()
{
#ifdef ZKA_DEBUG
#ifdef ZKA_WINDOWS
	snprintf(gDbgFilename, sizeof(time_t), "%llu_zka.log", zka_get_epoch());
#else
	snprintf(gDbgFilename, sizeof(time_t), "%lu_zka.log", zka_get_epoch());
#endif
	if (fopen_s(&cFileLogger, gDbgFilename, "w+") != EXIT_SUCCESS)
	{
		ZKA_ASSERT(false);
		::exit(EXIT_FAILURE);

		return false;
	}
#endif // ZKA_DEBUG

	return true;
}
