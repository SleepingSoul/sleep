#include "stdafx.h"
#include "Scene.h"

BEGIN_NAMESPACE_SLEEP

Scene::Scene(Initer&& initer, std::string_view id)
    : m_initer(std::move(initer))
    , m_id(id)
{}

END_NAMESPACE_SLEEP
