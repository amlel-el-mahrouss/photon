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

#include <URL.hpp>
#include <IURLLoader.hpp>

#ifndef ZKA_URI_MAXSIZE
#define ZKA_URI_MAXSIZE (8196)
#endif // ZKA_URI_MAXSIZE

namespace ZKA
{
	URL::URL(const char* protocol)
	{
		m_protocol = protocol;

		if (m_protocol.find(":") != String::npos)
			m_protocol.erase(m_protocol.find(":"));
	}

	URL::~URL() = default;

	String URL::get() noexcept
	{
		return m_data;
	}

	URL& URL::operator/=(const String& uri)
	{
		this->operator/=(uri.c_str());

		return *this;
	}

	URL& URL::operator/=(const char* uri)
	{
		if (!uri ||
			*uri == 0)
			return *this;

		String uri_str = uri;

		if (uri_str.find(":") != String::npos)
		{
			m_data = uri_str.substr(0, uri_str.find(":"));
			m_port = uri_str.substr(uri_str.find(":") + 1);
		}
		else
		{
			m_data = uri_str;
		}

		return *this;
	}

	String URL::port() noexcept
	{
		return m_port;
	}

	String URL::protocol() noexcept
	{
		return m_protocol;
	}

	String URL::send(String data)
	{
		if (this->protocol() == ZKA_HTTPS_PROTOCOL ||
			this->protocol() == ZKA_HTTP_PROTOCOL)
		{
			try
			{
				if (this->protocol() == ZKA_HTTP_PROTOCOL)
				{
					ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTP;
				}
				else
				{
					ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTPS;
				}

				URL		   url(this->protocol().c_str());
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

				auto http = loader.post(url, data, true);

				if (http.find("\r\n\r\n") != String::npos)
				{
					auto html = http.substr(http.find("\r\n\r\n") + strlen("\r\n\r\n"));
					return html;
				}
			}
			catch (BrowserError err)
			{
				return "";
			}
		}

		return "";
	}

	String URL::fetch()
	{
		if (this->protocol() == ZKA_HTTPS_PROTOCOL ||
			this->protocol() == ZKA_HTTP_PROTOCOL)
		{
			try
			{
				if (this->protocol() == ZKA_HTTP_PROTOCOL)
				{
					ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTP;
				}
				else
				{
					ZKA::HTTP::ZKA_HTTP_PORT = ZKA_USE_HTTPS;
				}

				URL		   url(this->protocol().c_str());
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

				auto http = loader.get(url, false);

				if (http.find("\r\n\r\n") != String::npos)
				{
					auto html = http.substr(http.find("\r\n\r\n") + strlen("\r\n\r\n"));
					return html;
				}
			}
			catch (BrowserError err)
			{
				ZKA_GET_DATA_DIR(DIR);

				DIR += "/.html/DialogError.html";

				std::ifstream err_html(DIR);

				if (err_html.is_open())
				{
					std::stringstream ss;
					ss << err_html.rdbuf();

					auto output = ss.str();

					output = zka_replace_format("ERR_CODE", output, err.what());

					return output;
				}

				return ZKA_EMPTY_HTML;
			}

			return ZKA_EMPTY_HTML;
		}
		else if (this->protocol() == ZKA_FILE_PROTOCOL)
		{
			IShellHelper helper;

#ifdef ZKA_WINDOWS
			helper.open(this->get(), nullptr);
#else
			helper.open(this->get().c_str());
#endif

			return ZKA_EMPTY_HTML;
		}
		else if (this->protocol() == ZKA_ZKA_PROTOCOL)
		{

			return ZKA_EMPTY_HTML;
		}

		return ZKA_EMPTY_HTML;
	}

	URL& URLError::get()
	{
		return m_uri;
	}

} // namespace ZKA
