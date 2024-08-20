/*
 * =====================================================================
 *
 *			webdll
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

 /**
 @file
 */

#include "WebCore.h"

static FILE* ZKA_LOGGER{ nullptr };

ZKA_API FILE* zka_get_logger(void)
{
	return ZKA_LOGGER;
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
	snprintf(buf, sizeof(time_t), "%llu", zka_get_epoch());
	fprintf(ZKA_LOGGER, "[%s - LOG] %s", buf, msg);
#endif // ifdef ZKA_DEBUG
}

char dbg_filename[256];

bool zka_open_logger()
{
#ifdef ZKA_DEBUG
	snprintf(dbg_filename, 256, "%llu_xplicit.log", zka_get_epoch());

	if (fopen_s(&ZKA_LOGGER, dbg_filename, "w+") != EXIT_SUCCESS)
	{
		assert(false);
		exit(EXIT_FAILURE);

		return false;
	}

#endif // !NDEBUG

	return true;
}
