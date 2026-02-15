#include "Scene.h"
#include <vector>
#include <algorithm>
#include "AssetManager.h"

void Scene::Update() 
{
    UpdateAllActors();
    OnUpdate();

    for (GameActor* actor : mPendingActors)
    {
        mActors.emplace_back(actor);
    }
    mPendingActors.clear();

    KillAllDead();
}

void Scene::UpdateAllActors()
{
    mIsUpdatingActors = true;

    for (const auto& actor : mActors)
    {
        actor->Update();
    }

    mIsUpdatingActors = false;
}

void Scene::AddActor(GameActor* actor)
{
    actor->SetScene(this);
    actor->Start();

    if (mIsUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }

}

void Scene::KillAllDead()
{
    for (GameActor* actor : mActors)
    {
        if (actor->GetState() == Dead)
        {
            RemoveActor(actor);
            delete actor;
        }
    }
}

void Scene::RemoveActor(GameActor* actor)
{
    std::vector<GameActor*>::iterator it = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (it != mPendingActors.end())
    {
        std::iter_swap(it, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    it = find(mActors.begin(), mActors.end(), actor);
    if (it != mActors.end())
    {
        iter_swap(it, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Scene::SetRenderer(IRenderer* pRenderer)
{
    mRenderer = pRenderer;
}

void Scene::Unload()
{
    for (GameActor* i : mActors)
    {
        delete i;
    }
    mActors.clear();

    AssetManager::Clear();
}

void Scene::Start()
{
    OnStart();
}

void Scene::Close()
{
    OnClose();
    Unload();
}

GameActor* Scene::GetActorByTag(ActorTags tag) const
{
    for (GameActor* a : mActors)
        if (a->GetTag() == tag) return a;
    return nullptr;
}

std::vector<GameActor*> Scene::GetActorsByTag(ActorTags tag) const
{
    std::vector<GameActor*> actors = {};
    for (GameActor* a : mActors)
        if (a->GetTag() == tag) actors.push_back(a);
    return actors;
};