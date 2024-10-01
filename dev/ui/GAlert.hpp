/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma

#include <ui/GViews.hpp>

namespace ZKA
{
	class ZKA_API GAlert : public GView
	{
	private:
		String message{""};

	public:
		Bool Paint() override
		{
			return true;
		}

		Bool ShouldPaint() override
		{
		    return true;
		}
	};
} // namespace ZKA
