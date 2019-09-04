//
// Created by Taras Martyniuk on 7/25/2018.
//
#include "test_type_defs.h"
#include <Engine/ECS/signatures/SignatureBitsets.h>
using namespace tmengine::ecs;

namespace tests::tmengine::ecs {
namespace {
using Components = brigand::list<ComponentB, ComponentC>;
using Tags = brigand::list<TagB>;

using Signature = brigand::list<ComponentC, TagB>;
using Signatures = brigand::list<Signature>;

using TestSettings = Settings<
    Components,
    Tags,
    Signatures>;

using TestBitsets = SignatureBitsets<TestSettings>;


using FilteredComponents = TestBitsets::SignatureComponents<Signature>;
static_assert(std::is_same<FilteredComponents, brigand::list<ComponentC>>::value,
              "TestBitsets_SignatureComponents");

using FilteredTags = TestBitsets::SignatureTags<Signature>;
static_assert(std::is_same<FilteredTags, brigand::list<TagB>>::value,
              "TestBitsets_SignatureTags");


static_assert(TestBitsets::componentBit<ComponentC>() == 1,
              "TestBitsets_ComponentBit");

static_assert(TestBitsets::tagBit<TagB>() == 2,
              "TestBitsets_TagBit");

} // namespace

TEST(SignatureBitsets, Size) {
    TestBitsets::Bitset bitset;

    EXPECT_EQ(bitset.size(), 3);
}
} // namespace tests::tmengine::ecs
