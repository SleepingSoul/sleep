// Copyright 2019 Taras Martyniuk
#pragma once
#include <Engine/Config/EngineConfigData.h>

BEGIN_NAMESPACE_SLEEP

// loads config data from a file and stores it
class EngineConfig
{
public:
    SINGLETON_GETTER(EngineConfig)

    // parses config file
    void Load();
    EngineConfigData const& GetData() const;

private:
    EngineConfigData m_data;
    bool m_isLoaded = false;

    EngineConfig() = default;
};

END_NAMESPACE_SLEEP
