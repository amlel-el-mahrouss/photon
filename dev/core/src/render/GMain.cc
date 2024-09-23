/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <URL.hpp>
#include <ui/GLib.hpp>

int main(int argc, char* argv[])
{
#ifdef ZKA_WINDOWS
	WSADATA dat{0};
	ZKA::init_winsock(&dat);

	std::atexit(ZKA::fini_winsock);
#endif



	return 0;
}
