/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <GraphicsKit/GraphicsKit.hxx>
#include <BaseSpecs.hpp>

namespace ZKA
{
	class GWindow;

	inline MLCoreGraphicsContext* cContext = nullptr;

	class ZKA_API GWindow final
	{
	public:
		explicit GWindow() = default;
		~GWindow()		   = default;

		ZKA_COPY_DEFAULT(GWindow);

		int32_t run(int argc, char** argv);
	};

	class ZKA_API GView
	{
	public:
		explicit GView() = default;
		virtual ~GView() = default;

		ZKA_COPY_DEFAULT(GView);

		virtual bool Paint()	   = 0;
		virtual bool ShouldPaint() = 0;
	};
} // namespace ZKA
