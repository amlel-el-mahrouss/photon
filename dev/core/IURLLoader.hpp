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
#include <URI.hpp>

#define ZKA_URL_PROTO "HTTP"

namespace ZKA
{
	/*
	 *	@brief IURLLoader
	 *	@brief Takes care of HTTPS/HTTP requests.
	 */

	class ZKA_API IURLLoader final
	{
	public:
		IURLLoader()  = default;
		~IURLLoader() = default;

	public:
		ZKA_COPY_DEFAULT(IURLLoader);

	public:
		String   post(Utils::URIParser& url, String data, bool cache_data = false);
		String   get(Utils::URIParser& url, bool cache_data = false);
		void   set_endpoint(const String& endpoint) noexcept;
		String get_endpoint() noexcept;

	public:
		const char* get_protocol() noexcept
		{
			return ZKA_URL_PROTO;
		}

	private:
		//! Filesystem wrapper, create, open, delete!
		FilesystemWrapper mWriter;
		//! HTTP endpoint.
		String mEndpoint;
	};
} // namespace ZKA
