/*
 * =====================================================================
 *
 *			webdll
 *			Copyright ZKA Technologies, all rights reserved.
 *
 *			File: Uri.cpp
 *			Purpose: Xplicit URI parser
 *
 * =====================================================================
 */

/**
@file
*/

#include <URI.h>
#include <HTTPDownloadFactory.h>

#ifndef URI_MAXSIZE
#define URI_MAXSIZE (8196)
#endif // URI_MAXSIZE

#ifndef URI_SEPARATOR
#define URI_SEPARATOR '\a'
#endif // URI_SEPARATOR

namespace ZKA::Utils
{
	UriParser::UriParser(const char* protocol)
	{
		for (std::size_t i = 0; i < strlen(protocol); i++)
		{
			if (protocol[i] == ':')
				break;

			m_protocol += protocol[i];
		}
	}

	UriParser::~UriParser() = default;

	std::string UriParser::get() noexcept
	{
		std::string uri;

		for (size_t i = 0; i < m_data.size(); i++)
		{
			if (m_data[i] == URI_SEPARATOR)
				continue;

			uri.push_back(m_data[i]);
		}

		uri += '\0';

		return uri;
	}

	UriParser& UriParser::operator/=(const std::string& uri)
	{
		this->operator/=(uri.c_str());

		return *this;
	}

	UriParser& UriParser::operator/=(const char* uri)
	{
		if (!uri ||
			*uri == 0)
			return *this;

		std::string uri_str = uri;

		if (strstr(uri, m_protocol.c_str()))
			return *this;

		for (size_t i = 0; i < uri_str.size(); ++i)
		{
			if (uri_str[i] == '\\' || uri_str[i] == '/')
			{
				m_data.push_back(URI_SEPARATOR);
			}
			else if (uri_str[i] == ':')
			{
				++i;

				for (size_t y = i; y < uri_str.size(); ++y)
				{
					m_port += uri_str[y];
				}

				break;
			}
			else
			{
				m_data.push_back(uri[i]);
			}
		}

		return *this;
	}

	std::string UriParser::port() noexcept
	{
		return m_port;
	}

	std::string UriParser::protocol() noexcept
	{
		return m_protocol;
	}

	void UriParser::open_app()
	{
		if (this->protocol() == ZKA_HTTPS_PROTOCOL)
		{
			HTTPDownloadFactory download;
			auto				only_host = this->get();
			auto				only_page = this->get();

			// here we make a clean host name.
			if (only_host.find("www") != std::string::npos)
				only_host.erase(only_host.find("www"), 3);

			if (only_host.find("/") != std::string::npos)
				only_host.erase(only_host.find("/"));

			// and we get the contents later.
			if (only_page.find("/") == std::string::npos)
				return;

			download.set_endpoint(only_host);

			auto uuid = uuids::to_string(UUIDFactory::version<4>());

			download.download(only_page.substr(only_page.find("/") + 1), only_host + "-" + uuid + ".html");
		}
	}

	UriParser& UriError::get()
	{
		return m_uri;
	}

} // namespace ZKA::Utils
