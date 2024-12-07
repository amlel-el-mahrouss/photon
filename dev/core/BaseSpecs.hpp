/*
 * =====================================================================
 *
 *			Photon
 *
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <Config.hpp>
#include <Macros.hpp>
#include <cerrno>
#include <cstdlib>

#ifndef ZKA_WINDOWS

inline int fopen_s(FILE** fp, const char* path, const char* res) noexcept
{
	*fp = fopen(path, res);
	return errno;
}

#endif

#ifdef ZKA_END_OF_BUFFER
#undef ZKA_END_OF_BUFFER
#endif // ZKA_END_OF_BUFFER

#define ZKA_END_OF_BUFFER '\0'

#define ZKA_EMPTY_HTML "<!doctype html>\r\n<html>\r\n<head>\r\n</head>\r\n<body>\r\n</body>\r\n</html>\r\n"

ZKA_API void   zka_log(const char* str);
ZKA_API size_t zka_strlen(const char* str);
ZKA_API time_t zka_get_epoch();
ZKA_API FILE*  zka_get_logger();
ZKA_API bool   zka_open_logger();

#ifdef _MSC_VER
#define ZKA_PACKED_STRUCT(DECL)   \
	__pragma(pack(push, 1)) DECL; \
	__pragma(pack(pop))
#else
#define ZKA_PACKED_STRUCT(DECL) typedef DECL __attribute__((packed));
#endif

namespace ZKA
{
	namespace FS = std::filesystem;

	using Thread = std::thread;
	using String = std::string;

	template <typename CharType>
	using BasicString = std::basic_string<CharType>;

	using PChar = wchar_t;

	using PString = BasicString<PChar>;

	class ZKA_API BrowserError : public std::runtime_error
	{
	public:
		BrowserError(const char* error = "ERROR_UNKNOWN")
			: std::runtime_error(error)
		{
		}
		~BrowserError() = default; // let the ABI define that.

		BrowserError& operator=(const BrowserError&) = default;
		BrowserError(const BrowserError&)			 = default;
	};

	inline String zka_replace_format(String fmt, String output, String with)
	{
		auto err_pos = output.find("{{ " + fmt + " }}");

		if (err_pos != String::npos)
		{
			output.replace(err_pos, ("{{ " + fmt + " }}").size(), with);
		}

		return output;
	}

#ifdef ZKA_WINDOWS
	class ZKA_API Win32Error : public std::runtime_error
	{
	public:
		Win32Error(const String& what)
			: std::runtime_error(what)
		{
			mHr = GetLastError();
		}
		~Win32Error() = default; // let the ABI define that.

		Win32Error& operator=(const Win32Error&) = default;
		Win32Error(const Win32Error&)			 = default;

		const HRESULT& hr()
		{
			return mHr;
		}

	private:
		HRESULT mHr;
	};

	template <typename T>
	class ModuleType;
	class Win32Helper;
	class ModuleManagerWin32;

	template <typename T>
	class ZKA_API ModuleType final
	{
		ModuleType() = default;
		friend ModuleManagerWin32;

	public:
		ModuleType(T t)
			: m_ptr(t)
		{
		}

		T get()
		{
			return m_ptr;
		}

		T operator->()
		{
			return m_ptr;
		}

	private:
		T m_ptr;
	};

	class ZKA_API Win32Helper final
	{
	public:
		static HWND find_wnd(const wchar_t* compare)
		{
			if (!compare)
				return nullptr;

			HWND	hCurWnd = nullptr;
			wchar_t string[256];

			do
			{
				ZeroMemory(&string, 255);

				hCurWnd = FindWindowEx(nullptr, hCurWnd, nullptr, nullptr);
				GetWindowTextW(hCurWnd, string, 256);

				if (string == compare || !lstrcmpW(compare, string))
					return hCurWnd;

			} while (hCurWnd != nullptr);

			return nullptr;
		}
	};

	class ZKA_API ModuleManagerWin32 final
	{
	public:
		ModuleManagerWin32() = delete;

		explicit ModuleManagerWin32(const String& module_name)
			: hMod(nullptr)
		{
			assert(!module_name.empty());
			hMod = LoadLibraryExA(module_name.c_str(), nullptr, 0);

			if (!hMod)
				throw Win32Error("LoadLibraryExA failed!");
		}

		~ModuleManagerWin32()
		{
			if (hMod)
				FreeLibrary(hMod);
		}

		ModuleManagerWin32& operator=(const ModuleManagerWin32&) = default;
		ModuleManagerWin32(const ModuleManagerWin32&)			 = default;

		template <typename T>
		ModuleType<T> get(const String& ordinal)
		{
			if (!hMod)
				return {};
			if (ordinal.empty())
				return {};

			T the{reinterpret_cast<T>(GetProcAddress(hMod, ordinal.c_str()))};

			return the;
		}

	private:
		HMODULE hMod;
	};

	using ModuleManager = ModuleManagerWin32;
#endif // ZKA_WINDOWS

	template <typename T>
	concept IsPointer = (std::is_pointer<T>::value);

	template <typename T>
	concept NotNull = (!std::is_same<T, std::nullptr_t>::value);

	template <typename T>
	concept IsPointerAndNotNull = (IsPointer<T> && NotNull<T>);

	template <typename T>
	class ZKA_API Ref
	{
	public:
		Ref()
			: m_ptr(nullptr)
		{
		}

		Ref(IsPointerAndNotNull auto ptr)
			: m_ptr(ptr)
		{
			m_ref_cnt = new int32_t(0);
			assert(m_ref_cnt);

			this->_inc_ref();
		}

		~Ref()
		{
			if (m_ref_cnt && *m_ref_cnt == 0)
			{
				if (m_ptr)
				{
					delete m_ptr;
				}
			}
		}

		int32_t count()
		{
			return *m_ref_cnt;
		}

		T get()
		{
			return m_ptr;
		}
		T operator->()
		{
			return m_ptr;
		}

	public:
		Ref& operator=(const Ref& ref)
		{
			m_ptr			= ref.m_ptr;
			this->m_ref_cnt = ref.m_ref_cnt;

			return *this;
		}

		Ref(const Ref& ref)
		{
			m_ptr			= ref.m_ptr;
			this->m_ref_cnt = ref.m_ref_cnt;
		}

		operator bool()
		{
			return m_ptr;
		}

		void _inc_ref()
		{
			if (m_ref_cnt)
				++*(m_ref_cnt);
		}

	private:
		T		 m_ptr;
		int32_t* m_ref_cnt{nullptr};
	};

	template <typename T>
	static inline Ref<T> make_ref(Ref<T> cls)
	{
		Ref<T> ref{cls};
		ref._inc_ref();

		return ref;
	}

	template <typename T>
	static inline Ref<T> make_ref(T cls)
	{
		Ref<T> ref{cls};

		return ref;
	}

#ifdef ZKA_WINDOWS
	using PrivShellData = HWND;

	constexpr const char* SHELL_MANAGER_EXEC_OPEN = "open";
	constexpr size_t	  cCredsLength			  = CREDUI_MAX_PASSWORD_LENGTH;

	class ZKA_API IShellHelper final
	{
	public:
		explicit IShellHelper() = default;
		~IShellHelper()			= default;

		IShellHelper& operator=(const IShellHelper&) = default;
		IShellHelper(const IShellHelper&)			 = default;

		struct ZKA_API CredsResult final
		{
		private:
			friend IShellHelper;

			WCHAR fCredsIn[cCredsLength] = {0};
			PVOID fCredsOut				 = nullptr;
			ULONG fSizeCredsOut			 = cCredsLength;
			ULONG fAuthPkg				 = 0;

		public:
			std::vector<PString> login;
			BOOL				 fWasSuccessful = false;

			explicit CredsResult() = default;

			~CredsResult() = default;

			bool operator()() noexcept
			{
				WCHAR* pszName		  = new WCHAR[CREDUI_MAX_USERNAME_LENGTH + 1];
				WCHAR* pszPwd		  = new WCHAR[CREDUI_MAX_PASSWORD_LENGTH + 1];
				WCHAR* pszDomain	  = new WCHAR[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
				DWORD  maxLenName	  = CREDUI_MAX_USERNAME_LENGTH + 1;
				DWORD  maxLenPassword = CREDUI_MAX_PASSWORD_LENGTH + 1;

				DWORD maxLenDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

				//////////////////////////////////////////////////////////////
				//    DECRYPT CREDS BUFFER, ACCORDING TO TYPE.
				//////////////////////////////////////////////////////////////

				if (::CredUnPackAuthenticationBufferW(
						CRED_PACK_GENERIC_CREDENTIALS, fCredsOut, fSizeCredsOut, pszName,
						&maxLenName, pszDomain, &maxLenDomain, pszPwd,
						&maxLenPassword) == FALSE)
				{
					auto err = GetLastError();

					delete[] pszDomain;
					delete[] pszPwd;
					delete[] pszName;

					return false;
				}

				if (fCredsOut)
				{
					SecureZeroMemory(fCredsOut, fSizeCredsOut);
					CoTaskMemFree(fCredsOut);
				}

				//////////////////////////////////////////////////////////////
				//    APPEND CREDS TO LIST.
				//////////////////////////////////////////////////////////////

				login.push_back(pszName);
				login.push_back(pszPwd);
				login.push_back(pszDomain);

				HANDLE token = nullptr;

				if (::LogonUserW(pszName, pszDomain, pszPwd, LOGON32_LOGON_NETWORK,
								 LOGON32_PROVIDER_DEFAULT, &token) == FALSE)
				{
					//////////////////////////////////////////////////////////////
					//    NOW CLEAR HERE, DONT ADD A GOTO, SINCE WE ERRORED.
					//////////////////////////////////////////////////////////////

					delete[] pszDomain;
					delete[] pszPwd;
					delete[] pszName;

					if (token)
						CloseHandle(token);

					login.clear();
					return false;
				}

				if (token)
					CloseHandle(token);

				//////////////////////////////////////////////////////////////
				//    NOW CLEAR THE STUFF
				//////////////////////////////////////////////////////////////

				delete[] pszDomain;
				delete[] pszPwd;
				delete[] pszName;

				return true;
			}
		};

		CredsResult validate(
			PrivShellData priv, const wchar_t* message = L"Please confirm it's you.", const wchar_t* title = L"Permission Manager.") noexcept
		{
			static BOOL isSaved = false;

			static CredsResult credsRemember{};

			CredsResult credsFail{};
			credsFail.fWasSuccessful = false;

			if (isSaved)
				return credsRemember;

			CREDUI_INFOW ui{};
			ui.cbSize		  = sizeof(CREDUI_INFO);
			ui.hwndParent	  = priv;
			ui.pszMessageText = message;
			ui.pszCaptionText = title;
			ui.hbmBanner	  = nullptr; // ignored.

			CredsResult creds{};

			static auto cAlreadyRaised = false;

			if (cAlreadyRaised)
				return credsFail;

			cAlreadyRaised = true;

			auto dwAuthError = 0;

			auto dwResult = ::CredUIPromptForWindowsCredentialsW(
				&ui,					  // Customizing information
				dwAuthError,			  // Error code to display
				&creds.fAuthPkg,		  // Authorization package
				creds.fCredsIn,			  // Credential byte array
				cCredsLength,			  // Size of credential input buffer
				(void**)&creds.fCredsOut, // Output credential byte array
				&creds.fSizeCredsOut,	  // Size of credential byte array
				&isSaved,				  // Select the save check box.
				CREDUIWIN_GENERIC | CREDUIWIN_CHECKBOX);

			creds.fWasSuccessful = (dwResult == ERROR_SUCCESS);

			if (creds.fWasSuccessful)
			{
				creds.fWasSuccessful = creds();
			}

			cAlreadyRaised = false;

			credsRemember = creds;

			return creds;
		}

		Ref<HINSTANCE> open(const String& app_name, PrivShellData priv)
		{
			if (app_name.empty())
				return {};

			return IShellHelper::open(app_name.c_str(), priv);
		}

		Ref<HINSTANCE> open(const char* app_name, PrivShellData priv)
		{
			if (!app_name)
				return {};

			Ref<HINSTANCE> instance = ShellExecuteA(priv, SHELL_MANAGER_EXEC_OPEN, app_name, nullptr, nullptr, SW_SHOW);

			if (!instance)
				throw Win32Error("Win32 error, check hr()");

			return instance;
		}
	};
#else
	class ZKA_API IShellHelper final
	{
	public:
		explicit IShellHelper() = default;
		~IShellHelper()			= default;

		IShellHelper& operator=(const IShellHelper&) = default;
		IShellHelper(const IShellHelper&)			 = default;

		bool validate(const char* permission_name)
		{
			static std::vector<std::string> cPerms;

			if (std::find(cPerms.cbegin(), cPerms.cend(), permission_name) != cPerms.end())
				return true;

			String cmd = "pkexec --user $USER echo";

			if (std::system(cmd.c_str()) > 1)
			{
				cmd = "notify-send -a 'Photon' 'Permission Manager' 'Permission defined for: ";
				cmd += permission_name;
				cmd += "'";

				std::system(cmd.c_str());

				return false;
			}

			cmd = "notify-send -a 'Photon' 'Permission Manager' 'Got Permission for: ";
			cmd += permission_name;
			cmd += "'";
			std::system(cmd.c_str());

			cPerms.push_back(permission_name);
			return true;
		}

		int open(const char* app_name)
		{
			if (!app_name)
				return ENOENT;

			String cmd = "xdg-open ";
			cmd += app_name;

			return std::system(cmd.c_str());
		}
	};
#endif

	inline String get_at_current_path(const String& program_name)
	{
		auto path = FS::current_path();
		path /= program_name;

		try
		{
			std::ifstream io(path);

			// if it aint exist, throw and error
			if (!io.is_open())
				throw std::bad_alloc();
		}
		catch (std::bad_alloc err)
		{
			return "";
		}

		return path.string() + program_name;
	}

#ifdef ZKA_WINDOWS
	inline void fini_winsock() noexcept
	{
		WSACleanup();
	}

	inline bool init_winsock(WSADATA* dat) noexcept
	{
		if (WSAStartup(MAKEWORD(2, 2), dat) == 0)
		{
			std::atexit(fini_winsock);
			return true;
		}

		return false;
	}

	// for debug builds, also new the in-game console :p
	inline void open_terminal(FILE* fp = stdout)
	{
		AllocConsole();
		(void)freopen("CONOUT$", "w", fp);
	}
#endif

	class DialogHelper
	{
	public:
#ifdef ZKA_WINDOWS
		static int32_t message_box(wchar_t* title, wchar_t* message, int flags = 0)
		{
			if (!title)
				return -1;

			if (!message)
				return -1;

			return MessageBoxExW(nullptr, message, title, flags, LANG_ENGLISH);
		}
#endif // !ZKA_WINDOWS

#ifdef ZKA_WINDOWS
		static int32_t message_box(PCWSTR title, PCWSTR header, PCWSTR message, PCWSTR icon, int buttonFlags)
		{
			if (!title)
				return -1;

			if (!header)
				return -1;

			if (!message)
				return -1;

			TASKDIALOGCONFIG config			= {sizeof(TASKDIALOGCONFIG)};
			int32_t			 clicked_button = 0;

			config.pszContent		  = message;
			config.pszMainInstruction = header;
			config.pszWindowTitle	  = title;
			config.pszMainIcon		  = icon;
			config.dwCommonButtons	  = TDCBF_YES_BUTTON;
			config.hwndParent		  = nullptr;

			TaskDialogIndirect(&config, &clicked_button, nullptr, nullptr);

			return clicked_button;
		}
#endif // !ZKA_WINDOWS
	};

	class ZKA_API Logger final
	{
	public:
		Logger()  = default;
		~Logger() = default;

		Logger& operator=(const Logger&) = default;
		Logger(const Logger&)			 = default;

	public:
		static Logger& get_singleton() noexcept
		{
			static Logger logging;
			return logging;
		}

		auto get() noexcept
		{
			static spdlog::logger* LOGGER = nullptr;

			if (!LOGGER)
			{
#ifdef _WIN32
				auto info = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
				auto info = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif

				info->set_level(spdlog::level::info);
				info->set_pattern("[%^WWW%$] %v");

#ifdef _WIN32
				auto critical = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
				auto critical = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif

				critical->set_level(spdlog::level::critical);
				critical->set_pattern("[%^WWW%$] %v");

#ifdef _WIN32
				auto err = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
				auto err = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif

				err->set_level(spdlog::level::err);
				err->set_pattern("[%^WWW%$] %v");

				LOGGER = new spdlog::logger("WWW_SINK", {err, info, critical});

				std::ios_base::sync_with_stdio(false);
			}

			return LOGGER;
		}
	};

	class ZKA_API Timer final
	{
	public:
		Timer() noexcept
			: mTimer(std::chrono::steady_clock::now())
		{
		}

		~Timer() = default;

		std::chrono::steady_clock::time_point now() noexcept
		{
			return std::chrono::steady_clock::now();
		}

		const std::chrono::steady_clock::time_point& start() noexcept
		{
			return mTimer;
		}

		std::chrono::duration<double> time_since(const std::chrono::steady_clock::time_point& at) noexcept
		{
			return at - mTimer;
		}

	private:
		std::chrono::steady_clock::time_point mTimer;
	};

	class ZKA_API UUIDFactory final
	{
	public:
		template <short ver>
		static uuids::uuid version()
		{
			switch (ver)
			{
			case 4: {
				std::random_device rd;
				auto			   seed_data = std::array<int, std::mt19937::state_size>{};

				std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));

				std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
				std::mt19937  generator(seq);

				auto gen = uuids::uuid_random_generator(generator);

				return gen();
			}
			default:
				break;
			}

			return {};
		}
	};

	class ZKA_API FilesystemWrapper final
	{
	public:
		FilesystemWrapper()	 = default;
		~FilesystemWrapper() = default;

	public:
		ZKA_COPY_DEFAULT(FilesystemWrapper);

	public:
		std::ofstream write(const char* out_path, bool append) const noexcept
		{
			if (FS::exists(out_path) && append)
				return std::ofstream(out_path, std::ios::app);

			return std::ofstream(out_path);
		}

		std::ofstream open(const char* out_path) const noexcept
		{
			if (!FS::exists(out_path))
				return {};

			return std::ofstream(out_path);
		}

		bool create_directory(const char* path) const noexcept
		{
			return FS::create_directory(path);
		}

		FS::path get_temp() const noexcept
		{
			return FS::temp_directory_path();
		}

		FS::path get_engine_dir() const noexcept
		{
			ZKA_GET_DATA_DIR(dir);
			dir += "Contents/";

			return dir;
		}
	};

	template <typename PtrType, std::size_t Size>
	class Pool final
	{
	public:
		explicit Pool() noexcept
			: mIndex(0UL),
			  mPointer(nullptr)
		{
			/* allocate these shits */ // type			  size
			this->mPointer = static_cast<char*>(malloc(sizeof(PtrType) * Size));
			ZKA_ASSERT(mPointer); // assert that shit

			/* zero memory that shit */
			ZeroMemory(this->mPointer, sizeof(PtrType) * Size);
		}

		~Pool() noexcept
		{
			if (this->mPointer)
			{
				free(this->mPointer);
			}
		}

	private:
		std::size_t mIndex;
		char*		mPointer;

	public:
		std::size_t size() const noexcept
		{
			return sizeof(PtrType) * Size;
		}

		const std::size_t& capacity() const noexcept
		{
			return mIndex;
		}

		char* data() const noexcept
		{
			return mPointer;
		}

	public:
		template <typename... Args>
		PtrType* allocate(Args&&... args) noexcept
		{
			if (mIndex > Size)
				return nullptr;

			PtrType* ptr = reinterpret_cast<PtrType*>(&mPointer[mIndex]);
			*ptr		 = PtrType(std::forward<Args>(args)...);

			mIndex += sizeof(PtrType);

			return ptr;
		}

		template <typename T>
		void deallocate(T* ptr) noexcept
		{
			if (!ptr)
				return;

			ptr->~T();
			memset(ptr, 0, sizeof(T));

			mIndex -= sizeof(PtrType);
		}
	};

	namespace Threading
	{
		template <typename Fn, typename... Args>
		class AsyncAction final
		{
			using FnT = Fn;

		public:
			AsyncAction() = delete;

			AsyncAction(FnT fn, Args&&... args)
			{
				ZKA_ASSERT(fn);
				mThread = std::thread(fn, args...);
			}

			~AsyncAction()
			{
			}

			void detach() noexcept
			{
				mThread.detach();
			}

			AsyncAction& operator=(const AsyncAction&) = default;
			AsyncAction(const AsyncAction&)			   = default;

		private:
			Thread mThread;
		};
	} // namespace Threading

	ZKA_API inline BasicString<PChar> platform_string(const char* utf8)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<PChar>> cvt;
		return cvt.from_bytes(utf8);
	}
} // namespace ZKA

#ifdef ZKA_WINDOWS
#define ZKA_INIT_COM ZKA_ASSERT(SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
#define ZKA_FINI_COM CoUninitialize()
#endif // ifdef ZKA_WINDOWS

#define ZKA_CRITICAL(...) ZKA::Logger::get_singleton().get()->critical(__VA_ARGS__)
#define ZKA_ERROR(...)	  ZKA::Logger::get_singleton().get()->error(__VA_ARGS__)
#define ZKA_INFO(...)	  ZKA::Logger::get_singleton().get()->info(__VA_ARGS__)
#define ZKA_WARN(...)	  ZKA::Logger::get_singleton().get()->warn(__VA_ARGS__)
