/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

/// @file IURLLoader.cc

#include <IURLLoader.hpp>
#include <Macros.hpp>
#include <string>

namespace ZKA
{
	constexpr int64_t ZKA_MAX_BUF = 1000000;

	String IURLLoader::post(Utils::URIParser& url, String data, bool cache_data)
	{
		HTTP::HTTPWriter http_writer(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			return "";
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			return "";
		}

		auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, !(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS), HTTP::ZKA_HTTP_POST);

		http_request += "Content-Length: " + std::to_string(data.size()) + "\r\n";
		http_request += "\r\n\r\n"; // End HTTP request.

		auto http_hdr = HTTP::HTTP::HTTPHeader{
			.Type = HTTP::HTTP::RequestType::POST,
		};

		for (auto& ch : http_request)
		{
			http_hdr.Bytes.push_back(ch);
		}

		for (auto& ch : data)
		{
			http_hdr.Bytes.push_back(ch);
		}

		Ref<HTTP::HTTP::HTTPHeader*> http_hdr_wrapper{&http_hdr};

		auto sock = http_writer.create_and_connect(mEndpoint);

		if (!sock)
			return "";

		if (!http_writer.send_from_socket(sock, http_hdr_wrapper))
			return "";

		return "";
	}

	String IURLLoader::get(Utils::URIParser& url, String output_as, bool cache_data)
	{
		HTTP::HTTPWriter http_writer(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		if (HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS &&
			url.protocol() != ZKA_HTTPS_PROTOCOL)
		{
			ZKA_WARN("Trying to use HTTPS on a HTTP route.");
			return "";
		}
		else if (HTTP::ZKA_HTTP_PORT != ZKA_USE_HTTPS &&
				 url.protocol() == ZKA_HTTPS_PROTOCOL)
		{
			ZKA_ERROR("Trying to use HTTP on a HTTPS route.");
			return "";
		}

		String http_path = this->get_download_dir();

		if (FS::exists(http_path))
		{
			http_path += output_as;

			if (cache_data)
			{
				ZKA_INFO("Getting previously downloaded page...\n");

				std::stringstream ss;
				ss << std::ifstream(http_path).rdbuf();

				return ss.str();
			}

			FS::remove(http_path);
		}

		std::ofstream file = mWriter.write(http_path.c_str());

		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			auto http_request = HTTP::IHTTPHelper::form_request(url.get(), mEndpoint, !(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS), HTTP::ZKA_HTTP_GET);
			http_request += "\r\n\r\n"; // End HTTP request.

			auto http_hdr = HTTP::HTTP::HTTPHeader{
				.Type = HTTP::HTTP::RequestType::GET,
			};

			for (auto& ch : http_request)
			{
				http_hdr.Bytes.push_back(ch);
			}

			Ref<HTTP::HTTP::HTTPHeader*> http_hdr_wrapper{&http_hdr};

			auto sock = http_writer.create_and_connect(mEndpoint);

			if (!sock)
				return "";

			if (!http_writer.send_from_socket(sock, http_hdr_wrapper))
				return "";

			ZKA_INFO("Reading HTTP data...");

			http_writer.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			ZKA_INFO("Reading HTTP data (assign to String)...");

			String bytes_as_string = bytes;

			ZKA_INFO("Analyzing HTTP header...");
			ZKA_INFO(bytes_as_string);

			auto valid_header = bytes_as_string.find("\r\n\r\n");

			if (valid_header == String::npos)
			{
				valid_header = bytes_as_string.find("\n\n");
				if (valid_header == String::npos)
				{
					throw BrowserError("HTTP_INVALID_REQUEST");
					return "";
				}
			}

			if (valid_header != String::npos)
			{
				auto sz = HTTP::IHTTPHelper::content_length<10>(bytes_as_string);

				ZKA_INFO("Writing down HTTP body...");

				char* bytes_out = new char[sz];
				ZKA_ASSERT(bytes_out);

				http_writer.read_from_socket(sock, bytes_out, sz);

				file.write(bytes_out, sz);
				file.flush();

				bytes_as_string = bytes_out;

				delete[] bytes_out;
				delete[] bytes;

				return bytes_as_string;
			}

			delete[] bytes;
		}

		return "";
	}

	String IURLLoader::get_download_dir() const noexcept
	{
		ZKA_GET_DATA_DIR(full_path);

		String http_path;

		http_path += full_path;
		http_path += ".tmp/";

		return http_path;
	}

	void IURLLoader::set_endpoint(const String& endpoint) noexcept
	{
		if (!endpoint.empty())
			mEndpoint = endpoint;
	}
} // namespace ZKA
