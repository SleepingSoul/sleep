#pragma once

#pragma region Standard headers
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include <filesystem>
#include <string>
#include <string_view>
#include <functional>
#include <chrono>
#include <cmath>
#include <thread>
#include <mutex>
#include <numeric>
#include <future>
#include <optional>
#pragma endregion

#pragma region Render
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma endregion

#pragma region Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma endregion

//profiling
#include <easy/profiler.h>
#include <easy/arbitrary_value.h>

// logging
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

// json
#include <nlohmann/json.hpp>

#include <Engine/Utils/MacroUtils.h>
#include <Engine/SleepTypes.h>
#include <Engine/Utils/Utils.h>

#include <Engine/Render/Texture.h>
#include <Engine/Transform2DData.h>
#include <Engine/Render/DrawCall.h>
#include <Engine/Render/GameRenderer.h>
#include <Engine/Camera.h>
#include <Engine/Clock.h>
#include <Engine/Timer.h>
#include <Engine/GameWindow.h>
#include <Engine/ObjectTree.h>
#include <Engine/GameTemplate/Game.h>
#include <Engine/Components/Component.h>
#include <Engine/Systems/System.h>
#include <Engine/Object.h>
#include <Engine/Components/Renderer.h>
#include <Engine/Components/Transform2D.h>
#include <Engine/Components/RigidBody.h>
#include <Engine/Utils/FactoryUtils.h>
#include <Engine/Systems/ConcreteSystem.h>
#include <Engine/Systems/PhysicsSystem.h>
