/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <js/JSSpecs.hpp>

using namespace ZKA;

IJSProgram::IJSProgram(String file_blob)
	: mBlob(file_blob)
{
}

Bool IJSProgram::run_script()
{
    return true;
}