/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <core/IScriptObject.hpp>
#include <js/JSSpecs.hpp>

namespace ZKA
{
	IScriptObject::IScriptObject(rapidxml::xml_node<char>* p_node)
		: IDOMObject(p_node)
	{
	}

	Int32 IScriptObject::node_type()
	{
		return ZKA_SCRIPT_OBJECT;
	}

	Bool IScriptObject::run_script()
	{
		if (!this->get_node(nullptr)->value())
			return false;

		String js = this->get_node(nullptr)->value();

		IJSProgram prog(js);
		return prog.run_script();
	}

	IScriptObject* IScriptObject::make_script_object(String data)
	{
		if (data.empty())
			return nullptr;

		rapidxml::xml_document<char> doc;
		doc.parse<0>(data.data());

		String name = doc.first_node()->name();
		const char* cScriptElementName = "script";

		if (name != cScriptElementName)
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
} // namespace ZKA
