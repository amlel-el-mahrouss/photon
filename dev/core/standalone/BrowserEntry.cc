#include <IURLLoader.hpp>

int main()
{
    ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTPS;

    ZKA::IURLLoader loader;
    loader.set_endpoint("w3.org");

    ZKA::Utils::URIParser url(ZKA_HTTPS_PROTOCOL);

    auto result = loader.get(url, "index-w3c.html");

    std::cout << result << std::endl;
    return 0;
}
