/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <URL.hpp>
#include <ui/XUL.hpp>



int main(int argc, char* argv[])
{
#ifdef ZKA_WINDOWS
	WSADATA dat{0};
	ZKA::init_winsock(&dat);

	std::atexit(ZKA::fini_winsock);
#endif

	ZKA::Utils::URIParser parser(argv[1]);
	parser /= argv[2];

	std::cout << parser.open();

	return 0;
}
