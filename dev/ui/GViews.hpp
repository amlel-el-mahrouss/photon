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

	class ZKA_API GWindow
	{
	public:
		explicit GWindow() = default;
		virtual ~GWindow() = default;

		ZKA_COPY_DEFAULT(GWindow);

		virtual Int32 run(int argc, char** argv) = 0;
	};

	class ZKA_API GView
	{
	public:
		explicit GView() = default;
		virtual ~GView() = default;

		ZKA_COPY_DEFAULT(GView);

		virtual void OnPaint()	   = 0;
		virtual Bool ShouldPaint() = 0;
	};
} // namespace ZKA
