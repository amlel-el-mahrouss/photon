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

namespace ZKA
{
	/*
	 *	@brief HTTPDownloadFactory
	 *	@brief Downloads and xasset:// from HTTP/1.1 using Xplicit's own client.
	 */

	class ZKA_API HTTPDownloadFactory final
	{
	public:
		HTTPDownloadFactory() = default;
		~HTTPDownloadFactory() = default;

	public:
		ZKA_COPY_DEFAULT(HTTPDownloadFactory);

	public:
		bool download(const String url, const String output_file_name, const bool cache_data = false) const noexcept;
		void set_endpoint(const String& endpoint) noexcept;
		String get_download_dir() noexcept;

	public:
		const char* protocol() noexcept { return ZKA_HTTPS_PROTOCOL; }
		float version() const noexcept { return ZKA_HTTP_VER; }

	private:
		//! Filesystem wrapper, create, open, delete!
		FilesystemWrapper mWriter;
		//! HTTP endpoint.
		String mEndpoint;

	};
}
