#pragma once
// shortcuts for long trains of functions for game's members
#include <Engine/Config/EngineConfig.h>

BEGIN_NAMESPACE_SLEEP

inline ConfigManager& globalConfigManager()
{
    return Game::instance().getConfigManager();
}

inline EngineConfig const* globalEngineConfig()
{
    return globalConfigManager().getConfig<EngineConfig>();
}

inline ResourceManager& globalResourceManager()
{
    return Game::instance().getResourceManager();
}

inline Game::Scene& currentScene()
{
    return Game::instance().getCurrentScene();
}

END_NAMESPACE_SLEEP
