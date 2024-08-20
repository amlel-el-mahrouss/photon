/*
 * =====================================================================
 *
 *			webdll
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#ifdef _WIN32
#   define NOMINMAX
#   define WIN32_LEAN_AND_MEAN

#   define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#endif // ifdef _WIN32

#include <ctime>
#include <cstdio>
#include <clocale>
#include <cstring>
#include <codecvt>
#include <cassert>
#include <cstdlib>
#include <cstdint>

#include <spdlog/spdlog.h>
#include <uuid/uuid.h>

#ifdef _WIN32

#   include <WinSock2.h>
#   include <ws2tcpip.h>

#else

#   include <sys/socket.h>
#   include <unistd.h>
#   include <netdb.h>
#   include <sys/ioctl.h>
#   include <arpa/inet.h>

#define SD_BOTH SHUT_RDWR
#define SD_SEND SHUT_WR
#define SD_READ SHUT_RD

#define ZeroMemory(ptr, sz) memset(ptr, 0, sz)

#define INVALID_SOCKET -1

#endif


#include <tuple>
#include <array>
#include <thread>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <concepts>
#include <stdexcept>
#include <algorithm>
#include <filesystem>

#ifdef _WIN32

#include <Windows.h>
#include <tlhelp32.h>

#include <shellapi.h>
#include <CommCtrl.h>

#pragma comment(lib,"comctl32.lib")
#pragma comment(lib, "Ws2_32.lib")

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifdef _WIN32
#define ZKA_WINDOWS 1
#endif // ifdef _MSC_VER

#ifdef __EXPORT_ZKA__
#   define ZKA_API __declspec(dllexport)
#else
#   define ZKA_API __declspec(dllimport)
#endif


#ifdef _MSC_VER
#   define ZKA_MSVC (1)
#   define ZKA_CXX_COMPILER "Microsoft Visual C++"
#   define ZKA_CXX ZKA_MSVC
#endif // ifdef _MSC_VER

#else

#ifdef __GNUC__
#   define ZKA_GCC (2)
#   define ZKA_CXX_COMPILER "GNU C++"
#   define ZKA_CXX ZKA_GCC

#   define ZKA_API __attribute__ ((visibility ("default")))
#endif

#endif

#ifndef _NDEBUG
#   define ZKA_DEBUG (1)
#else
#   define ZKA_RELEASE (2)
#endif

#ifdef _WIN32
#   define ZKA_ASSERT(expression) (void)(                                                \
            (!!(expression)) ||                                                              \
            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \
        )
#else
#   define ZKA_ASSERT(expression) assert(expression)
#endif

#ifndef ZKA_ENV
#   define ZKA_ENV getenv
#endif // ZKA_ENV

#define ZKA_COPY_DELETE(KLASS)\
KLASS& operator=(const KLASS&) = delete;\
KLASS(const KLASS&) = delete;\



#define ZKA_COPY_DEFAULT(KLASS)\
KLASS& operator=(const KLASS&) = default;\
KLASS(const KLASS&) = default;\



#define ZKA_MOVE_DELETE(KLASS)\
KLASS& operator=(KLASS&&) = delete;\
KLASS(KLASS&&) = delete;\



#define ZKA_MOVE_DEFAULT(KLASS)\
KLASS& operator=(KLASS&&) = default;\
KLASS(KLASS&&) = default;\

#ifndef ZKA_SLEEP
#   ifdef ZKA_WINDOWS
#   define ZKA_SLEEP Sleep
#   else
#   define ZKA_SLEEP sleep
#   endif
#endif /* ifndef */

namespace ZKA
{
    typedef double Double;
    typedef float Real;

    typedef std::int32_t Int32;
    typedef std::uint32_t UInt32;

    typedef std::int64_t Int64;
    typedef std::uint64_t UInt64;
}

#define ZKA_RELEASE "1.0.0-Salamanca"

#ifdef ZKA_BULLET
#   include <bullet/btBulletCollisionCommon.h>
#   include <bullet/btBulletDynamicsCommon.h>

#   define ZKA_PHYSICS "Bullet"
#else
#   define ZKA_PHYSICS "webdll.Physics"
#endif
