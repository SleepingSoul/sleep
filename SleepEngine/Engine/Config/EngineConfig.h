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
	CONST_REF_GETTER(GetData, m_data)

private:
	EngineConfigData m_data;

    EngineConfig() = default;
};

END_NAMESPACE_SLEEP
