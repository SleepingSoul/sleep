#include "stdafx.h"
#include "ConfigManager.h"

BEGIN_NAMESPACE_SLEEP

void ConfigManager::loadAllConfigs()
{
    for(auto& config : m_configs)
    {
        if (!config->isLoaded())
        {
            config->load();
        }
    }
}

void ConfigManager::addConfig(std::unique_ptr<BaseConfig> config)
{
    m_configs.emplace_back(std::move(config));
}

END_NAMESPACE_SLEEP
