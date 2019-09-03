//
// Created by Taras Martyniuk on 7/24/2018.
//
#pragma once
#include <brigand/algorithms.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types.hpp>

BEGIN_NAMESPACE_SLEEP

// register's user-defined Components, Tags and Signatures
// Signature must be a Signature template
// containing Components and Types, required by a system
template <typename TComponents,
          typename TTags,
          typename TSignatures>
class Settings
{
public:
    using Signatures = TSignatures;
    using Components = TComponents;
    using Tags = TTags;

    template <typename TList, typename T>
    using ContainsFilter = brigand::found<TList, std::is_same<T, brigand::_1>>;

    template <typename T>
    using IsComponentFilter = ContainsFilter<TComponents, T>;

    template <typename T>
    using IsTagFilter = ContainsFilter<TTags, T>;

    static constexpr unsigned componentCount() noexcept
    {
        return brigand::size<TComponents>::value;
    }

    static constexpr unsigned tagCount() noexcept
    {
        return brigand::size<TTags>::value;
    }

    static constexpr unsigned signatureCount() noexcept
    {
        return brigand::size<TSignatures>::value;
    }

    // fails at compile time if the TComponent is not a Component
    template <class TComponent>
    static constexpr std::size_t componentId()
    {
        static_assert(isComponent<TComponent>(), "TComponent must be in Settings::TComponents typelist");

        using index = brigand::index_of<TComponents, TComponent>;
        return index::value;
    }

    // fails at compile time if the TTag is not a Tag
    template <class TTag>
    static constexpr std::size_t tagId()
    {
        static_assert(isTag<TTag>(), "TTag must be in Settings::TTags typelist");

        using index = brigand::index_of<TTags, TTag>;
        return index::value;
    }

    // fails at compile time if the TSignature is not a Tag
    template <class TSignature>
    static constexpr std::size_t signatureId()
    {
        static_assert(isSignature<TSignature>(), "TSignature must be in Settings::TSignatures typelist");

        using index = brigand::index_of<TSignatures, TSignature>;
        return index::value;
    }

    template <typename T>
    static constexpr bool isComponent() noexcept { return contains<TComponents, T>(); }

    template <typename T>
    static constexpr bool isTag() noexcept { return contains<TTags, T>(); }

    template <typename T>
    static constexpr bool isSignature() noexcept { return contains<TSignatures, T>(); }

private:
    template <typename TList, typename T>
    static constexpr bool contains()
    {
        using found = ContainsFilter<TList, T>;
        return found::value;
    };
};
END_NAMESPACE_SLEEP
