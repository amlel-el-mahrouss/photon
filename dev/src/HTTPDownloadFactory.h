/*
 * =====================================================================
 *
 *			iWeb Browser Engine
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <WebCore.h>
#include <HTTPProtocol.h>
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
		bool download(const String assetId, const String outputFileName) const noexcept;
		void set_endpoint(const String& endpoint) noexcept;

	public:
		const char* protocol() noexcept { return ZKA_HTTPS_PROTOCOL; }
		float version() const noexcept { return ZKA_HTTP_VER; }

	private:
		//! Filesystem wrapper, create, open, delete!
		FilesystemWrapper mWriter;

		//! HTTP endpoint
		String mEndpoint;

	};
}
