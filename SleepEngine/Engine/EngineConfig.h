// Copyright 2019, Tihran Katolikian

#pragma once

#include <Engine/Utils/MacroUtils.h>
#include <Engine/SleepTypes.h>

BeginNamespaceSleep

static Layer const MaxLayer = 99;
static size_t const MeterLengthInPixels = 100;
static glm::vec2 const PrimaryWindowSize(1024.f, 1024.f);

static auto EngineLogger = "engine_logger";
static auto EngineLoggerPath = "Logs/engine_logger.log";

EndNamespaceSleep
