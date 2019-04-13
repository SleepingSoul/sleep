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

#define FORBID_COPY(classname)\
classname(classname const&) = delete;\
classname& operator =(classname const&) = delete;

#define FORBID_MOVE(classname)\
classname(classname&&) = delete;\
classname& operator =(classname&&) = delete;

#define FORBID_COPY_AND_MOVE(classname)\
FORBID_COPY(classname)\
FORBID_MOVE(classname)

#pragma region GettersSetters

#define __GETTER_IMPL(rtype, getterName, member)\
rtype getterName() { return member; }

#define __CONST_GETTER_IMPL(rtype, getterName, member)\
rtype getterName() const { return member; }

#define __SETTER_IMPL(paramType, setterName, member)\
void setterName(paramType value) { member = value; }

#define CONST_REF_GETTER(getterName, member)\
__CONST_GETTER_IMPL(auto&, getterName, member)

#define REF_GETTER(getterName, member)\
__GETTER_IMPL(auto&, getterName, member)

#define GETTER(getterName, member)\
__CONST_GETTER_IMPL(auto, getterName, member)

#define REF_GETTERS(getterName, member)\
CONST_REF_GETTER(getterName, member)\
REF_GETTER(getterName, member)

#define CONST_REF_SETTER(paramType, setterName, member)\
__SETTER_IMPL(paramType const&, setterName, member)

#define SETTER(paramType, setterName, member)\
__SETTER_IMPL(paramType, setterName, member)

#define GET_SET(type, getterName, setterName, member)\
GETTER(getterName, member)\
SETTER(type, setterName, member)

#define REF_GET_SET(type, getterName, setterName, member)\
CONST_REF_GETTER(getterName, member)\
CONST_REF_SETTER(type, setterName, member)

#pragma endregion

#define BEGIN_NAMESPACE_SLEEP namespace slp{
#define END_NAMESPACE_SLEEP }
