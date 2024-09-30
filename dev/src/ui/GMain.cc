/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <core/URL.hpp>
#include <ui/GViews.hpp>

int main(int argc, char* argv[])
{
#ifdef ZKA_WINDOWS
	WSADATA dat{0};
	ZKA::init_winsock(&dat);

	std::atexit(ZKA::fini_winsock);
#endif

	ZKA::GWindow win;

	return win.run(argc, argv);
}
