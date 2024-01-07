//
// Created by parthu on 12/19/23.
//
#pragma once

#include <core/db/database_types.hpp>
#include <core/ArticlePropertyHash.hpp>

template<typename T>
SerializedMapping serialize_mapping() = delete;

template<typename T>
SerializedValues serialize(const T& obj) = delete;

template<typename T>
std::optional<T> deserialize(const SerializedValues& obj) = delete;

template<typename T>
std::string table_name() = delete;

/*!
 * \note Apply this concept after overloading functions. Otherwise the call to decltype() will default to base templates
 */
template<typename T>
concept PropertyIsSerializable = requires()
{
    requires std::derived_from<T, ArticlePropertyInterface>;
    requires std::invocable<decltype(serialize_mapping<T>)>;
    requires std::invocable<decltype(serialize<T>), T>;
    requires std::invocable<decltype(deserialize<T>), SerializedValues>;
};

template<typename T>
concept PropertyIsStorable = requires()
{
    requires PropertyIsSerializable<T>;
    requires std::invocable<decltype(table_name<T>)>;
};

#if false
// Reflection, at this point we can't call it hash
static std::unordered_map<ArticlePropertyHash, std::function<SerializedValues(ArticlePropertyInterface*)>> unhash_funcs;

template<typename T>
requires PropertyIsStorable<T>
void allow_unhash()
{
    constexpr ArticlePropertyHash hash = ArticlePropertyHash::create<T>();
    if(unhash_funcs.contains(hash))
    {
        SPDLOG_WARN("Unhash-function for {} already exists", typeid(T).name());
        return;
    }

    unhash_funcs[hash] = [](ArticlePropertyInterface* interface) -> SerializedValues
    {
        auto ptr = dynamic_cast<T*>(interface);
        assert(ptr);
        return serialize(ptr);
    };

    SPDLOG_DEBUG("Registered unhash-function for {}", typeid(T).name());
}

#endif