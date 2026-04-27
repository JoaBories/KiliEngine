#pragma once

#include <string>
#include "SDL_keycode.h"
#include "Utils/Vector3.h"

enum ScreenMode : Uint8
{
    Windowed,
    Fullscreen,
};

enum FpsMode : Uint8
{
    Limited,
    Unlimited,
    Vsync
};

namespace Cfg
{
    constexpr FpsMode FPS_LOCKED = Limited;
    constexpr int FPS_MAX = 144;

    constexpr float DELTA_TIME_MAX = 0.1f;
    
    const std::string TEXTURE_PATH = "Resources/Textures";
    const std::string SHADER_PATH = "Resources/Shaders";
    const std::string MESH_PATH = "Resources/Meshes";
    const std::string MATERIAL_PATH = "Resources/Materials";
    const std::string MAP_PATH = "Resources/Maps";

    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 800;
    
    constexpr ScreenMode WINDOW_MODE = ScreenMode::Windowed;
    constexpr bool WINDOW_BORDERLESS = true;
    constexpr bool WINDOW_ALWAYS_ON_TOP = false;

    const std::string WINDOW_TITLE = "Kili Engine - DoomLike";

    constexpr float GRAVITY_FORCE = 9.8f;
    const Vector3 GRAVITY_DIR = Vector3(0, 0, -1).Normalized();

    constexpr float CORRECTION_STRENGTH = 1.0f;
    constexpr float ALLOWED_PENETRATION = 0.0f;

    constexpr bool MOUSECAPTURE_DEFAULT= true;

    const Vector3 DIRECTIONAL_LIGHT = Vector3(-1, -1, 0).Normalized();

    #ifdef _DEBUG
    constexpr SDL_Keycode EXIT_KEY = SDLK_ESCAPE;

    constexpr SDL_Keycode RENDER_MODE_DEFAULT = SDLK_F1;
    constexpr SDL_Keycode RENDER_MODE_UV = SDLK_F2;
    constexpr SDL_Keycode RENDER_MODE_NORMAL = SDLK_F3;
    constexpr SDL_Keycode RENDER_MODE_WIREFRAME = SDLK_F4;

    constexpr SDL_Keycode MOUSECAPTURE_TOGGLE = SDLK_F5;

    constexpr bool DEBUG_COLLISIONS = true;
    #endif
}
