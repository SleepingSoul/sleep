#pragma once
#include <Engine/Config/BaseConfig.h>

BEGIN_NAMESPACE_SLEEP

// reads json file, stores config in json object
class JsonConfig : public BaseConfig
{
    using Base = BaseConfig;
public:
    JsonConfig(std::string_view filename);
    // so that child classes can init base config with their class id
    JsonConfig(std::string_view filename, TypeID typeId);

    auto const& at(std::string const& propertyName) const { return m_jsonConfig.at(propertyName); }

protected:
    // parses config file
    // true if success
    bool doLoad() override;

private:
    std::string m_filename;
    nlohmann::json m_jsonConfig;
};

END_NAMESPACE_SLEEP

