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
#include <future>
#pragma endregion

#pragma region Render
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma endregion

#pragma region Math
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#pragma endregion

#include <Engine/SleepTypes.h>
#include <Engine/Utils/MacroUtils.h>
#include <Engine/Utils/Utils.h>

#include <Engine/Render/Texture.h>
#include <Engine/Updator.h>
#include <Engine/Render/DrawCall.h>
#include <Engine/Render/Renderer.h>
#include <Engine/GameWindow.h>
