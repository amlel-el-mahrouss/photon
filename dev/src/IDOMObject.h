/*
 * =====================================================================
 *
 *			Vito
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <HTTPDownloadFactory.h>
#include <rapidxml/rapidxml.hpp>
#include <cassert>
#include <BaseSpecs.h>

#define ZKA_INVALID_OBJECT (0)

namespace ZKA
{
	class IDOMObject;

	class IDOMObject
	{
	public:
		explicit IDOMObject(rapidxml::xml_node<char>* p_node)
			: m_node(p_node)
		{
			ZKA_ASSERT(m_node);
		}

		virtual ~IDOMObject() = default;

		virtual Int32 type()
		{
			return ZKA_INVALID_OBJECT;
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

	private:
		rapidxml::xml_node<char>* m_node{nullptr};
	};
} // namespace ZKA
