#pragma once
#include <Engine/ECS/signatures/brigand_type_macro.h>


template <typename T>
void printType(const T* addr)
{
    char* name = abi::__cxa_demangle(typeid(*addr).name(), 0, 0, nullptr);
    printf("type is: %s\n", name);
    free(name);
}

template <typename TBrigandType>
void printBrigandType(TBrigandType brigandType)
{
    printType(new BRIGAND_TYPE(brigandType));
}
