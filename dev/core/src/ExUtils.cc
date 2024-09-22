/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

 /**
 @file
 */

#include <BaseSpecs.hpp>

size_t zka_strlen(const char* buffer)
{
	if (!buffer) return 0;
	if (*buffer == ZKA_END_OF_BUFFER) return 0;

	size_t index = 0;
	while (buffer[index] != ZKA_END_OF_BUFFER) ++index;

	return index;
}
