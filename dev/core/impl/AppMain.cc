
/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <IURLLoader.hpp>

/// @brief Browser entrypoint.
int main(int argc, char** argv)
{
	ZKA::Utils::URIParser url(argv[1]);
	url /= argv[2];

	std::cout << url.open_app();

    return 0;
}
