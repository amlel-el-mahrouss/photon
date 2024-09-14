/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

 /**
 @file
 */

#include <BaseSpecs.h>

static FILE* g_ZKALogger{ nullptr };

FILE* zka_get_logger(void)
{
	return g_ZKALogger;
}

size_t fstrlen(const char* buffer)
{
	if (!buffer) return 0;
	if (*buffer == ZKA_END_OF_BUFFER) return 0;

	size_t index = 0;
	while (buffer[index] != ZKA_END_OF_BUFFER) ++index;

	return index;
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
	snprintf(buf, sizeof(time_t), "%lu", zka_get_epoch());
	fprintf(g_ZKALogger, "[%s - LOG] %s", buf, msg);
#endif // ifdef ZKA_DEBUG
}

char dbg_filename[256];

bool zka_open_logger()
{
#ifdef ZKA_DEBUG
	snprintf(dbg_filename, 256, "%lu_zka.log", zka_get_epoch());

	if (fopen_s(&g_ZKALogger, dbg_filename, "w+") != EXIT_SUCCESS)
	{
		assert(false);
		exit(EXIT_FAILURE);

		return false;
	}

#endif // ZKA_DEBUG

	return true;
}
