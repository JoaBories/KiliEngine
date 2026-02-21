#pragma once

#include <string>
#include "IRenderer.h"
#include "GameActor.h"

class Scene
{
protected:
	std::string mTitle;
	IRenderer* mRenderer;

	std::vector<GameActor*> mActors;
	std::vector<GameActor*> mPendingActors;
	bool mIsUpdatingActors;
	
	explicit Scene(const std::string& pTitle = "Scene") :
		mTitle{pTitle},
		mRenderer{nullptr},
		mIsUpdatingActors{false}
	{
	}
	
public :

	virtual ~Scene() = default;

	static Scene* ActiveScene;

	[[nodiscard]] IRenderer* GetRenderer() const { return mRenderer; }

	void UpdateAllActors();
	void RemoveActor(const GameActor* pActor);
	void AddActor(GameActor* pActor);
	void KillAllDead();

	void Update();
	void Close();
	void Start();

	void SetRenderer(IRenderer* pRenderer);

	[[nodiscard]] bool IsUpdatingActors() const { return mIsUpdatingActors; }

	virtual void AssetLoad() = 0;
	virtual void Unload();
	
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnClose() = 0;

	virtual void DebugDraw() = 0;

	[[nodiscard]] std::string GetTitle() const { return mTitle; }

	[[nodiscard]] GameActor* GetActorByTag(ActorTags pTag) const;
	[[nodiscard]] std::vector<GameActor*> GetActorsByTag(ActorTags pTag) const;

	template<typename T> T* GetActorOfClass() const
	{
		for (GameActor* a : mActors)
			if (T* actor = dynamic_cast<T*>(a)) return actor;
		return nullptr;
	}

	template<typename T> std::vector<T*> GetActorsOfClass() const
	{
		std::vector<T*> actors = {};
		for (GameActor* a : mActors)
			if (T* actor = dynamic_cast<T*>(a)) actors.push_back(actor);
		return actors;
	}
};

