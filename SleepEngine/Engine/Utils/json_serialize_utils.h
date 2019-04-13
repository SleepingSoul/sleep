#pragma once
BEGIN_NAMESPACE_SLEEP

static void from_json(nlohmann::json const& json, glm::vec2& vec)
{
	vec.x = json.at("x");
	vec.y = json.at("y");
}

END_NAMESPACE_SLEEP