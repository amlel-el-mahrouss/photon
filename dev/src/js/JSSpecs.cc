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

IJSVirtualMachine::IJSVirtualMachine(std::vector<String> js_blob)
	: mBlob(js_blob)
{
    ZKA_INFO("Allocated JavaScript Context!");
}

Bool IJSVirtualMachine::run_script()
{
    ZKA_INFO("Running script...");

    for (auto& line : mBlob)
    {
        
    }

    return true;
}
