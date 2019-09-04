#pragma once

#include <Engine/ECS/Signatures/Settings.h>
#include <Engine/ECS/Signatures/Signature.h>
#include <brigand/sequences/list.hpp>

BEGIN_NAMESPACE_SLEEP_TEST

struct ComponentA
{};
struct ComponentB
{};
struct ComponentC
{};

struct TagA
{};
struct TagB
{};
struct TagC
{};

using SignatureA = slp::Signature<ComponentA, TagB>;

//    struct SignatureA {};

using AllComponents = brigand::list<ComponentA, ComponentB, ComponentC>;
using AllTags = brigand::list<TagA, TagB, TagC>;
END_NAMESPACE_SLEEP_TEST
