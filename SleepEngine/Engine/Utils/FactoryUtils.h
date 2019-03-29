//Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

inline std::unique_ptr <Object> createRenderableObject()
{
    auto object = std::make_unique <Object>();

    object->addComponent <Renderer>();
    object->addComponent <Transform2D>();

    return object;
}

EndNamespaceSleep
