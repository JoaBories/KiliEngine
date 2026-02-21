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

void Scene::AddActor(GameActor* pActor)
{
    pActor->Start();

    if (mIsUpdatingActors)
    {
        mPendingActors.emplace_back(pActor);
    }
    else
    {
        mActors.emplace_back(pActor);
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

void Scene::RemoveActor(const GameActor* pActor)
{
    auto it = find(mPendingActors.begin(), mPendingActors.end(), pActor);
    if (it != mPendingActors.end())
    {
        std::iter_swap(it, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    it = find(mActors.begin(), mActors.end(), pActor);
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
    for (const GameActor* actor : mActors)
    {
        delete actor;
    }
    mActors.clear();
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

GameActor* Scene::GetActorByTag(ActorTags pTag) const
{
    for (GameActor* a : mActors)
        if (a->GetTag() == pTag) return a;
    return nullptr;
}

std::vector<GameActor*> Scene::GetActorsByTag(ActorTags pTag) const
{
    std::vector<GameActor*> actors = {};
    for (GameActor* a : mActors)
        if (a->GetTag() == pTag) actors.push_back(a);
    return actors;
};