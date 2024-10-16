/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <core/BaseSpecs.hpp>
#include <js/JITSpecs.hpp>

#define ZKA_JS_UNDEFINED "undefined"
#define ZKA_JS_NULL		 "null"
#define ZKA_JS_WINDOW	 "window"

/***********************************************************************************/
/** @brief This file is also about defining core js concepts. */
/***********************************************************************************/

namespace ZKA
{
    class IJSVirtualMachine;

    /// @brief JavaScriptEngine class program.
    class IJSVirtualMachine final
    {
    private:
        std::vector<String> mBlob;

    public:
        explicit IJSVirtualMachine(std::vector<String> js_blob);
        ~IJSVirtualMachine() = default;

        Bool run_script();

    public:
        ZKA_COPY_DEFAULT(IJSVirtualMachine);

    };
}
