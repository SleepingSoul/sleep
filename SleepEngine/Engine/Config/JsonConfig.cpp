#include "stdafx.h"
#include "JsonConfig.h"

BEGIN_NAMESPACE_SLEEP

JsonConfig::JsonConfig(std::string_view filename)
    : JsonConfig(filename, Base::getConfigTypeID<JsonConfig>())
{}

JsonConfig::JsonConfig(std::string_view filename, TypeID typeId)
    : Base(typeId)
    , m_filename(filename)
{}

bool JsonConfig::doLoad()
{
    std::ifstream file(m_filename);
    file >> m_jsonConfig;

    if (m_jsonConfig.is_null())
    {
        LOG_AND_FAIL_ERROR("could not parse config file: {}", m_filename);
        return false;
    }

    return true;
}

END_NAMESPACE_SLEEP
