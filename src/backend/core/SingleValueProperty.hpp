//
// Created by parthu on 11/26/23.
//

#pragma once
#include <memory>
#include <type_traits>

#include <ArticlePropertyInterface.hpp>

template<typename T, typename DerivedClass>
requires std::is_copy_constructible_v<T> // required for constructor definition
/*!
 * \brief Simple Container for custom properties containing a single value. You must derive this class to generate a custom ArticlePropertyHash.
 * \note Don't delete the `DerivedConstructor(T)` - Function.
 * \note Don't store other members in your derived class. `copy_as_impl()` will only copy the given T value.
 * \tparam T Type to store in this container
 * \tparam DerivedClass used for curiously recurring template pattern
 */
class SingleValueProperty : public ArticlePropertyInterface
{
private:
    T value;
public:

    SingleValueProperty(T value)
        : value(std::move(value))
    {

    }

    [[nodiscard]] std::unique_ptr<ArticlePropertyInterface> copy_as_interface() const override
    {
        auto* copy = static_cast<DerivedClass*>(new SingleValueProperty<T, DerivedClass>(value));

        return std::unique_ptr<ArticlePropertyInterface>(copy);
    }

    const T& get() const
    {
        return value;
    }

    T& get()
    {
        return value;
    }

    void set(T value)
    {
        this->value = std::move(value);
    }
};