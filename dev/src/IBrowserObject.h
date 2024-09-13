/*
 * =====================================================================
 *
 *			iWeb Browser Engine
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <HTTPDownloadFactory.h>
#include <rapidxml/rapidxml.hpp>
#include <cassert>
#include <WebCore.h>

#define ZKA_INVALID_OBJECT (0)

namespace ZKA
{
	class IBrowserObject;

	class IBrowserObject
	{
	public:
		explicit IBrowserObject(rapidxml::xml_node<char>* p_node)
			: m_node(p_node)
		{
		}

		virtual ~IBrowserObject() = default;

		virtual Int32 type()
		{
			return ZKA_INVALID_OBJECT;
		}

		virtual Ref<rapidxml::xml_node<char>*> node_as_ref()
		{
			assert(m_node);
			return make_ref(m_node);
		}

		virtual bool is_element()
		{
			assert(m_node);
			return rapidxml::node_element == m_node->type();
		}

		virtual bool is_data()
		{
			assert(m_node);
			return rapidxml::node_data == m_node->type();
		}

		virtual bool is_comment()
		{
			assert(m_node);
			return rapidxml::node_comment == m_node->type();
		}

		virtual bool is_doc_type()
		{
			assert(m_node);
			return rapidxml::node_doctype == m_node->type();
		}

		virtual rapidxml::xml_attribute<char>* key(const char* attrib_name)
		{
			assert(m_node);
			return m_node->first_attribute(attrib_name, strlen(attrib_name));
		}

	private:
		rapidxml::xml_node<char>* m_node{nullptr};
	};
} // namespace ZKA
