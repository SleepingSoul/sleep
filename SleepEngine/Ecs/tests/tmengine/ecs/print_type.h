//
// Created by Taras Martyniuk on 7/25/2018.
//
#ifndef SFML_GAME_ENGINE_PRINT_TYPE_H
#define SFML_GAME_ENGINE_PRINT_TYPE_H
#include <ecs/signatures/brigand_type_macro.h>
#include <cxxabi.h> // the libstdc++ used by g++ does contain this header

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

#endif //SFML_GAME_ENGINE_PRINT_TYPE_H
