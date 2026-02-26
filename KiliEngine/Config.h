#pragma once

#include <string>
#include "SDL_keycode.h"
#include "Vector3.h"

const std::string TEXTURE_PATH = "Resources/Textures/";
const std::string SHADER_PATH = "Resources/Shaders/";
const std::string MESH_PATH = "Resources/Meshes";

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE = "Kili Engine";

constexpr float GRAVITY_FORCE = 9.8f;
const Vector3 GRAVITY_DIR = Vector3(0,0,-1);

#ifdef _DEBUG
constexpr SDL_Keycode EXIT_KEY = SDLK_ESCAPE;

constexpr SDL_Keycode RENDER_MODE_DEFAULT = SDLK_F1;
constexpr SDL_Keycode RENDER_MODE_UV = SDLK_F2;
constexpr SDL_Keycode RENDER_MODE_NORMAL = SDLK_F3;
constexpr SDL_Keycode RENDER_MODE_WIREFRAME = SDLK_F4;
#endif