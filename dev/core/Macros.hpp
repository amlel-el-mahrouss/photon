/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 *			File: Macros.h
 *			Purpose:
 *
 * =====================================================================
 */

#pragma once

#ifndef ZKA_GET_DATA_DIR
#ifdef ZKA_WINDOWS
#define ZKA_GET_DATA_DIR(DIR)            \
	ZKA::String DIR = getenv("APPDATA"); \
	DIR += "/.zka/";

#else
#define ZKA_GET_DATA_DIR(DIR)         \
	ZKA::String DIR = getenv("HOME"); \
	DIR += "/.zka/";

#endif

#ifdef ZKA_ZKA_OS
#define ZKA_GET_DATA_DIR(DIR)            \
	ZKA::String DIR = EnvGetVar("HOME"); \
	DIR += "\\.zka\\";

#else
#define ZKA_GET_DATA_DIR(DIR)         \
	ZKA::String DIR = getenv("HOME"); \
	DIR += "/.zka/";

#endif
#endif // ifndef ZKA_GET_DATA_DIR
