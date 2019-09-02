#include <iostream>
#include "testfoo.h"
using namespace std;

FooTest::FooTest() {

    cout << "changed";
}

FooTest::~FooTest() {};

void FooTest::SetUp() {};

void FooTest::TearDown() {};



