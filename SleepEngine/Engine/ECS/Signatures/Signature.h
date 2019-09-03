//
// Created by Taras Martyniuk on 7/27/2018.
//
#pragma once
#include "Settings.h"
#include "SignatureBitsetsStorage.h"

BEGIN_NAMESPACE_SLEEP

// when working with lists of class templates,
// brigand::find requires them to have a ::type field yielding their type
// the ordinary brigand::list does not conform to this,
// so it is impossible to perform search with nested lists
// this class is only adds the type field to the brigand::list, for that reason
template <class... T>
struct Signature
{
    using type = Signature<T...>;
};
END_NAMESPACE_SLEEP
