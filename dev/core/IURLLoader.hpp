/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <BaseSpecs.hpp>
#include <IHTTPProtocol.hpp>
#include <URI.hpp>

#define ZKA_SUPPORT_PROTO "HTTP"

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
		String   post(Utils::URIParser& url, String data, bool cache_data);
		String   get(Utils::URIParser& url, String output_file_name, bool cache_data = false);
		void   set_endpoint(const String& endpoint) noexcept;
		String get_download_dir() const noexcept;

	public:
		const char* get_protocol() noexcept
		{
			return ZKA_SUPPORT_PROTO;
		}

	private:
		//! Filesystem wrapper, create, open, delete!
		FilesystemWrapper mWriter;
		//! HTTP endpoint.
		String mEndpoint;
	};
} // namespace ZKA
