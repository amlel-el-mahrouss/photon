/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <BaseSpecs.hpp>
#include <Socket.hpp>

// OpenSSL headers.
#include <cstddef>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>

#define ZKA_HTTP_VER 1.1

#define ZKA_USE_HTTPS 443
#define ZKA_USE_HTTP  80

namespace ZKA::HTTP
{
	inline int16_t ZKA_HTTP_PORT = ZKA_USE_HTTPS;

	class MIMEFactory;
	class IHTTPHelper;
	class HTTPWriter;
	class HTTPError;

	class MIMEFactory final
	{
	public:
		struct MIME final
		{
			std::string t_name;
			std::string t_mime;
		};

	public:
		MIMEFactory()  = default;
		~MIMEFactory() = default;

		MIMEFactory& operator=(const MIMEFactory&) = default;
		MIMEFactory(const MIMEFactory&)			   = default;

	public:
		MIMEFactory::MIME operator()(char* name)
		{
			if (!name ||
				!strchr(name, '.'))
				return {.t_name = "N/A", .t_mime = "*/*"};

			std::string extension = strchr(name, '.');

			if (strstr(extension.c_str(), ".png"))
				return {.t_name = "PNG Image", .t_mime = "image/png"};
			else if (strstr(extension.c_str(), ".html"))
				return {.t_name = "HTML Document", .t_mime = "text/html"};
			else if (strstr(extension.c_str(), ".bmp"))
				return {.t_name = "BMP Image", .t_mime = "image/bmp"};
			else if (strstr(extension.c_str(), ".webp"))
				return {.t_name = "WEBP Image", .t_mime = "image/webp"};
			else if (strstr(extension.c_str(), ".exe"))
				return {.t_name = "Microsoft Portable Executable", .t_mime = "application/vnd.microsoft.executable"};
			else if (strstr(extension.c_str(), ".pef"))
				return {.t_name = "ZKA Preferred Executable Format", .t_mime = "application/vnd.zka.executable"};
			else if (strstr(extension.c_str(), ".jpg"))
				return {.t_name = "JPEG Image", .t_mime = "image/jpeg"};
			else if (strstr(extension.c_str(), ".zip"))
				return {.t_name = "PKZIP", .t_mime = "application/zip"};

			return {.t_name = "N/A", .t_mime = "*/y"};
		}
	};

	namespace HTTP
	{
		class HTTPSocket final
		{
			struct sockaddr_in m_Addr
			{
				0
			};
			std::string		 m_Dns{""};
			Network::CSocket m_Socket{INVALID_SOCKET};

			friend HTTPWriter;

		public:
			HTTPSocket()  = default;
			~HTTPSocket() = default;

			HTTPSocket& operator=(const HTTPSocket&) = default;
			HTTPSocket(const HTTPSocket&)			 = default;
		};

		enum class RequestType : uint8_t
		{
			GET,
			POST,
			PUT,
			DEL,
		};

		struct HTTPHeader final
		{
			RequestType Type{RequestType::GET};
			String		Bytes{};
		};

	} // namespace HTTP

	enum HTTP_ERROR_LIST : int16_t
	{
		HTTP_OK				= 200,
		HTTP_BAD_GATEWAY	= 502,
		HTTP_NOT_FOUND		= 404,
		HTTP_BAD_REQ		= 403,
		HTTP_DNS_ERROR		= -1,
		HTTP_INTERNAL_ERROR = -2,
		HTTP_ERROR_COUNT	= 6,
	};

	class HTTPError final : public std::runtime_error
	{
	public:
		explicit HTTPError(const std::uint16_t what)
			: std::runtime_error("HTTP_RESULT_")
		{
		}
		~HTTPError() override = default; // let the ABI define that.

		HTTPError& operator=(const HTTPError&) = default;
		HTTPError(const HTTPError&)			   = default;

		Int32 error() const
		{
			return mError;
		}

		std::string as_string() noexcept
		{
			std::string base = this->what();
			base += std::to_string(mError);

			return base;
		}

