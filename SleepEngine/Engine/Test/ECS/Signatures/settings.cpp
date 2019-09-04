#include "stdafx.h"
#include "test_type_defs.h"
#include <Engine/ECS/Signatures/Settings.h>

BEGIN_NAMESPACE_SLEEP_TEST
namespace
{

using Components = brigand::list<ComponentA, ComponentB, ComponentC>;
using Tags = brigand::list<TagA, TagB>;
using Signatures = brigand::list<SignatureA>;

static const int kComponentsSize = 3;
static const int kTagsSize = 2;
static const int kSignaturesSize = 1;

using TestSettings = Settings<Components,
                              Tags,
                              Signatures>;

static_assert(TestSettings::isComponent<ComponentA>(),
              "IsComponent_True_ForComponentType");
static_assert(!TestSettings::isComponent<TagA>(),
              "IsComponent_False_ForWrongType");

static_assert(TestSettings::isTag<TagB>(),
              "IsTag_True_ForTagType");
static_assert(!TestSettings::isTag<ComponentB>(),
              "IsTag_False_ForWrongType");

static_assert(TestSettings::isSignature<SignatureA>(),
              "IsSignature_True_ForSignatureType");
static_assert(!TestSettings::isSignature<TagB>(),
              "IsSignature_False_ForWrongType");


static_assert(TestSettings::componentCount() == kComponentsSize,
              "ComponentCount");
static_assert(TestSettings::tagCount() == kTagsSize,
              "TagCount");
static_assert(TestSettings::signatureCount() == kSignaturesSize,
              "SignatureCount");


static_assert(TestSettings::componentId<ComponentB>() == 1,
              "ComponentId");
static_assert(TestSettings::tagId<TagA>() == 0,
              "TagId");
static_assert(TestSettings::signatureId<SignatureA>() == 0,
              "SignatureId");
} // namespace
END_NAMESPACE_SLEEP_TEST
