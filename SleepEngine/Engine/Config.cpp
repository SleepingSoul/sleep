#include "stdafx.h"
#include "Config.h"
#include <Engine/Utils/file_utils.h>

Config& Config::Instance()
{
    static Config instance;
    return instance;
}

void Config::Load()
{
    std::optional<std::string> configFileText = ReadFile(ConfigFiles::Weapon);

    if (!configFileText.has_value())
    {
        LogError("weapon config file missing");
        return;
    }

    auto configJson = nlohmann::json::parse(configFileText.value());
    m_configEntries = JsonToMap<WeaponConfigData>(configJson);
}