	private:
		int mError{200};
	};

	inline std::string ZKA_HTTP_GET	   = "GET";
	inline std::string ZKA_HTTP_POST   = "POST";
	inline std::string ZKA_HTTP_PUT	   = "PUT";
	inline std::string ZKA_HTTP_DELETE = "DELETE";

	class ZKA_API IHTTPHelper final
	{
	public:
		static std::string form_request(const std::string								 path,
										const std::string								 host,
										const std::string								 request_type,
										const size_t									 length	 = 0,
										std::vector<std::pair<std::string, std::string>> headers = {}, String data = "")
		{
			if (path.empty() || host.empty())
				throw BrowserError("ILL_FORMED_PACKET");

			ZKA_INFO("Forming packet...");

			std::string request = request_type;

			request += " ";
			request += path;
			request += " HTTP/1.1\r\n";
			request += "Host: ";
			request += host;
			request += "\r\n";
			request += "User-Agent: Photon/1.0\r\n";

			MIMEFactory factory;
			auto		mime_struct = factory(const_cast<char*>(path.data()));

			if (length > 0 && request_type != ZKA_HTTP_GET)
			{
				request += "Content-Length: ";
				request += std::to_string(length);
				request += "\r\n";
			}

			request += "Accept: ";
			request += mime_struct.t_mime;
			request += "\r\n";

			for (const auto& header : headers)
			{
				request += header.first;
				request += ": ";
				request += header.second;
				request += "\r\n";
			}

			request += "Connection: keep-alive\r\n";
			request += "\r\n";

			if (data.size() > 0 && request_type == ZKA_HTTP_POST)
			{
				request += data;
			}


			ZKA_INFO("Packet created...");

			ZKA_INFO(request.c_str());

			return request;
		}

		static bool has_field(const std::string& http, const std::string& rest)
		{
			if (http.empty())
				return false;

			if (rest.empty())
				throw std::runtime_error("Bad restrict type.");

			return http.find(rest) != std::string::npos;
		}

		template <int Base>
		static long content_length(const std::string& http)
		{
			size_t at = http.find("Content-Length: ");

			if (at == std::string::npos)
				return IHTTPHelper::bad_pos;

			std::string final;

			at += strlen("Content-Length: ");

			for (size_t first = at; first < http.size(); ++first)
			{
				if (http[first] == '\r')
					break;

				if (http[first] >= '0' && http[first] <= '9')
				{
					final += http[first];
				}
			}

			std::cout << final << std::endl;

			return std::atol(final.c_str());
		}

		static const int bad_pos = 0;
	};

	using HTTPSharedPtr = std::shared_ptr<HTTP::HTTPSocket>;

	class HTTPWriter final
	{
	public:
		explicit HTTPWriter(bool use_https)
		{
			if (!use_https)
				return;

			m_SslCtx = _init_ssl();
			m_Ssl	 = SSL_new(m_SslCtx);

			// in case the SSL context fails
			if (m_Ssl == nullptr)
			{
				fprintf(stderr, "SSL_new() failed\n");

				throw BrowserError("Bad SSL context, SSL_new() failed!");
			}

			ZKA_WARN("Init HTTPS context.");
		}

		~HTTPWriter() = default;

	public:
		HTTPWriter& operator=(const HTTPWriter&) = default;
		HTTPWriter(const HTTPWriter&)			 = default;

