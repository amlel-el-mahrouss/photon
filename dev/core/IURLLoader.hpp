/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <IHTTPProtocol.hpp>
#include <URL.hpp>

#define ZKA_URL_PROTO "HTTP"

namespace ZKA
{
	/*
	 *	@brief IURLLoader
	 *	@brief Interface for loading HTTP/HTTPS urls, this is the base class for loading stuff as well.
	 */

	class ZKA_API IURLLoader
	{
	public:
		IURLLoader()		  = default;
		virtual ~IURLLoader() = default;

	public:
		ZKA_COPY_DEFAULT(IURLLoader);

	public:
		virtual String post(URL& url, String data, bool cache_data = false);
		virtual String put(URL& url, String data, bool cache_data = false);
		virtual String del(URL& url, String data, bool cache_data = false);
		virtual String get(URL& url, bool cache_data = true);
		virtual void   set_endpoint(const String& endpoint) noexcept;
		virtual String get_endpoint() noexcept;
		virtual String get_protocol() noexcept;

	protected:
		//! Filesystem wrapper, create, open, delete!
		FilesystemWrapper mWriter;
		//! HTTP endpoint.
		String mEndpoint;
	};
} // namespace ZKA
