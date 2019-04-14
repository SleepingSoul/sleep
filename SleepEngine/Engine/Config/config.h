// Copyright 2019, Tihran Katolikian

#pragma once
#include <Engine/Utils/MacroUtils.h>


BEGIN_NAMESPACE_SLEEP

// logger info and any paths for dynamic loading should be here, 
// but all data that can be retrieved dynamically should be in EngineConfig isntead
static auto EngineLogger = "engine_logger";
static auto EngineLoggerPath = "Logs/engine_logger.log";
static auto ConfigFile = "Engine/Config/config.json";

namespace Resources
{
    static auto ImagesTablePath = "Engine/Generated/textures_table.json";
}

END_NAMESPACE_SLEEP
