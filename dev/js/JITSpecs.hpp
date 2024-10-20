/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#ifndef _WIN32

#include <core/BaseSpecs.hpp>
#include <stdarg.h>
#include <sys/mman.h>

namespace ZKA
{
	/// @brief Generic javascript function.
	typedef void (*zka_asm_fn_t)(void* arg, size_t arg_cnt);

	inline int zka_delete_chunk(char* fn, size_t size)
	{
		if (!fn ||
			!size)
			return 1;

		return munmap(fn, size);
	}

	inline zka_asm_fn_t zka_allocate_chunk(char* data, size_t size)
	{
		if (!data ||
			!size)
		{
			throw ZKA::BrowserError("JIT_ARGUMENT_INVALID");
		}

		char* mem_exec = (char*)mmap(NULL, // address
									 4096, // size
									 PROT_READ | PROT_WRITE | PROT_EXEC,
									 MAP_PRIVATE | MAP_ANONYMOUS,
									 -1, // fd (not used here)
									 0); // offset (not used here)

		if (mem_exec == MAP_FAILED)
		{
			throw ZKA::BrowserError("JIT_ERROR_OUT_OF_MEMORY");
			return nullptr;
		}

		memcpy(mem_exec, data, size);

		return (zka_asm_fn_t)mem_exec;
	}
} // namespace ZKA

#endif // !_WIN32
