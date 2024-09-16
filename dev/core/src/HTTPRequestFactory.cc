/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

// @file HTTPRequestFactory.cc

#include <HTTPRequestFactory.h>
#include <Macros.h>

namespace ZKA
{
	bool HTTPRequestFactory::get_url(const String url, const String output_file_name, const bool cache_data) const
	{
		HTTP::HTTPWriter http_writer(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

		String http_path = this->get_download_dir();

		if (FS::exists(http_path))
		{
			if (cache_data)
				return true;

			FS::remove(http_path);
		}

		std::ofstream file = mWriter.write(http_path.c_str());

		constexpr int64_t ZKA_MAX_BUF = 100000000;
		char* bytes = new char[ZKA_MAX_BUF];
		ZKA_ASSERT(bytes);

		ZeroMemory(bytes, ZKA_MAX_BUF);

		if (bytes)
		{
			auto path = HTTP::IHTTPHelper::make_get(url, mEndpoint, !(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS), HTTP::ZKA_HTTP_GET);

			auto http_hdr = HTTP::HTTP::HTTPHeader{
				.Type  = HTTP::HTTP::RequestType::GET,
				.Bytes = "",
				.Size  = static_cast<int>(path.size()),
			};
			memcpy(http_hdr.Bytes, path.data(), strlen(path.data()));

			Ref<HTTP::HTTP::HTTPHeader*> http_hdr_wrapper{&http_hdr};

			auto sock = http_writer.create_and_connect(mEndpoint);

			if (!sock)
				return false;

			if (!http_writer.send_from_socket(sock, http_hdr_wrapper))
				return false;

			http_writer.read_from_socket(sock, bytes, ZKA_MAX_BUF);

			String _bytes = bytes;

			auto valid_header = _bytes.find("\r\n\r\n");

			if (valid_header == String::npos)
			{
				valid_header = _bytes.find("\n\n");
				if (valid_header == String::npos)
				{
					throw BrowserError("HTTP_INVALID_REQUEST");
					return false;
				}
			}

			if (valid_header != String::npos)
			{
				auto sz = HTTP::IHTTPHelper::content_length<10>(_bytes);

				delete[] bytes;
				bytes = new char[sz];

				auto _sz = http_writer.read_from_socket(sock, bytes, sz);

				while (_sz > 0)
				{
					file.write(bytes, _sz);
					_sz = http_writer.read_from_socket(sock, bytes, sz);
				}

				file.flush();
				file.close();

				delete[] bytes;

				return true;
			}

			delete[] bytes;
		}

		return false;
	}

	String HTTPRequestFactory::get_download_dir() const noexcept
	{
		ZKA_GET_DATA_DIR(full_path);

		String http_path;

		http_path += full_path;
		http_path += ".tmp/";

		return http_path;
	}

	void HTTPRequestFactory::set_endpoint(const String& endpoint) noexcept
	{
		if (!endpoint.empty())
			mEndpoint = endpoint;
	}
} // namespace ZKA
