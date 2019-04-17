// Copyright 2019 Taras Martyniuk
#pragma once
#include <Engine/Config/EngineConfigData.h>
#include <Engine/Config/BaseConfig.h>

BEGIN_NAMESPACE_SLEEP

// loads config data from a file and stores it
// TODO: make generic deserialize to struct config
class EngineConfig : public BaseConfig
{
    using Base = BaseConfig;
public:
    EngineConfig();
    EngineConfigData const& getData() const;

protected:
    bool doLoad() override;

private:
    EngineConfigData m_data;
};

END_NAMESPACE_SLEEP
