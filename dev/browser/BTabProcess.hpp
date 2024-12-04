/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <core/BaseSpecs.hpp>
#include <core/URL.hpp>
#include <dom/IDOMObject.hpp>
#include <dom/IScriptObject.hpp>

namespace ZKA
{
    class ZKA_API BTabProcess final
    {
    private:
        URL m_tab_url;
        String m_tab_name;
        String m_html_blob;
        
    public:
        explicit BTabProcess() = default;
        ~BTabProcess() = default;
        
        ZKA_COPY_DEFAULT(BTabProcess);
        
    };
}
