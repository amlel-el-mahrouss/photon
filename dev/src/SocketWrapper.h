/*
 * =====================================================================
 *
 *			webdll
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include "WebCore.h"

#ifdef ZKA_WINDOWS

#define ZKA_SOCKET socket
#define ZKA_CLOSE closesocket
#define ZKA_SHUTDOWN shutdown
#define ZKA_ACCEPT accept
#define ZKA_CONNECT connect
#define ZKA_IOCTL ioctlsocket

#else

#ifndef _WIN32
#   define INADDR_NONE -1
#   define SOCKET_ERROR -1
#   define WSAECONNRESET ECONNRESET
#   define WSAEWOULDBLOCK EWOULDBLOCK
#   define WSAGetLastError() errno
#endif

#ifdef _WIN32
#   define s_addr S_un.S_addr
#endif

#define ZKA_SOCKET socket
#define ZKA_CLOSE close
#define ZKA_SHUTDOWN shutdown
#define ZKA_ACCEPT accept
#define ZKA_CONNECT connect
#define ZKA_IOCTL ioctl

#endif // ZKA_WINDOWS

namespace ZKA
{
	enum class SOCKET_FLAG : std::int64_t
	{
		NON_BLOCKING = FIONBIO,
		ASYNC = FIOASYNC,
	};
}

namespace ZKA::Network
{
	enum class SOCKET_TYPE
	{
		TCP,
		UDP,
		COUNT,
	};

	using CSocket = uintptr_t;

	class ZKA_API Socket final
	{
	public:
		explicit Socket(const SOCKET_TYPE type);
		~Socket();

		Socket& operator=(const Socket&) = default;
		Socket(const Socket&) = default;

	public:
		operator bool() noexcept;

	public:
		template <typename Data, size_t Size = sizeof(Data)>
		void send(Data ptr, std::size_t sz = 0);

		template <typename Data, size_t Size = sizeof(Data)>
		void recv(Data ptr, std::size_t sz = 0);

	public:
		CSocket PublicSocket;


	};
}

#include "SocketWrapper.inl"