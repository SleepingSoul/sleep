// Copyright 2019 Tihran Katolikian

#pragma once

#define assertion(condition, message)\
assert((message, condition))

#define logAndAssertError(condition, message)\
if (!condition)\
{\
    spdlog::get(slp::EngineLogger)->error(message);\
    assertion(condition, message);\
}

#define ForbidCopy(classname)\
classname(classname const&) = delete;\
classname& operator =(classname const&) = delete;

#define ForbidMove(classname)\
classname(classname&&) = delete;\
classname& operator =(classname&&) = delete;

#define ForbidCopyAndMove(classname)\
ForbidCopy(classname)\
ForbidMove(classname)

#define REF_GETTERS(getterName, member) GETTERS(auto&, getterName, member)

#define GETTERS(type, getterName, member)\
type getterName() { return member; }\
const type getterName() const { return member; }


#define BeginNamespaceSleep namespace slp{
#define EndNamespaceSleep }
