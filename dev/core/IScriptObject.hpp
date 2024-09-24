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
		explicit IScriptObject(rapidxml::xml_node<char>* p_node)
			: IDOMObject(p_node)
		{
		}

	public:
		~IScriptObject() override = default;

		Int32 node_type() override
		{
			return ZKA_SCRIPT_OBJECT;
		}

		static IScriptObject* make_script_object(String data)
		{
			if (data.empty())
				return nullptr;

			rapidxml::xml_document<char> doc;
			doc.parse<0>(data.data());

			String name = doc.first_node()->name();

			if (name != "script")
			{
				return nullptr;
			}

			IScriptObject* new_dom = new IScriptObject(doc.first_node());

			if (new_dom)
			{
				ZKA_ERROR("<script> allocation failed, probably out of memory.");
				return nullptr;
			}

			return new_dom;
		}
	};
} // namespace ZKA
