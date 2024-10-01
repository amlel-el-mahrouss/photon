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

	ZKA_INIT_COM;

	std::atexit([]() -> void {
		ZKA::fini_winsock();
		ZKA_FINI_COM;
	});
#endif

    return 0;
}
