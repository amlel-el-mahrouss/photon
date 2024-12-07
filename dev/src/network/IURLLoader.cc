/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

/// @file IURLLoader.cc

#include <core/IURLLoader.hpp>

namespace ZKA
{
	constexpr size_t ZKA_MAX_BUF = 1000000000UL;

	String IURLLoader::put(URL& url, String data, bool cache_data)
	{
		HTTP::HTTPWriter http_req(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			throw BrowserError("HTTPS_ON_HTTP");
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			throw BrowserError("HTTP_ON_HTTPS");
		}

		std::vector<std::pair<std::string, std::string>> headers;

		if (!cache_data)
		{
			headers.push_back({"Pragma", "no-cache"});
			headers.push_back({"Cache-Control", "no-cache"});
		}

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_PUT, data.size(), headers, data);

		auto sock = http_req.create_and_connect(mEndpoint);

		if (!sock)
			return ZKA_EMPTY_HTML;

		if (!http_req.send_from_socket(sock, http_request.c_str(), http_request.size()))
			return ZKA_EMPTY_HTML;

		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			http_req.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			String result = bytes;

			http_req.close_socket();

			delete[] bytes;
			bytes = nullptr;

			return result;
		}

		http_req.close_socket();

		return ZKA_EMPTY_HTML;
	}

	String IURLLoader::del(URL& url, String data, bool cache_data)
	{
		HTTP::HTTPWriter http_req(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			throw BrowserError("HTTPS_ON_HTTP");
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			throw BrowserError("HTTP_ON_HTTPS");
		}

		std::vector<std::pair<std::string, std::string>> headers;

		if (!cache_data)
		{
			headers.push_back({"Pragma", "no-cache"});
			headers.push_back({"Cache-Control", "no-cache"});
		}

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_DELETE, data.size(), headers, data);

		auto sock = http_req.create_and_connect(mEndpoint);

		if (!sock)
			return ZKA_EMPTY_HTML;

		if (!http_req.send_from_socket(sock, http_request.c_str(), http_request.size()))
			return ZKA_EMPTY_HTML;

		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			http_req.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			String result = bytes;

			http_req.close_socket();

			delete[] bytes;
			bytes = nullptr;

			return result;
		}

		http_req.close_socket();

		return ZKA_EMPTY_HTML;
	}

	String IURLLoader::post(URL& url, String data, bool cache_data)
	{
		HTTP::HTTPWriter http_req(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			throw BrowserError("HTTPS_ON_HTTP");
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			throw BrowserError("HTTP_ON_HTTPS");
		}

		std::vector<std::pair<std::string, std::string>> headers;

		if (!cache_data)
		{
			headers.push_back({"Pragma", "no-cache"});
			headers.push_back({"Cache-Control", "no-cache"});
		}

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_POST, data.size(), headers, data);

		auto sock = http_req.create_and_connect(mEndpoint);

		if (!sock)
			return ZKA_EMPTY_HTML;

		if (!http_req.send_from_socket(sock, http_request.c_str(), http_request.size()))
			return ZKA_EMPTY_HTML;

		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			http_req.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			String result = bytes;

			http_req.close_socket();

			delete[] bytes;
			bytes = nullptr;

			return result;
		}

		http_req.close_socket();

		return ZKA_EMPTY_HTML;
	}

	String IURLLoader::get(URL& url, bool cache_data)
	{
		HTTP::HTTPWriter http_probe(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			throw BrowserError("HTTPS_ON_HTTP");
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			throw BrowserError("HTTP_ON_HTTPS");
		}

		std::vector<std::pair<std::string, std::string>> headers;

		if (!cache_data)
		{
			headers.push_back({"Pragma", "no-cache"});
			headers.push_back({"Cache-Control", "no-cache"});
		}

		ZKA_INFO("Forming HTTP request...");

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

		http_probe.close_socket();

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
