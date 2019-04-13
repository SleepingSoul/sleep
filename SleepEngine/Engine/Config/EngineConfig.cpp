// Copyright 2019 Taras Martyniuk
#include "stdafx.h"
#include "EngineConfig.h"
#include <Engine/Config/EngineConfig.h>
#include <Engine/Utils/file_utils.h>
#include <Engine/Utils/MacroUtils.h>

BEGIN_NAMESPACE_SLEEP

void EngineConfig::Load()
{
    std::ifstream file(ConfigFile);
    nlohmann::json configJson;
    file >> configJson;

    if (configJson.is_null())
    {
        LOG_AND_ASSERT_ERROR("could not parse config file");
        return;
    }

    from_json(configJson, m_data);
}

END_NAMESPACE_SLEEP
