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

#include <Engine/Utils/MacroUtils.h>
#include <Engine/EngineConfig.h>
#include <Engine/SleepTypes.h>
#include <Engine/Utils/Utils.h>

#include <Engine/Render/Texture.h>
#include <Engine/Updator.h>
#include <Engine/Render/Transform2D.h>
#include <Engine/Render/DrawCall.h>
#include <Engine/Render/Renderer.h>
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Camera.h>
#include <Engine/Clock.h>
#include <Engine/Timer.h>
#include <Engine/GameWindow.h>
#include <Engine/Object.h>