	public:
		HTTPSharedPtr create_and_connect(const std::string dns)
		{
			if (dns.empty())
				throw HTTPError(HTTP_DNS_ERROR);

			ZKA_INFO("Creating HTTPSharedPtr...");

			HTTPSharedPtr sock = std::make_unique<HTTP::HTTPSocket>();

			if (!sock)
				throw HTTPError(HTTP_INTERNAL_ERROR);

			ZKA_INFO("Creating Socket...");

			sock->m_Socket = ::ZKA_SOCKET(AF_INET, SOCK_STREAM, 0);

			if (sock->m_Socket == INVALID_SOCKET)
				throw HTTPError(HTTP_INTERNAL_ERROR);

			ZeroMemory(&sock->m_Addr, sizeof(struct sockaddr_in));

			sock->m_Addr.sin_family = AF_INET;

			sock->m_Addr.sin_addr.s_addr = inet_addr(dns.c_str());
			sock->m_Addr.sin_port		 = htons(ZKA_HTTP_PORT);

			ZKA_INFO("Connecting...");

			if (sock->m_Addr.sin_addr.s_addr == INADDR_NONE)
			{
				struct hostent* host = gethostbyname(dns.c_str());

				if (!host)
				{
					ZKA_CLOSE(sock->m_Socket);

					ZKA_INFO("Invalid hostname! returning nullptr...");
					ZKA_INFO(dns.c_str());

					throw BrowserError("INVALID_DNS_PROBE_X2");
				}

				sock->m_Addr.sin_addr.s_addr = *((u_long*)host->h_addr);
			}

			sock->m_Dns = std::string{dns.data()};

			int result = ::connect(sock->m_Socket, reinterpret_cast<struct sockaddr*>(&sock->m_Addr), sizeof(sock->m_Addr));

			if (result == SOCKET_ERROR)
			{
				perror("HTTP");
				return nullptr;
			}

			if (ZKA_HTTP_PORT == ZKA_USE_HTTPS)
			{
				SSL_set_fd(m_Ssl, sock->m_Socket);
				auto status = SSL_connect(m_Ssl);

				if (status <= 0)
				{
					return nullptr;
				}

				ZKA_INFO(std::string("Connected with HTTPS encryption: ") + SSL_get_cipher(m_Ssl));

				return sock;
			}
			else
			{
				ZKA_INFO("Connected with HTTP.");
			}

			return sock;
		}

		bool close_socket() noexcept
		{
			if (m_Socket)
			{
				if (ZKA_SHUTDOWN(m_Socket->m_Socket, SD_BOTH) == SOCKET_ERROR)
					ZKA_CLOSE(m_Socket->m_Socket);

				if (m_Ssl)
				{
					SSL_free(m_Ssl);
					SSL_CTX_free(m_SslCtx);
				}

				return true;
			}

			return false;
		}

		bool send_from_socket(HTTPSharedPtr& sock, const char* bytes, size_t len)
		{
			if (!sock ||
				!len ||
				!bytes)
				return false;

			if (ZKA_HTTP_PORT == ZKA_USE_HTTPS)
			{
				return ::SSL_write(m_Ssl, bytes, len) > 0;
			}
			else
			{
				return ::send(sock->m_Socket, bytes, len, 0) > 0;
			}
		}

		int64_t read_from_socket(HTTPSharedPtr& sock, char* bytes, int len)
		{
			if (!sock ||
				!bytes ||
				len < 1)
				return -1;

			if (ZKA_HTTP_PORT == ZKA_USE_HTTPS)
			{
				auto ret = ::SSL_read(m_Ssl, bytes, len);

				bytes[len - 1] = 0;

				if (ret == -1)
				    return false;

				return ret == 1;
			}
			else
			{
				auto ret = ::recv(sock->m_Socket, bytes, len, 0);
				bytes[len - 1] = 0;

				if (ret == -1)
				    return false;

				return ret == 0;
			}
		}

	private:
		SSL_CTX* _init_ssl(void) noexcept
		{
			const SSL_METHOD* method = TLS_client_method(); /* Create new client-method instance */
			SSL_CTX*		  ctx	 = SSL_CTX_new(method);

			if (ctx == nullptr)
			{
				ERR_print_errors_fp(stderr);
				return nullptr;
			}

			return ctx;
		}

	private:
		HTTPSharedPtr m_Socket;
		SSL_CTX*	  m_SslCtx{nullptr};
		SSL*		  m_Ssl{nullptr};
	};
} // namespace ZKA::HTTP
