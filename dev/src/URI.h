/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 *			File: Uri.h
 *			Purpose: Xplicit URI parser
 *
 * =====================================================================
 */

#pragma once

#include "BaseSpecs.h"

#ifndef ZKA_HTTPS_PROTOCOL
#define ZKA_HTTPS_PROTOCOL ("https://")
#endif // !ZKA_HTTPS_PROTOCOL

#ifndef ZKA_HTTP_PROTOCOL
#define ZKA_HTTP_PROTOCOL ("http://")
#endif // !ZKA_HTTP_PROTOCOL

#ifndef ZKA_FILE_PROTOCOL
#define ZKA_FILE_PROTOCOL ("file://")
#endif // !ZKA_FILE_PROTOCOL

#ifndef ZKA_ZKA_PROTOCOL
#define ZKA_ZKA_PROTOCOL ("zka://")
#endif // !ZKA_ZKA_PROTOCOL

namespace ZKA::Utils
{
	// Accessors are like iterators, but with an offset.
	using UriAccessor = int32_t;

	class ZKA_API UriParser final
	{
	public:
		UriParser(const char* protocol);
		virtual ~UriParser();

		UriParser& operator=(const UriParser&) = default;
		UriParser(const UriParser&) = default;

		String port() noexcept;
		String protocol() noexcept;
		String get() noexcept;

	public:
		UriParser& operator/=(const String& uri);
		UriParser& operator/=(const char* uri);

		bool open_app();

	private:
		std::vector<char> m_data;
		String m_protocol;
		String m_port;

	};

	class ZKA_API UriError final : public std::runtime_error
	{
	public:
		UriError(UriParser& uri) : std::runtime_error("UriError"), m_uri(uri) {}
		~UriError() = default; // let the ABI define that.

		UriError& operator=(const UriError&) = default;
		UriError(const UriError&) = default;

		UriParser& get();

	private:
		UriParser m_uri;

	};
}
