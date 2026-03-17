#include "Gui.h"
#include "Renderer/OpenGlRenderer.h"
#include "Renderer/SdlRenderer.h"
#include "Tools/GameTime.h"

bool Gui::Init(Window* pWindow, IRenderer* pRenderer)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends

    if (const GlRenderer* renderer = dynamic_cast<GlRenderer*>(pRenderer))
    {
        ImGui_ImplSDL2_InitForOpenGL(pWindow->GetSdlWindow(), renderer->GetContext());
        ImGui_ImplOpenGL3_Init();
        
        return true;
    }
    if (const SdlRenderer* renderer = dynamic_cast<SdlRenderer*>(pRenderer))
    {
        ImGui_ImplSDL2_InitForSDLRenderer(pWindow->GetSdlWindow(), renderer->GetSdlRenderer());

        return true;
    }

    ImGui::DockSpaceOverViewport();

    return false;
}

void Gui::Input(const SDL_Event& pEvent)
{
    ImGui_ImplSDL2_ProcessEvent(&pEvent);
}

void Gui::BeginGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
    
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Fps", nullptr, window_flags))
    {
        ImGui::Text(("Fps : " + std::to_string(1.0f / GameTime::DeltaTime)).c_str());
        ImGui::Text(("Avg : " + std::to_string(1000.0f / GameTime::GetAvgFrameTime())).c_str());
    }
    ImGui::End();
}

void Gui::EndGui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::Close()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
