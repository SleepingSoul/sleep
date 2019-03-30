// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class ResourceManager
{
public:
    using TexturesContainerType = std::unordered_map <std::string, std::unique_ptr <Texture>>;
    using FutureType = std::future <bool>;

    // can't use string_view because .find not works
    Texture* getTexture(std::string const& path);
    FutureType preloadFromDirectory(std::string_view path, bool recursive = false);

private:
    mutable std::mutex m_mutex;
    TexturesContainerType m_textures;
};

END_NAMESPACE_SLEEP
