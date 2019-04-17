#include "stdafx.h"
#include "JsonConfig.h"

BEGIN_NAMESPACE_SLEEP

JsonConfig::JsonConfig(std::string_view filename)
    : Base(Base::getConfigTypeID<JsonConfig>())
    , m_filename(filename)
{}

bool JsonConfig::doLoad()
{
    std::ifstream file(ConfigFile);
    file >> m_jsonConfig;

    if (m_jsonConfig.is_null())
    {
        LOG_AND_FAIL_ERROR("could not parse config file: {}", m_filename);
        return false;
    }

    return true;
}

END_NAMESPACE_SLEEP
