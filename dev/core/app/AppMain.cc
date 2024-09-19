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
	ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTPS;
	ZKA::Utils::URIParser url(ZKA_HTTPS_PROTOCOL);
	ZKA::IURLLoader loader;

	loader.set_endpoint("google.com");

	auto http_object = loader.get(url);

    return 0;
}
