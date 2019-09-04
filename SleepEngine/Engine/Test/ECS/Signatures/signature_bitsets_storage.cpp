//
// Created by Taras Martyniuk on 7/27/2018.
//
#include <gtest/gtest.h>
#include "test_type_defs.h"
#include <Engine/ECS/signatures/SignatureBitsetsStorage.h>
using 
using namespace tmengine::ecs;
using namespace std;

class SignatureBitsetsStorageTest : public ::testing::Test {
protected:
    using Components = brigand::list<ComponentA, ComponentB, ComponentC>;
    using Tags = brigand::list<TagA, TagB>;
    using TestSignature = Signature<ComponentB, TagA>;
    using Signatures = brigand::list<TestSignature>;

    using TestSettings = Settings
        <Components,
            Tags,
            Signatures>;

    SignatureBitsetsStorage<TestSettings> test_bitset_storage_;
};

TEST_F(SignatureBitsetsStorageTest,
       NoMoreBitsAreSet_ThanSignatureTypesCount)
{
    static const auto kSignatureSize = brigand::size<TestSignature>::value;

    const auto& bitset = test_bitset_storage_.getSignatureBitset<TestSignature>();

    EXPECT_LE(bitset.count(), kSignatureSize);
}

TEST_F(SignatureBitsetsStorageTest,
       AllSignaturesBits_AreSet) {
    auto& bitset = test_bitset_storage_.getSignatureBitset<TestSignature>();

    int component_b_bit = 1;
    EXPECT_TRUE(bitset.test(component_b_bit));

    int tag_a_bit = 3;
    EXPECT_TRUE(bitset.test(tag_a_bit));
}













