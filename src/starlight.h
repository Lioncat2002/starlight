#pragma once
#include "renderer/Loader.h"
#include "models/RawModel.h"
#include "renderer/Renderer.h"
#include "shaders/StaticShader.h"
#include "textures/Texture.h"
#include "models/Model.h"
#include "entities/Entity.h"
#include "entities/Lighting.h"
#include "utils/LogUtils.h"
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"