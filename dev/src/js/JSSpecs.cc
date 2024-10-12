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

IJSProgram::IJSProgram(std::vector<String> js_blob)
	: mBlob(js_blob)
{
    ZKA_INFO("Allocated JavaScript Context!");
}

Bool IJSProgram::run_script()
{
    ZKA_INFO("Start running JavaScript context...");

    for (auto& line : mBlob)
    {
        ZKA_INFO("Line: " + line);

    }

    return true;
}
