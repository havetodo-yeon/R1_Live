#include "R1GameInstance.h"
#include "R1AssetManager.h"

UR1GameInstance::UR1GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	// 가상함수 override 할 때 꼭 super 해주기
{

}

void UR1GameInstance::Init()
{
	Super::Init();

	UR1AssetManager::Initialize();
}

void UR1GameInstance::Shutdown()
{
	Super::Shutdown();

}

