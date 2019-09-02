//
// Created by Taras Martyniuk on 7/25/2018.
//
#ifndef SFML_GAME_ENGINE_TEST_TYPE_DEFS_H
#define SFML_GAME_ENGINE_TEST_TYPE_DEFS_H
#include <brigand/sequences/list.hpp>
#include <ecs/ecs.h>

namespace tests::tmengine::ecs {

    struct ComponentA {};
    struct ComponentB {};
    struct ComponentC {};

    struct TagA {};
    struct TagB {};
    struct TagC {};

    using SignatureA = ::tmengine::ecs::Signature<ComponentA, TagB>;

//    struct SignatureA {};

    using AllComponents = brigand::list<ComponentA, ComponentB, ComponentC>;
    using AllTags = brigand::list<TagA, TagB, TagC>;
}
#endif //SFML_GAME_ENGINE_TEST_TYPE_DEFS_H
