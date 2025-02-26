

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "R1GameInstance.generated.h"

/**
 *
 */
UCLASS()
class R1_API UR1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// 게임 실행할 때 초기화
	UR1GameInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Init() override;
	virtual void Shutdown() override;
};
