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

namespace ZKA::Utils
{
	// Accessors are like iterators, but with an offset.
	using URIAccessor = int32_t;

	class ZKA_API URIParser final
	{
	public:
		URIParser(const char* protocol);
		virtual ~URIParser();

		URIParser& operator=(const URIParser&) = default;
		URIParser(const URIParser&) = default;

		String port() noexcept;
		String protocol() noexcept;
		String get() noexcept;

	public:
		URIParser& operator/=(const String& uri);
		URIParser& operator/=(const char* uri);

	public:
		bool open_app();

	private:
		std::vector<char> m_data;
		String m_protocol;
		String m_port;

	};

	typedef URIParser URLParser;

	class ZKA_API URIError final : public std::runtime_error
	{
	public:
		URIError(URIParser& uri) : std::runtime_error("URIError"), m_uri(uri) {}
		~URIError() = default; // let the ABI define that.

		URIError& operator=(const URIError&) = default;
		URIError(const URIError&) = default;

		URIParser& get();

	private:
		URIParser m_uri;

	};
}
