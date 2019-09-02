#include "gtest/gtest.h"

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {

protected:

    // You can do set-up work for each tests here.
    FooTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~FooTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each tests, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each tests).
    virtual void SetUp();

    // Code here will be called immediately after each tests (right
    // before the destructor).
    virtual void TearDown();
};
