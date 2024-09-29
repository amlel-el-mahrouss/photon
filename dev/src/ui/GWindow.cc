/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <ui/GWindow.hpp>
#include <core/URL.hpp>

namespace ZKA
{
	int32_t GWindow::run(int argc, char** argv)
	{
		ZKA_INFO("Starting Photon Browser...");

		URL url(argv[1]);
		url /= argv[2];

		std::cout << url.fetch();

		return 0;
	}
} // namespace ZKA
