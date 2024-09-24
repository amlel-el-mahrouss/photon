/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <BaseSpecs.hpp>

namespace ZKA
{
	class GWindow;

	class ZKA_API GWindow final
	{
	public:
		explicit GWindow() = default;
		~GWindow()		   = default;

		ZKA_COPY_DEFAULT(GWindow);

		int32_t run(int argc, char** argv);
	};
} // namespace ZKA
