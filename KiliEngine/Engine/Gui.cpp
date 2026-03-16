#include "Gui.h"
#include "Renderer/OpenGlRenderer.h"
#include "Renderer/SdlRenderer.h"

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
    ImGui::ShowDemoWindow();
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
