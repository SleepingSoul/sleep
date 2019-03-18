#pragma once

// loads config data from a file and stores it
class Config
{
public:
    static Config& Instance();
    
    // parses config file, adding entries to map
    void Load();

    // json entry for weaponName must be in config file, and it must be loaded
    // otherwise, default initialized entry is created and returned
    WeaponConfigData const& GetWeaponData(std::string const& weaponName);

private:
    using ConfigMap = std::unordered_map <std::string, WeaponConfigData>;
    ConfigMap m_configEntries;

    WeaponConfig() = default;
};
