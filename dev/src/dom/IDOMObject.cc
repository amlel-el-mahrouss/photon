/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <dom/IDOMObject.hpp>

namespace ZKA
{
	bool is_html_document(String data) noexcept
	{
		std::transform(data.begin(), data.end(), data.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		return data.find(ZKA_HTML_DOCTYPE) != String::npos &&
			   data.find(ZKA_XHTML_DOCTYPE) == String::npos;
	}

	/// @brief Check if xml is XHTML document.
	bool is_xhtml_document(String data) noexcept
	{
		return data.find(ZKA_XHTML_DOCTYPE) != String::npos;
	}

	/// @brief Get HTML document from xml blob.
	String get_xhtml_document(String data) noexcept
    {
        if (!is_xhtml_document(data))
		{
			return ZKA_EMPTY_HTML;
		}

		std::transform(data.begin(), data.end(), data.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		if (data.find(ZKA_HTML_DOCTYPE) != String::npos)
		{
			return data.substr(data.find(ZKA_HTML_DOCTYPE) + strlen(ZKA_HTML_DOCTYPE));
		}
		else
		{
			String doc_type = data.substr(0, strlen(ZKA_HTML_DOCTYPE));

			std::transform(doc_type.begin(), doc_type.end(), doc_type.begin(),
						   [](unsigned char c) { return std::tolower(c); });

			return data.substr(data.find(doc_type) + doc_type.size());
		}
    }
    
	/// @Brief Get HTML document.
	String get_html_document(String data) noexcept
	{
		if (!is_html_document(data))
		{
			return ZKA_EMPTY_HTML;
		}

		std::transform(data.begin(), data.end(), data.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		if (data.find(ZKA_HTML_DOCTYPE) != String::npos)
		{
			return data.substr(data.find(ZKA_HTML_DOCTYPE) + strlen(ZKA_HTML_DOCTYPE));
		}
		else
		{
			String doc_type = data.substr(0, strlen(ZKA_HTML_DOCTYPE));

			std::transform(doc_type.begin(), doc_type.end(), doc_type.begin(),
						   [](unsigned char c) { return std::tolower(c); });

			return data.substr(data.find(doc_type) + doc_type.size());
		}
	}

	IDOMObject* IDOMObject::make_dom_object(String data)
	{
		if (data.empty())
			return nullptr;

		rapidxml::xml_document<char> doc;
		doc.parse<0>(data.data());

		IDOMObject* new_dom = new IDOMObject(doc.first_node());

		if (new_dom)
		{
			ZKA_ERROR("DOM allocation failure, probably out of memory.");
			return nullptr;
		}

		return new_dom;
	}
} // namespace ZKA
