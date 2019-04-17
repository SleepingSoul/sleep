// Copyright 2019 Taras Martyniuk
#pragma once
#include <Engine/Config/BaseConfig.h>

BEGIN_NAMESPACE_SLEEP

// holds all configs
// register your configs here, than load them all at once
// TODO: define loaders at compile time as a typelist
class ConfigManager
{
public:
    // does not reload if they are already loaded
    void loadAllConfigs();

    void addConfig(std::unique_ptr<BaseConfig>&& config);

    template <class TConfig>
    void addConfig()
    {
        static_assert(std::is_default_constructible_v <TConfig>, "TConfig is not default constructible. Please, "
            "create an instance of this class and use non-templated 'addConfig' method.");
        addConfig(std::make_unique<TConfig>());
    }
    
    template <class TConfig>
    TConfig const* getConfig() 
    {
        TypeID const id = BaseConfig::getConfigTypeID<TConfig>();

        auto isOurTypeId = [id](std::unique_ptr<BaseConfig> const& config)
        {
            return config->getTypeId() == id;
        };

        auto it = std::find_if(m_configs.cbegin(), m_configs.cend(), isOurTypeId);
        
        if (it == m_configs.cend())
        {
            FAIL_ASSERT("object does not have a component of that type");
            return nullptr;
        }

        return static_cast <TConfig*>(it->get());
    }

private:
    std::vector<std::unique_ptr<BaseConfig>> m_configs;
};

END_NAMESPACE_SLEEP