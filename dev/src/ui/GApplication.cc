/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <core/URL.hpp>
#include <ui/GViews.hpp>

int ZKA::GApplication::run(int argc, char* argv[])
{
#ifdef ZKA_WINDOWS
	WSADATA dat{0};
	ZKA::init_winsock(&dat);

	ZKA_INIT_COM;

	std::atexit([]() -> void {
		ZKA::fini_winsock();
		ZKA_FINI_COM;
	});
#endif

	while (true)
	{
		if (m_should_stop)
			break;

		for (auto& view : m_views)
		{
		    if (view->ShouldPaint())
				view->OnPaint();
		}

		// TODO: Execute JavaScript VM here as well.
	}

    return m_exit_code;
}

void ZKA::GApplication::abort()
{
	std::abort();
}

void ZKA::GApplication::exit(int code)
{
	m_exit_code = code;
}
