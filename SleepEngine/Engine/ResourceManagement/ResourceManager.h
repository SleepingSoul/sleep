// Copyright 2019 Tihran Katolikian
// do not include this file to stdafx, because it will change every time used adds any data.

#pragma once

#include <Engine/Generated/all_textures.hpp>

BEGIN_NAMESPACE_SLEEP

class ResourceManager
{
public:
    using TexturesContainerType = std::unordered_map <Textures, std::unique_ptr <Texture>>;
    using FutureType = std::future <bool>;

    Texture* getTexture(Textures texture);
    void preload();

private:
    void loadResourceTable();

    mutable std::mutex m_mutex;
    TexturesContainerType m_textures;
    nlohmann::json m_resourceTable;
};

END_NAMESPACE_SLEEP
