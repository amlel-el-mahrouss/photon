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
	constexpr int64_t ZKA_MAX_BUF = 1000000;

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

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_POST);

		http_request += "Content-Length: " + std::to_string(data.size());

		http_request += "\r\n\r\n";

		auto http_hdr = HTTP::HTTP::HTTPHeader{
			.Type = HTTP::HTTP::RequestType::POST,
		};

		http_hdr.Bytes += http_request;
		http_hdr.Bytes += data;

		Ref<HTTP::HTTP::HTTPHeader*> http_hdr_wrapper{&http_hdr};

		auto sock = http_post.create_and_connect(mEndpoint);

		if (!sock)
			return ZKA_EMPTY_HTML;

		if (!http_post.send_from_socket(sock, http_hdr_wrapper))
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

		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, HTTP::ZKA_HTTP_GET);
			http_request += "\r\n";

			std::cout << http_request;

			auto http_hdr = HTTP::HTTP::HTTPHeader{
				.Type = HTTP::HTTP::RequestType::GET,
			};

			http_hdr.Bytes = http_request;

			Ref<HTTP::HTTP::HTTPHeader*> http_hdr_wrapper{&http_hdr};

			auto sock = http_probe.create_and_connect(mEndpoint);

			if (!sock)
				return ZKA_EMPTY_HTML;

			if (!http_probe.send_from_socket(sock, http_hdr_wrapper))
				return ZKA_EMPTY_HTML;

			http_probe.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			String bytes_as_string	= bytes;
			String header_as_string = bytes_as_string.substr(0, bytes_as_string.find("\r\n\r\n") + strlen("\r\n\r\n"));

			long len = HTTP::IHTTPHelper::content_length<10>(bytes_as_string);

			delete[] bytes;
			bytes = nullptr;

			if (len < 1)
			{
				throw BrowserError("ERROR_BAD_HTTP_PACKET");
			}

			len += header_as_string.size();

			HTTP::HTTPWriter http_fetch(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

			char* bytes = new char[len];
			ZKA_ASSERT(bytes);

			ZeroMemory(bytes, len);

			auto sock_fetch = http_fetch.create_and_connect(mEndpoint);

			if (!http_fetch.send_from_socket(sock_fetch, http_hdr_wrapper))
				return ZKA_EMPTY_HTML;

			http_fetch.read_from_socket(sock_fetch, bytes, len);
			bytes_as_string = bytes;

			return bytes_as_string;
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
} // namespace ZKA
