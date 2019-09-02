#include "gtest/gtest.h"
#include <print_type.h>
#include <test_type_defs.h>
#include <iostream>
#include <ecs/signatures/SignatureBitsetsStorage.h>
#include <brigand/types.hpp>
#include <brigand/algorithms.hpp>
#include <brigand/types/type.hpp>

using namespace tests::tmengine::ecs;
using namespace tmengine::ecs;
using namespace std;

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

