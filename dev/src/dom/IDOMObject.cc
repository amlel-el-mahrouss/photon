/*
 * =====================================================================
 *
 *			Photon
 *			Copyright ZKA Technologies, all rights reserved.
 *
 * =====================================================================
 */

#include <IDOMObject.hpp>

namespace ZKA
{
	bool is_html_document(String the_xml_blob) noexcept
	{
		std::transform(the_xml_blob.begin(), the_xml_blob.end(), the_xml_blob.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		return the_xml_blob.find(ZKA_HTML_DOCTYPE) != String::npos &&
			   the_xml_blob.find(ZKA_XHTML_DOCTYPE) == String::npos;
	}

	/// @brief Check if xml is XHTML document.
	bool is_xhtml_document(String the_xml_blob) noexcept
	{
		return the_xml_blob.find(ZKA_XHTML_DOCTYPE) != String::npos;
	}

	/// @Brief Get HTML document.
	String get_html_document(String the_xml_blob) noexcept
	{
		if (!is_html_document(the_xml_blob))
		{
			return ZKA_EMPTY_HTML;
		}

		std::transform(the_xml_blob.begin(), the_xml_blob.end(), the_xml_blob.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		if (the_xml_blob.find(ZKA_HTML_DOCTYPE) != String::npos)
		{
			return the_xml_blob.substr(the_xml_blob.find(ZKA_HTML_DOCTYPE) + strlen(ZKA_HTML_DOCTYPE));
		}
		else
		{
			String doc_type = the_xml_blob.substr(0, strlen(ZKA_HTML_DOCTYPE));

			std::transform(doc_type.begin(), doc_type.end(), doc_type.begin(),
						   [](unsigned char c) { return std::tolower(c); });

			return the_xml_blob.substr(the_xml_blob.find(doc_type) + doc_type.size());
		}
	}
} // namespace ZKA
