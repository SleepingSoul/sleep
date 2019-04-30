// Copyright 2019 Tihran Katolikian
#include <Engine/Config/config.h>
#pragma once

#pragma region LogAssert
#define assertion(condition, message)\
assert((message, condition))

#define FAIL_ASSERT(message) assertion(false, message)

#define LOG_ERROR(message, ...) spdlog::get(slp::EngineLogger)->error(message, __VA_ARGS__);\

#define LOG_AND_ASSERT_ERROR(condition, message, ...)\
if (!(condition))\
{\
    LOG_ERROR(message, __VA_ARGS__)\
    assertion(condition, message);\
}

#define LOG_AND_FAIL(message, ...) LOG_AND_ASSERT_ERROR(false, message, __VA_ARGS__);

#pragma endregion

#define FORBID_COPY(classname)\
classname(classname const&) = delete;\
classname& operator =(classname const&) = delete;

#define FORBID_MOVE(classname)\
classname(classname&&) = delete;\
classname& operator =(classname&&) = delete;

#define FORBID_COPY_AND_MOVE(classname)\
FORBID_COPY(classname)\
FORBID_MOVE(classname)

#define SINGLETON_GETTER(class_)\
static class_& instance()\
{\
    static class_ instance;\
    return instance;\
}\

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

#define COMPONENT_SHORTCUTS(componentType, shortcutName)\
inline componentType* shortcutName##Ptr(Object* obj)  \
{   \
    return obj->getComponent<componentType>();  \
}   \
    \
inline componentType* shortcutName##Ptr(Object& obj)  \
{   \
    return shortcutName##Ptr(&obj);  \
}   \
    \
inline componentType& shortcutName(Object* obj) \
{   \
    return *shortcutName##Ptr(obj);  \
}   \
    \
inline componentType& shortcutName(Object& obj)  \
{   \
    return shortcutName(&obj);  \
}   \
    \
    \
    \
inline componentType const* shortcutName##Ptr(Object const* obj)  \
{   \
    return shortcutName##Ptr(obj);  \
}   \
    \
inline componentType const* shortcutName##Ptr(Object const& obj)  \
{   \
    return shortcutName##Ptr(obj);  \
}   \
    \
inline componentType const& shortcutName(Object const& obj)  \
{   \
    return shortcutName(obj);\
}   \
    \
inline componentType const& shortcutName(Object const* obj) \
{   \
    return shortcutName(obj);  \
}   \
    \

#define All(container) std::begin(container), std::end(container)
#define C_All(container) std::cbegin(container), std::cend(container)

#define BEGIN_NAMESPACE_SLEEP namespace slp{
#define END_NAMESPACE_SLEEP }
