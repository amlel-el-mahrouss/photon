/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

/// @file IScriptObject.hpp
/// @brief <script> element.

#include <IDOMObject.hpp>

#define ZKA_SCRIPT_OBJECT (1)

namespace ZKA
{
	class IScriptObject;

	class IScriptObject final : public IDOMObject
	{
		explicit IScriptObject(rapidxml::xml_node<char>* p_node);

	public:
		~IScriptObject() override = default;

		Int32				  node_type() override;
		static IScriptObject* make_script_object(String data);
	};
} // namespace ZKA
