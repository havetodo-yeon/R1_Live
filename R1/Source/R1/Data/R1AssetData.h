

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "R1AssetData.generated.h"

USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName AssetName;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> AssetLabels;

};

USTRUCT()
struct FAssetSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAssetEntry> AssetEntries;

};


/**
 * 
 */
UCLASS()
class R1_API UR1AssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

public:
	// 캐싱한 거 꺼내서 빠르게 쓰겠다
	FSoftObjectPath GetAssetPathByName(const FName& AssetName);
	const FAssetSet& GetAssetSetByLabel(const FName& Label);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FAssetSet> AssetGroupNameToSet;

	// 임시적으로 캐싱해가지고 사용하고 싶은 그런 부분은 
	// UPROPERTY만 붙이고 괄호 안에 아무것도 안붙이면 됨
	// 캐싱하겠다는 함수 두 개
	UPROPERTY()
	TMap<FName, FSoftObjectPath> AssetNameToPath;

	UPROPERTY()
	TMap<FName, FAssetSet> AssetLabelToSet;


};
