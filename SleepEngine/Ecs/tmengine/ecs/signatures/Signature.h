//
// Created by Taras Martyniuk on 7/27/2018.
//
#ifndef SFML_GAME_ENGINE_SIGNATURE_H
#define SFML_GAME_ENGINE_SIGNATURE_H
#include "_G_config.h"
#include "Settings.h"
#include "SignatureBitsetsStorage.h"

namespace tmengine::ecs
{
    // when working with lists of class templates,
    // brigand::find requires them to have a ::type field yielding their type
    // the ordinary brigand::list does not conform to this,
    // so it is impossible to perform search with nested lists
    // this class is only adds the type field to the brigand::list, for that reason
    template<class... T>
    struct Signature
    {
        using type = Signature<T...>;
    };
}

#endif //SFML_GAME_ENGINE_SIGNATURE_H
