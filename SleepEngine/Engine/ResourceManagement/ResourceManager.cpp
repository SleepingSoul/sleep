#include "stdafx.h"
#include "ResourceManager.h"

BEGIN_NAMESPACE_SLEEP

Texture* ResourceManager::getTexture(Textures texture)
{
    std::lock_guard lk(m_mutex);
    auto it = m_textures.find(texture);
    if (it == m_textures.cend())
    {
        LOG_AND_ASSERT_ERROR(false, "No texture found. Maybe you forgot to call preload()?");
        return nullptr;
    }
    return it->second.get();
}

void ResourceManager::preload()
{
    loadResourceTable();

    for (auto const& item : m_resourceTable.items())
    {
        std::lock_guard lk(m_mutex);
        m_textures.emplace(static_cast <Textures>(std::stoi(item.key())),
            std::make_unique <Texture>(item.value().get <std::string>().c_str()));
    }
}

void ResourceManager::loadResourceTable()
{
    std::ifstream file(Resources::ImagesTablePath);
    file >> m_resourceTable;
}

END_NAMESPACE_SLEEP
