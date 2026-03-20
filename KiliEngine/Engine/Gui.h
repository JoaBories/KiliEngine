#pragma once

#ifdef _DEBUG

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "Window.h"
#include "Renderer/IRenderer.h"

class Gui
{

private:
    static void DrawFps();
    static void Properties();
    static void Scene();
    
public:
    static bool Init(Window* pWindow, IRenderer* pRenderer);
    static void Input(const SDL_Event& pEvent);
    static void BeginGui();
    static void EndGui();
    static void Close();

    
};

#endif
