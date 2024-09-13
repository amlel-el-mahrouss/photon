/*
 * =====================================================================
 *
 *			iWeb Browser Engine
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
#define ZKA_GET_DATA_DIR(DIR)\
ZKA::String DIR = getenv("APPDATA");\
DIR += "/ZKA/";


#else
#define ZKA_GET_DATA_DIR(DIR)\
ZKA::String DIR = getenv("HOME");\
DIR += "/ZKA/";


#endif
#endif // ifndef ZKA_GET_DATA_DIR
