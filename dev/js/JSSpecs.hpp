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
    class IJSProgram;

    /// @brief JavaScriptEngine class program.
    class IJSProgram final
    {
    private:
        String mBlob;

    public:
        explicit IJSProgram(String file_blob);
        ~IJSProgram() = default;

        Bool run_script();

    public:
        ZKA_COPY_DEFAULT(IJSProgram);

    };
}
