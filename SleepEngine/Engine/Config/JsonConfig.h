#pragma once
#include <Engine/Config/BaseConfig.h>

BEGIN_NAMESPACE_SLEEP

// reads json file, stores config in json object
class JsonConfig : public BaseConfig
{
    using Base = BaseConfig;
public:
    JsonConfig(std::string_view filename);
    CONST_REF_GETTER(getData, m_jsonConfig);

protected:
    // parses config file
    // true if success
    bool doLoad() override;

private:
    std::string m_filename;
    nlohmann::json m_jsonConfig;
};

END_NAMESPACE_SLEEP

