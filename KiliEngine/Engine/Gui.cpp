#ifdef _DEBUG

#include "Gui.h"
#include "Renderer/OpenGlRenderer.h"
#include "Renderer/SdlRenderer.h"
#include "Scene/SceneManager.h"
#include "Tools/GameTime.h"

void Gui::DrawFps()
{
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    
    ImGui::SetNextWindowBgAlpha(0.5f);
    if (ImGui::Begin("Performance", nullptr, window_flags))
    {
        std::string fps = std::to_string(MathUtils::Round(1.0f / GameTime::DeltaTime));
        ImGui::Text(("Fps : " + fps).c_str());
        std::string avg = std::to_string(MathUtils::Round(1000.0f / GameTime::GetAvgFrameTime()));
        ImGui::Text(("Avg : " + avg).c_str());
    }
    ImGui::End();
}

void Gui::Properties()
{
    ImGui::Begin("Properties");
    ImGui::Text("Hello World!");
    ImGui::End();
}

void Gui::Scene()
{
    ImGui::Begin("Scene");
    ImGui::Text("List of Actors");
    ImGui::Separator();
    for (GameActor* actor : SceneManager::ActiveScene()->GetActorsOfClass<GameActor>())
    {
        ImGui::PushID(actor);
        if (ImGui::TreeNode(actor->GetName().c_str()))
        {
            for (ActorComponent* component : actor->GetComponents<ActorComponent>())
            {
                ImGui::PushID(component);
                ImGui::Indent();
                ImGui::Text(component->GetName().c_str());
                ImGui::Unindent();
                ImGui::PopID();
            }
            ImGui::TreePop();
        }
        ImGui::PopID();
    }
    ImGui::End();
}

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

    //Properties();
    Scene();
    
    DrawFps();
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

#endif