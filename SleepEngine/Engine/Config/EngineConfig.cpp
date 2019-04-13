// Copyright 2019 Taras Martyniuk
#include "stdafx.h"
#include "EngineConfig.h"
#include <Engine/Config/EngineConfig.h>
#include <Engine/Utils/file_utils.h>
#include <Engine/Utils/MacroUtils.h>

BEGIN_NAMESPACE_SLEEP

void EngineConfig::Load()
{
    std::optional<std::string> configFileText = readFile(ConfigFile);

    if (!configFileText.has_value())
    {
        LOG_AND_ASSERT_ERROR("config file missing");
        return;
    }

    nlohmann::json configJson = nlohmann::json::parse(configFileText.value());
    from_json(configJson, m_data);
}

END_NAMESPACE_SLEEP
