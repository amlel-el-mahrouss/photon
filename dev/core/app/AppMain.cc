/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <IURLLoader.hpp>

/// <summary>
/// Browser entrypoint, starts before Skia.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char** argv)
{
	ZKA::Utils::URIParser url(argv[1]);
	url /= argv[2];

	url.open_app();

    return 0;
}
