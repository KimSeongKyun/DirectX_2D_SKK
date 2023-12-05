#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DropItem :public GameEngineActor
{
	friend class Item;
public:
	// constrcuter destructer
	DropItem();
	~DropItem();

	// delete Function
	DropItem(const DropItem& _Other) = delete;
	DropItem(DropItem&& _Other) noexcept = delete;
	DropItem& operator=(const DropItem& _Other) = delete;
	DropItem& operator=(DropItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ItemBody = nullptr;
	std::shared_ptr<class GameEngineCollision> ItemCollision = nullptr;
	std::string ItemName = "";
	float ItemSize = 26.0f;
	float ResultPos = 0.0f;
	float MoveTime = 0.0f;
	float StandardTime = 0.0f;

	void ComponentSetting();
	void SettingPos(int _EA, int _Number);
	void DropMotion(float _Delta);
	void StandardMotion(float _Delta);
};

