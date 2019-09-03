// Copyright 2019, Tihran Katolikian

#pragma once
#include <Engine/Utils/MacroUtils.h>


BEGIN_NAMESPACE_SLEEP

// logger info and any paths for dynamic loading should be here, 
// but all data that can be retrieved dynamically should be in EngineConfig instead
static auto EngineLogger = "engine_logger";
static auto EngineLoggerPath = "Logs/slp_logger.log";
static auto ConfigFile = "Config/slp_config.json";
static auto VertexShader = "Generated/Shaders/shader.vs";
static auto FragmentShader = "Generated/Shaders/shader.fs";

namespace Resources
{
    static auto ImagesTablePath = "Generated/textures_table.json";
}

END_NAMESPACE_SLEEP
