#pragma once
#include <Engine/Utils/json_serialize_utils.h>

BEGIN_NAMESPACE_SLEEP

struct EngineConfigData
{
    Layer MaxLayer = 0;
    size_t MeterLengthInPixels = 0;
    glm::vec2 PrimaryWindowSize;
};

static void from_json(nlohmann::json const& json, EngineConfigData& configData) 
{
    try
    {
        configData.MaxLayer = json.at("max_layer");
        configData.MeterLengthInPixels = json.at("meter_length_in_pixels");
        from_json(json.at("primary_window_size"), configData.PrimaryWindowSize);
    }
    catch (nlohmann::json::exception const&)
    {
        LOG_AND_ASSERT_ERROR("Error parsing config data json");
    }
}

END_NAMESPACE_SLEEP

