/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <IURLLoader.hpp>

int main(int argc, char** argv)
{
    ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTPS;

    ZKA::IURLLoader loader;
    loader.set_endpoint("google.com");

    ZKA::Utils::URIParser url(ZKA_HTTPS_PROTOCOL);
    url /= "index.html";

    auto result = loader.get(url);

    return 0;
}
