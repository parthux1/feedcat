//
// Created by parthu on 11/19/23.
//
#pragma once

#include <concepts>
#include <typeinfo>

#include <ArticlePropertyInterface.hpp>

/*!
 * \brief This class constrains typeid hashes to be from a class derived from ArticlePropertyInterface
 * \note Hash is distinct for each derived class, not for each instance of the same class.
 * \note typeid differs for T* and T.
 * \note Because the hash can be created via class-template or instance when updating the hash definition one must update both constructors.
 * \see ArticlePropertyInterface
 */

class ArticlePropertyHash
{
private:
    /*!
     * \brief Use ArticlePropertyHash::create<T>()
     */
    ArticlePropertyHash(std::size_t value);
public:
    template<typename T>
    requires std::derived_from<T, ArticlePropertyInterface>
    explicit ArticlePropertyHash(const T* property)
    {
        value = typeid(T).hash_code();
    }

    ~ArticlePropertyHash() = default;

public:
    bool operator==(const ArticlePropertyHash& other) const;

    bool operator!=(const ArticlePropertyHash& other) const;

public:

    /*!
     * \brief Creates a hash from a class derived from ArticlePropertyInterface
     * @tparam T Class to create hash from
     * @return Hash
     */
    template<typename T>
        requires std::derived_from<T, ArticlePropertyInterface>
    static ArticlePropertyHash create()
    {
        return ArticlePropertyHash{typeid(T).hash_code()};
    }

    [[nodiscard]] const std::size_t& get() const;

private:
    std::size_t value;
};


/*
 * Implement std::hash functionality, so we can use ArticlePropertyHash as a key in std::unordered_map
 */
template <>
struct std::hash<ArticlePropertyHash>
{
    std::size_t operator()(const ArticlePropertyHash& k) const
    {
        return k.get();
    }
};