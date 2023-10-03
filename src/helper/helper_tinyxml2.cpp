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


    std::string strip_javascript(std::string html_raw)
    {
        // regex crashes on execution with segmentation fault. The file may be too long
        //std::regex r_scripts("<script.*?>(.|\\s)*?<\\/script>", std::regex_constants::optimize);
        // we thus remove script tokens the manual way..

        const static std::vector<std::string> tokens{"<script", "</script", ">"};
        auto token = tokens.begin(); // currently handled token

        std::size_t offset_parser = 0; // current parser position
        std::size_t offset_first_token = 0; // position of currently found <script
        bool reset_pos = false;
        while(html_raw.find(*tokens.begin(), 0) != std::string::npos) // run as long <script tokens exist
        {
            const auto pos = html_raw.find(*token, offset_parser); // pos does not start at offset_parser

            if(pos == std::string::npos) break;

            if(token == tokens.begin())
            {
                offset_first_token = pos;
            }
            // remove everything
            else if(token == tokens.end()-1)
            {
                const std::size_t amount = (pos-offset_first_token)+1;
                html_raw.replace(offset_first_token, amount, "");
                reset_pos = true;
            }
            offset_parser = pos;

            // update states
            if(reset_pos)
            {
                reset_pos = false;
                offset_parser = 0;
                offset_first_token = 0;
            }
            if(++token == tokens.end()) token = tokens.begin();
        }
        return html_raw;
    }
}