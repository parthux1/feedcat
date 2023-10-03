#include "helper_tinyxml2.hpp"

namespace tinyxml2 {
    std::optional<const XMLElement*> get_first_by_attribute(const XMLElement* root, const char* attribute, const char* value)
    {
        if(root == nullptr)
        {
            SPDLOG_DEBUG("called on nullptr");
            return std::nullopt;
        }

        for(const XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            // anchor
            if(child->Attribute(attribute, value)) return child;

            // dfs
            if(child->FirstChildElement())
            {
                SPDLOG_DEBUG("has child");
                auto res = get_first_by_attribute(child, attribute, value);
                if(res.has_value()) return res;
            }
        }
        return std::nullopt;
    }


    std::vector<const XMLElement*> get_all_by_tag(const XMLElement* root, const char* tag)
    {
        std::vector<const XMLElement*> res;
        // supplying FirstChildElement() with the required tag name would skip matching nodes in other childs
        for(const XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            // anchor
            if(child->Name() == std::string(tag)) res.push_back(child);

            // dfs
            if(child->FirstChildElement())
            {
                auto tmp = get_all_by_tag(child, tag);
                SPDLOG_DEBUG("inserting {} elements", tmp.size());
                res.insert(res.end(), tmp.begin(), tmp.end());
            }
        }
        return res;
    }


    std::string strip_javascript(const std::string& html_raw)
    {
        // regex crashes on execution with segmentation fault
        std::regex r_scripts("<script.*?>(.|\\s)*?<\\/script>", std::regex_constants::optimize);
        try
        {
            const std::string res = std::regex_replace(html_raw, r_scripts, " ");
            SPDLOG_DEBUG("returning {}", res);
            return res;
        }catch(std::exception& e)
        {
            SPDLOG_ERROR(e.what());
        }
        SPDLOG_DEBUG("returning empty string");
        return "";
    }
}