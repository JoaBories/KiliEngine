#include "Scene.h"
#include <vector>
#include <algorithm>
#include "Engine/Assets/AssetManager.h"

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
    std::vector<GameActor*> dead; // collect deads

    auto actorIterator = mActors.begin();
    while (actorIterator != mActors.end()) // iterate trough actors
    {
        if ((*actorIterator)->GetState() == ActorState::Dead) // if dead remove it from list and add it in dead
        {
            dead.push_back(*actorIterator);
            actorIterator = mActors.erase(actorIterator);     // remove dead actor and return next iterator
        }
        else
        {
            ++actorIterator;
        }
    }
    
    for (const GameActor* actor : dead)
    {
        delete actor;
    }
}

void Scene::SetRenderer(GlRenderer* pRenderer)
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