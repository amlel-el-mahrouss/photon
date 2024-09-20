/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 *			File: Uri.cpp
 *			Purpose: ZKA URI parser
 *
 * =====================================================================
 */

/**
@file
*/

#include <URI.hpp>
#include <IURLLoader.hpp>

#ifndef ZKA_URI_MAXSIZE
#define ZKA_URI_MAXSIZE (8196)
#endif // ZKA_URI_MAXSIZE

#ifndef ZKA_URI_SEPARATOR
#define ZKA_URI_SEPARATOR '\a'
#endif // ZKA_URI_SEPARATOR

namespace ZKA::Utils
{
	URIParser::URIParser(const char* protocol)
	{
		for (std::size_t i = 0; i < strlen(protocol); i++)
		{
			if (protocol[i] == ':')
				break;

			m_protocol += protocol[i];
		}
	}

	URIParser::~URIParser() = default;

	String URIParser::get() noexcept
	{
		String uri;

		for (size_t i = 0; i < m_data.size(); i++)
		{
			if (m_data[i] == ZKA_URI_SEPARATOR)
				continue;

			uri.push_back(m_data[i]);
		}

		uri += '\0';

		return uri;
	}

	URIParser& URIParser::operator/=(const String& uri)
	{
		this->operator/=(uri.c_str());

		return *this;
	}

	URIParser& URIParser::operator/=(const char* uri)
	{
		if (!uri ||
			*uri == 0)
			return *this;

		String uri_str = uri;

		if (strstr(uri, m_protocol.c_str()))
			return *this;

		for (size_t i = 0; i < uri_str.size(); ++i)
		{
			if (uri_str[i] == ':')
			{
				if (!m_port.empty())
					m_port.clear();

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

	String URIParser::port() noexcept
	{
		return m_port;
	}

	String URIParser::protocol() noexcept
	{
		return m_protocol;
	}

	bool URIParser::open_app()
	{
		if (this->protocol() == ZKA_HTTPS_PROTOCOL ||
			this->protocol() == ZKA_HTTP_PROTOCOL)
		{
			if (this->protocol() == ZKA_HTTP_PROTOCOL)
			{
				ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTP;
			}
			else
			{
				ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTPS;
			}

			URIParser  url(this->protocol().c_str());
			IURLLoader loader;

			String root = "/";

			String content = this->get();

			if (content.find("/") != std::string::npos)
			{
				loader.set_endpoint(content.substr(0, content.find("/")));

				root = content.substr(content.find("/"));

				// remove port.
				if (root.find(":") != String::npos)
					root.erase(root.find(":"));
			}
			else
			{
				loader.set_endpoint(content);
			}

			url /= root;

			std::cout << loader.get(url);

			return true;
		}
		else if (this->protocol() == ZKA_FILE_PROTOCOL)
		{
#ifdef ZKA_WINDOWS
			IShellHelper helper;
			helper.open(this->get(), nullptr);
#else
			String cmd = "xdg-open ";
			cmd += this->get();

			std::system(cmd.c_str());
#endif

			return true;
		}
		else if (this->protocol() == ZKA_ZKA_PROTOCOL)
		{
			// We don't handle the ZKA protocol directly.
			return false;
		}

		return false;
	}

	URIParser& URIError::get()
	{
		return m_uri;
	}

} // namespace ZKA::Utils
