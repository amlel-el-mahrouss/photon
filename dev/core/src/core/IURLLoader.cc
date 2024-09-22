/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

/// @file IURLLoader.cc

#include <IURLLoader.hpp>

namespace ZKA
{
	constexpr size_t ZKA_MAX_BUF = 1000000000;

	String IURLLoader::put(Utils::URIParser& url, String data, bool cache_data)
	{
		return ZKA_EMPTY_HTML;
	}

	String IURLLoader::del(Utils::URIParser& url, String data, bool cache_data)
	{
		return ZKA_EMPTY_HTML;
	}

	String IURLLoader::post(Utils::URIParser& url, String data, bool cache_data)
	{
		HTTP::HTTPWriter http_post(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			return ZKA_EMPTY_HTML;
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			return ZKA_EMPTY_HTML;
		}

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_POST, data.size(), {}, data);

		auto sock = http_post.create_and_connect(mEndpoint);

		if (!sock)
			return ZKA_EMPTY_HTML;

		if (!http_post.send_from_socket(sock, http_request.c_str(), http_request.size()))
			return ZKA_EMPTY_HTML;

		return ZKA_EMPTY_HTML;
	}

	String IURLLoader::get(Utils::URIParser& url, bool cache_data)
	{
		HTTP::HTTPWriter http_probe(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			return ZKA_EMPTY_HTML;
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			return ZKA_EMPTY_HTML;
		}

		std::vector<std::pair<std::string, std::string>> headers;

		if (!cache_data)
		{
			headers.push_back({"Pragma", "no-cache"});
			headers.push_back({"Cache-Control", "no-cache"});
		}

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_GET, 0, headers);

		auto sock = http_probe.create_and_connect(mEndpoint);

		if (!sock)
			return ZKA_EMPTY_HTML;

		if (!http_probe.send_from_socket(sock, http_request.c_str(), http_request.size()))
			return ZKA_EMPTY_HTML;

		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			http_probe.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			String result = bytes;

			http_probe.close_socket();

			delete[] bytes;
			bytes = nullptr;

			return result;
		}

		return ZKA_EMPTY_HTML;
	}

	void IURLLoader::set_endpoint(const String& endpoint) noexcept
	{
		if (!endpoint.empty())
			mEndpoint = endpoint;
	}

	String IURLLoader::get_endpoint() noexcept
	{
		return mEndpoint;
	}

	String IURLLoader::get_protocol() noexcept
	{
		return ZKA_URL_PROTO;
	}
} // namespace ZKA
