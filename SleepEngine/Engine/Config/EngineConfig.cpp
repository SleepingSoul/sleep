// Copyright 2019 Taras Martyniuk
#include "stdafx.h"
#include "EngineConfig.h"
#include <Engine/Config/EngineConfig.h>
#include <Engine/Utils/file_utils.h>
#include <Engine/Utils/MacroUtils.h>

BEGIN_NAMESPACE_SLEEP

EngineConfig::EngineConfig()
    : Base(Base::getConfigTypeID<EngineConfig>())
{}

bool EngineConfig::doLoad()
{
    std::ifstream file(ConfigFile);
    nlohmann::json configJson;
    file >> configJson;

    if (configJson.is_null())
    {
        LOG_AND_FAIL_ERROR("could not parse config file");
        return false;
    }

    from_json(configJson, m_data);
    return true;
}

EngineConfigData const& EngineConfig::getData() const
{
    if (!isLoaded())
    {
        LOG_AND_FAIL_ERROR("config data not loaded");
    }
    return m_data;
}

END_NAMESPACE_SLEEP
