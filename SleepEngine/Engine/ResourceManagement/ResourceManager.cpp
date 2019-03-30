#include "stdafx.h"
#include "ResourceManager.h"


BEGIN_NAMESPACE_SLEEP

Texture* ResourceManager::getTexture(std::string const& path)
{
    std::lock_guard lk(m_mutex);
    auto it = m_textures.find(path);
    if (it == m_textures.cend())
    {
        return m_textures.emplace(path, std::make_unique <Texture>(path.c_str())).first->second.get();
    }
    return it->second.get();
}

ResourceManager::FutureType ResourceManager::preloadFromDirectory(std::string_view const path, bool const recursive)
{
    auto preload = [this, path, recursive]
    {
        if (!std::filesystem::exists(path))
        {
            logAndAssertError(false, "Directory not exists");
            return false;
        }

        if (!recursive)
        {
            auto dir = std::filesystem::directory_iterator(path);
            for (auto const& entry : dir)
            {
                std::lock_guard lk(m_mutex);
                auto path = entry.path().string();

                m_textures.emplace(path, std::make_unique <Texture>(path.c_str()));
            }
        }
        else
        {
            auto dir = std::filesystem::recursive_directory_iterator(path);
            for (auto const& entry : dir)
            {
                std::lock_guard lk(m_mutex);
                auto path = entry.path().string();

                m_textures.emplace(path, std::make_unique <Texture>(path.c_str()));
            }
        }

        return true;
    };

    return std::async(std::launch::async, preload);
}

EndNamespaceSleep
