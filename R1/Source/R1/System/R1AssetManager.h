

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "R1AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class R1_API UR1AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UR1AssetManager();
	static UR1AssetManager& Get();

	// TODO

};
