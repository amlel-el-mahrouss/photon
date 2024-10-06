/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <core/Socket.hpp>

namespace ZKA::Network
{
	Socket::Socket(const SOCKET_TYPE type)
		: PublicSocket(SOCKET_ERROR)
	{
		if (type == SOCKET_TYPE::TCP)
		{
			this->PublicSocket = ZKA_SOCKET(AF_INET,
											SOCK_STREAM,
											0);
		}
		else if (type == SOCKET_TYPE::UDP)
		{
			this->PublicSocket = ZKA_SOCKET(AF_INET,
											SOCK_DGRAM,
											0);
		}

		ZKA_ASSERT(this->PublicSocket != SOCKET_ERROR);
	}

	Socket::~Socket()
	{
		if (ZKA_SHUTDOWN(this->PublicSocket, SD_BOTH))
			ZKA_CLOSE(this->PublicSocket);
	}

	Socket::operator bool() noexcept
	{
		return this->PublicSocket != SOCKET_ERROR;
	}
} // namespace ZKA::Network
