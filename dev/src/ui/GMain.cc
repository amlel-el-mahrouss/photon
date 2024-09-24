/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <URL.hpp>
#include <ui/GWindow.hpp>

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
