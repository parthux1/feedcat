#pragma once

#include <optional>
#include <vector>
#include <string>
#include <regex>

#include <spdlog/spdlog.h>
#include <tinyxml2.h>

namespace tinyxml2 {

    /*!
     * \brief Get first child element with a specific attribute - value pair
     * \param root node to start traversing
     * \param attribute name to check
     * \param value to check in attribute
     * \returns first matching element if existing
     */
    std::optional<const XMLElement*> get_first_by_attribute(const XMLElement* root, const char* attribute, const char* value);

    /*!
     *
     * \param root node to start traversing
     * \param tag to check for
     * \returns all elements with the given tag
     */
    std::vector<const XMLElement*> get_all_by_tag(const XMLElement* root, const char* tag);

    /*!
     * \brief Strip javascript from html
     * \param html_raw html to strip
     * \returns html without <script></script> tags
     */
    std::string strip_javascript(const std::string& html_raw);
}
