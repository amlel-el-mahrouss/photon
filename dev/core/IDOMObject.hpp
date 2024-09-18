/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <IURLLoader.hpp>
#include <rapidxml/rapidxml.hpp>
#include <cassert>
#include <BaseSpecs.hpp>

#define ZKA_DOM_OBJECT (0)

namespace ZKA
{
	class IDOMObject;

	class IDOMObject
	{
		explicit IDOMObject(rapidxml::xml_node<char>* p_node)
			: m_node(p_node)
		{
			ZKA_ASSERT(m_node);
		}

	public:
		virtual ~IDOMObject() = default;

		ZKA_COPY_DEFAULT(IDOMObject);

		virtual Int32 type()
		{
			return ZKA_DOM_OBJECT;
		}

		virtual Ref<rapidxml::xml_node<char>*> node_as_ref()
		{
			ZKA_ASSERT(m_node);
			return make_ref(m_node);
		}

		virtual bool is_element()
		{
			ZKA_ASSERT(m_node);
			return rapidxml::node_element == m_node->type();
		}

		virtual bool is_data()
		{
			ZKA_ASSERT(m_node);
			return rapidxml::node_data == m_node->type();
		}

		virtual bool is_comment()
		{
			ZKA_ASSERT(m_node);
			return rapidxml::node_comment == m_node->type();
		}

		virtual bool is_doc_type()
		{
			ZKA_ASSERT(m_node);
			return rapidxml::node_doctype == m_node->type();
		}

		virtual rapidxml::xml_attribute<char>* get_attribute(const char* attrib_name)
		{
			ZKA_ASSERT(m_node);
			return m_node->first_attribute(attrib_name, strlen(attrib_name));
		}

		virtual rapidxml::xml_node<char>* get_node(const char* attrib_name)
		{
			ZKA_ASSERT(m_node);
			return m_node->first_node(attrib_name, strlen(attrib_name));
		}

		static IDOMObject* make_dom_factory(char* data)
		{
			rapidxml::xml_document<char> doc;
			doc.parse<0>(data);

			IDOMObject* new_dom = new IDOMObject(doc.first_node());

			if (new_dom)
			{
				ZKA_ERROR("new_dom allocation failure, probably out of memory.");
				return nullptr;
			}

			return new_dom;
		}

	private:
		rapidxml::xml_node<char>* m_node{nullptr};
	};

	bool is_html_document(String the_xml_blob) noexcept
	{
		return the_xml_blob.find("<!DOCTYPE html>") != String::npos &&
			   the_xml_blob.find("<!DOCTYPE html>") == 0;
	}
} // namespace ZKA
