/*
 * =====================================================================
 *
 *			webdll
 *			Copyright ZKA Technologies, all rights reserved.
 *
 *			File: HelperMacros.h
 *			Purpose:
 *
 * =====================================================================
 */

#pragma once

#include "WebCore.h"

#ifndef ZKA_GET_DATA_DIR
#ifdef _WIN32
#define ZKA_GET_DATA_DIR(DIR)\
ZKA::String DIR = getenv("APPDATA");\
DIR += "/ZKA/";


#else
#define ZKA_GET_DATA_DIR(DIR)\
ZKA::String DIR = getenv("HOME");\
DIR += "/ZKA/";


#endif
#endif // ifndef ZKA_GET_DATA_DIR
