//
// Created by Taras Martyniuk on 7/25/2018.
//
#pragma once

#include <Engine/ECS/signatures/brigand_type_macro.h>

namespace tests::tmengine::ecs {
    template <typename T>
    void printType(const T *addr)
    {
        char * name = abi::__cxa_demangle(typeid(*addr).name(), 0, 0, nullptr);
        printf("type is: %s\n", name);
        free(name);
    }

    template<typename TBrigandType>
    void printBrigandType(TBrigandType brigandType) {
        printType(new BRIGAND_TYPE(brigandType));
    }
}


