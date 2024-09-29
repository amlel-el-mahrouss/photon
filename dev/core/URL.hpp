/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 *			File: Uri.h
 *			Purpose: ZKA URI parser
 *
 * =====================================================================
 */

#pragma once

#include <BaseSpecs.hpp>

#ifndef ZKA_HTTPS_PROTOCOL
#define ZKA_HTTPS_PROTOCOL ("https")
#endif // !ZKA_HTTPS_PROTOCOL

#ifndef ZKA_HTTP_PROTOCOL
#define ZKA_HTTP_PROTOCOL ("http")
#endif // !ZKA_HTTP_PROTOCOL

#ifndef ZKA_FILE_PROTOCOL
#define ZKA_FILE_PROTOCOL ("file")
#endif // !ZKA_FILE_PROTOCOL

#ifndef ZKA_MAIL_PROTOCOL
#define ZKA_MAIL_PROTOCOL ("mailto")
#endif // !ZKA_MAIL_PROTOCOL

#ifndef ZKA_ZKA_PROTOCOL
#define ZKA_ZKA_PROTOCOL ("zka://")
#endif // !ZKA_ZKA_PROTOCOL

namespace ZKA
{
	class ZKA_API URL final
	{
	public:
		URL(const char* protocol);
		virtual ~URL();

		URL& operator=(const URL&) = default;
		URL(const URL&)			   = default;

		String port() noexcept;
		String protocol() noexcept;
		String get() noexcept;

	public:
		String send(String data);
		String fetch();

	public:
		URL& operator/=(const String& uri);
		URL& operator/=(const char* uri);

	private:
		String m_data;
		String m_protocol;
		String m_port;
	};

	class ZKA_API URLError final : public BrowserError
	{
	public:
		URLError(URL& uri)
			: BrowserError("INVALID_URL_AT_DEST"), m_uri(uri)
		{
		}
		~URLError() = default; // let the ABI define that.

		URLError& operator=(const URLError&) = default;
		URLError(const URLError&)			 = default;

		URL& get();

	private:
		URL m_uri;
	};
} // namespace ZKA
