//
// Created by Taras Martyniuk on 7/25/2018.
//
#include <ecs/signatures/SignatureBitsets.h>
#include "test_type_defs.h"
using namespace tmengine::ecs;

namespace tests::tmengine::ecs
{
    namespace
    {
        using Components = brigand::list<ComponentB, ComponentC>;
        using Tags = brigand::list<TagB>;

        using Signature = brigand::list<ComponentC, TagB>;
        using Signatures = brigand::list<Signature>;

        using TestSettings = Settings<
                Components,
                Tags,
                Signatures>;

        using TestBitsets = SignatureBitsets<TestSettings>;

        //region filtering

        using FilteredComponents = TestBitsets::SignatureComponents<Signature>;
        static_assert(std::is_same<FilteredComponents, brigand::list<ComponentC>>::value,
                      "TestBitsets_SignatureComponents");

        using FilteredTags = TestBitsets::SignatureTags<Signature>;
        static_assert(std::is_same<FilteredTags, brigand::list<TagB>>::value,
                      "TestBitsets_SignatureTags");
        //endregion
        //region bits

        static_assert(TestBitsets::componentBit<ComponentC>() == 1,
                      "TestBitsets_ComponentBit");

        static_assert(TestBitsets::tagBit<TagB>() == 2,
                      "TestBitsets_TagBit");
        //endregion
    }

    TEST(SignatureBitsets, Size)
    {
        TestBitsets::Bitset bitset;

        EXPECT_EQ(bitset.size(), 3);
    }
}

