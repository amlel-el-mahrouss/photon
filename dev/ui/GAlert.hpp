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
			if (!cContext)
				return false;

			cContext->rectangle(this->Width(), this->Height(), this->Radius())
				->move(this->X() + 10, this->Y() + 10)
				->text(message.c_str(), false);

			return true;
		}

		CGReal X() override
		{
			return 100;
		}

		CGReal Y() override
		{
			return 100;
		}

		CGReal Width() override
		{
			return 279;
		}

		CGReal Radius() override
		{
			return 30;
		}

		CGReal Height() override
		{
			return 149;
		}
	};
} // namespace ZKA
