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
                res.insert(res.end(), tmp.begin(), tmp.end());
            }
        }
        return res;
    }


    std::string strip_tag(std::string html_raw, const std::string& tag)
    {
        const static std::vector<std::string_view> selfclosing_tags = {
                "link", "base", "br", "col", "embed", "hr", "img", "input",
                "meta", "param", "source", "track", "wbr", "colgroup"
        };

        if(std::find(selfclosing_tags.begin(), selfclosing_tags.end(), tag) != selfclosing_tags.end())
        {
            SPDLOG_DEBUG("{} is a selfclosing tag. Will remove <{}...> elements before proceeding with normal regex.", tag, tag);

            std::regex r_selfclosing_tag{fmt::format("<{}[^]*?>", tag)};

            std::smatch match;
            while(std::regex_search(html_raw, match, r_selfclosing_tag))
            {
                const std::size_t start = match.position();
                const std::size_t n = match.length();

                SPDLOG_TRACE("Removing {} chars from {}:\n{}", n, start, html_raw.substr(start, n));
                html_raw.replace(start, n, "");
            }

        }

        std::regex r_start_tag{fmt::format("<{}[^>]*>", tag)};       // match all start tags
        std::regex r_close_tag{fmt::format("</{}[^>]*>", tag)};       // match all close tags
        std::regex r_standalone_tag{fmt::format("<{}[^>]*/>", tag)};// match all standalone tags

        //html_raw = std::regex_replace(html_raw, r_standalone_tag, "");

        std::smatch match_standalone;
        while(std::regex_search(html_raw, match_standalone, r_standalone_tag))
        {
            const std::size_t start = match_standalone.position();
            const std::size_t n = match_standalone.length();

            SPDLOG_TRACE("Removing {} chars from {}:\n{}", n, start, html_raw.substr(start, n));
            html_raw.replace(start, n, "");
        }

        // for enclosing tags we want to delete everything within
        std::smatch match_begin;
        std::smatch match_close;
        while(std::regex_search(html_raw, match_begin, r_start_tag))
        {
            if(!std::regex_search(html_raw, match_close, r_close_tag))
            {
                SPDLOG_CRITICAL("Tag {} opened but no regex match for closing tag. Content:\n{}", tag, html_raw.substr(match_begin.position()));
            }

            const std::size_t start = match_begin.position();
            const std::size_t n = match_close.position() - start + match_close.length();

            SPDLOG_TRACE("Removing {} chars from {}:\n{}", n, start, html_raw.substr(start, n));

            html_raw.replace(start, n, "");
        }

        return html_raw;
    }
}