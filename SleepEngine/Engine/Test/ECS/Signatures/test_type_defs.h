//
// Created by Taras Martyniuk on 7/25/2018.
//
#pragma once

#include <brigand/sequences/list.hpp>
#include <Engine/ECS/ecs.h>

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

