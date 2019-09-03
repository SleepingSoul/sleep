#pragma once
#include <Engine/Config/JsonConfig.h>

// need to define unique class, because the config manager looks up the instance by it's class
class BubbleConfig : public slp::JsonConfig 
{
public:
    BubbleConfig() 
        : JsonConfig("Config/bubble_config.json", BaseConfig::getConfigTypeID<BubbleConfig>()) 
    {}
};

inline BubbleConfig const& globalBubbleConfig()
{
    return *slp::globalConfigManager().getConfig<BubbleConfig>();
}
