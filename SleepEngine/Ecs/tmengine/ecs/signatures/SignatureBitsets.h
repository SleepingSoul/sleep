//
// Created by Taras Martyniuk on 7/25/2018.
//
#ifndef SFML_GAME_ENGINE_SIGNATUREBITSETS_H
#define SFML_GAME_ENGINE_SIGNATUREBITSETS_H
#include "brigand/sequences.hpp"
#include "Settings.h"
#include <brigand/algorithms.hpp>
#include <brigand/sequences.hpp>
#include <c++/5/cstdio>
#include <c++/5/cstdlib>
#include <bitset>

namespace tmengine::ecs {
    // builds the signature bitset type
    // provides info for SignatureBitsetsStorage to initialize bitsets for signatures at runtime
    template <class TSettings>
    class SignatureBitsets
    {
    private:
        template<typename T>
        using ComponentFilter = typename TSettings::template IsComponentFilter<T>;
        using ComponentFilterLambda = brigand::bind<ComponentFilter, brigand::_1>;

        template<typename T>
        using TagFilter = typename TSettings::template IsTagFilter<T>;
        using TagFilterLambda = brigand::bind<TagFilter, brigand::_1>;

    public:
        using Bitset = std::bitset<
                TSettings::componentCount() +
                TSettings::tagCount()>;

        // bit that identifies the component in the signature
        template <class TComponent>
        static constexpr std::size_t componentBit()
        {
            return TSettings::template componentId<TComponent>();
        }

        // bit that identifies the tag in the signature
        template <class TTag>
        static constexpr std::size_t tagBit()
        {
            return TSettings::componentCount() +
                    TSettings::template tagId<TTag>();
        }

        // list of components for signature
        template<typename TSignature>
        using SignatureComponents = brigand::filter<
                TSignature, ComponentFilterLambda>;

        // list of tags for signature
        template<typename TSignature>
        using SignatureTags = brigand::filter<
                TSignature, TagFilterLambda>;
    };
}
#endif //SFML_GAME_ENGINE_SIGNATUREBITSETS_H
