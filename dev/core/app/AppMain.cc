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
	ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTP;
	ZKA::Utils::URIParser url(ZKA_HTTP_PROTOCOL);
	url /= "www.perdu.com/index.html";

	url.open_app();

    return 0;
}
