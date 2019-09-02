//
// Created by Taras Martyniuk on 7/24/2018.
//
#include <ecs/ecs.h>
#include <test_type_defs.h>

using namespace tmengine::ecs;
using namespace std;

namespace tests::tmengine::ecs
{
    //region defs

    using Components = brigand::list<ComponentA, ComponentB, ComponentC>;
    using Tags = brigand::list<TagA, TagB>;
    using Signatures = brigand::list<SignatureA>;

    static const int kComponentsSize = 3;
    static const int kTagsSize = 2;
    static const int kSignaturesSize = 1;

    using TestSettings = Settings
            <Components,
                    Tags,
                    Signatures>;
    //endregion

    //region type checking

    static_assert(TestSettings::isComponent<ComponentA>(),
                  "IsComponent_True_ForComponentType");
    static_assert(! TestSettings::isComponent<TagA>(),
                  "IsComponent_False_ForWrongType");

    static_assert(TestSettings::isTag<TagB>(),
                  "IsTag_True_ForTagType");
    static_assert(! TestSettings::isTag<ComponentB>(),
                  "IsTag_False_ForWrongType");

    static_assert(TestSettings::isSignature<SignatureA>(),
                  "IsSignature_True_ForSignatureType");
    static_assert(! TestSettings::isSignature<TagB>(),
                  "IsSignature_False_ForWrongType");
    //endregion

    //region size
    static_assert(TestSettings::componentCount() == kComponentsSize,
                  "ComponentCount");

    static_assert(TestSettings::tagCount() == kTagsSize,
                  "TagCount");

    static_assert(TestSettings::signatureCount() == kSignaturesSize,
                  "SignatureCount");

    //endregion


    //region ids
    static_assert(TestSettings::componentId<ComponentB>() == 1,
                  "ComponentId");

    static_assert(TestSettings::tagId<TagA>() == 0,
                  "TagId");

    static_assert(TestSettings::signatureId<SignatureA>() == 0,
                  "SignatureId");

    //endregion
    //endregion
}
