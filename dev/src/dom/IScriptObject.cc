/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <core/IScriptObject.hpp>

namespace ZKA
{
	IScriptObject::IScriptObject(rapidxml::xml_node<char>* p_node)
		: IDOMObject(p_node)
	{
	}

	Int32 IScriptObject::node_type() override
	{
		return ZKA_SCRIPT_OBJECT;
	}

	IScriptObject* IScriptObject::make_script_object(String data)
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
}
