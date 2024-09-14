/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

// @file HTTPDownloadFactory.cc

#include <HTTPDownloadFactory.h>
#include <Macros.h>

namespace ZKA
{
	bool HTTPDownloadFactory::download(const String assetId, const String outputFileName) const noexcept
	{
        HTTP::HTTPWriter http_writer(HTTP::ZKA_HTTP_PORT == ZKA_USE_HTTPS);

        // static is added here wtf??
        // - check the preprocessor value of ZKA_GET_DATA_DIR :)
        ZKA_GET_DATA_DIR(full_path);

        String http_path;

        http_path += full_path;
        http_path += "Tmp/";
        http_path += outputFileName;

        if (std::filesystem::exists(http_path))
        {
            std::filesystem::remove(http_path);
        }

        std::ofstream file = mWriter.write(http_path.c_str());

        constexpr int64_t MAX_BUF = 1000000;

        auto bytes = new char[MAX_BUF];
        ZKA_ASSERT(bytes);

        memset(bytes, 0, MAX_BUF);

        if (bytes)
        {
            auto path = HTTP::HTTPHelpers::make_get(assetId, mEndpoint);

            auto http_hdr = HTTP::HTTP::HTTPHeader{ .Type = HTTP::HTTP::RequestType::GET, .Bytes = "", .Size = static_cast<int>(path.size()),};
            memcpy(http_hdr.Bytes, path.data(), strlen(path.data()));

            Ref<HTTP::HTTP::HTTPHeader*> http_hdr_wrapper{ &http_hdr };

            auto sock = http_writer.create_and_connect(mEndpoint);

            if (!sock)
                return false;

            if (!http_writer.send_from_socket(sock, http_hdr_wrapper))
                return false;

            http_writer.read_from_socket(sock, bytes, MAX_BUF);

            String _bytes = bytes;

            auto valid_header = _bytes.find("\r\n\r\n");

            if (valid_header == String::npos)
            {
                valid_header = _bytes.find("\n\n");
                if (valid_header == String::npos)
                {
                    ZKA_ERROR("[HTTPS] INVALID_HTTP_PACKET.\n");
                    return false;
                }
            }

            if (valid_header != String::npos)
            {
                auto sz = HTTP::HTTPHelpers::content_length<10>(_bytes);

                delete bytes;
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

	void HTTPDownloadFactory::set_endpoint(const String& endpoint) noexcept
	{
		if (!endpoint.empty())
			mEndpoint = endpoint;
	}
}
