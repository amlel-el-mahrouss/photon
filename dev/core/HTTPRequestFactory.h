/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <BaseSpecs.h>
#include <IHTTPProtocol.h>
#include <URI.h>

#define ZKA_SUPPORT_PROTO "HTTP"

namespace ZKA
{
	/*
	 *	@brief HTTPRequestFactory
	 *	@brief Takes care of HTTPS/HTTP requests.
	 */

	class ZKA_API HTTPRequestFactory final
	{
	public:
		HTTPRequestFactory() = default;
		~HTTPRequestFactory() = default;

	public:
		ZKA_COPY_DEFAULT(HTTPRequestFactory);

	public:
		bool get_url(const String url, const String output_file_name, const bool cache_data = false) const;
		void set_endpoint(const String& endpoint) noexcept;
		String get_download_dir() const noexcept;

	public:
		const char* get_protocol() noexcept { return ZKA_SUPPORT_PROTO; }

	private:
		//! Filesystem wrapper, create, open, delete!
		FilesystemWrapper mWriter;
		//! HTTP endpoint.
		String mEndpoint;

	};
}
