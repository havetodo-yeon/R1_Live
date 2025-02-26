

#pragma once

#include "R1LogChannels.h"
#include "Data/R1AssetData.h"
#include "Engine/AssetManager.h"
#include "R1AssetManager.generated.h"

class UR1AssetData;

DECLARE_DELEGATE_TwoParams(FAsyncLoadCompletedDelegate, const FName&/*AssetName or Label*/, UObject*/*LoadedAsset*/);

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

public:
	static void Initialize();

	template<typename AssetType>
	static AssetType* GetAssetByName(const FName& AssetName);

	// 함수 호출했을때 함수가 끝날때까지 기다릴지 안기다릴지 차이
	// 동기로딩 : 요청해놓고 끝날때까지 기다림.
	static void LoadSyncByPath(const FSoftObjectPath& AssetPath);
	static void LoadSyncByName(const FName& AssetName);
	static void LoadSyncByLabel(const FName& Label);

	// 비동기로딩: 일단 요청해놓고 빠져나와서 다른 일 진행하다가 
	// 나중에 완료가 되었다는 통지를 받으면 그거를 가지고 처리하는 방식.
	// 조금 더 유연하게 만들 수 있지만, 코드가 그만큼 복잡해진다.
	// FAsyncLoadCompletedDelegate 자료형 사용하여 CompletedDelegate 어떤 함수의 포인터를 받아주는 개념
	static void LoadAsyncByPath(const FSoftObjectPath& AssetPath, FAsyncLoadCompletedDelegate CompletedDelegate = FAsyncLoadCompletedDelegate());
	static void LoadAsyncByName(const FName& AssetName, FAsyncLoadCompletedDelegate CompletedDelegate = FAsyncLoadCompletedDelegate());

	static void ReleaseByPath(const FSoftObjectPath& AssetPath);
	static void ReleaseByName(const FName& AssetName);
	static void ReleaseByLabel(const FName& Label);
	static void ReleaseAll();

private:
	void LoadPreloadAssets();
	// 구현부
	void AddLoadedAsset(const FName& AssetName, const UObject* Asset);

private:
	UPROPERTY()
	TObjectPtr<UR1AssetData> LoadedAssetData;	// 여기가 핵심.. 로딩한 에셋 여기서 들고있음

	UPROPERTY()
	TMap<FName, TObjectPtr<const UObject>> NameToLoadedAsset;

	//FCriticalSection LoadedAssetsCritical;	// 멀티스레드가 필요하다면...
};

template<typename AssetType>
AssetType* UR1AssetManager::GetAssetByName(const FName& AssetName)
{
	UR1AssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	if (AssetPath.IsValid())
	{
		LoadedAsset = Cast<AssetType>(AssetPath.ResolveObject());
		if (LoadedAsset == nullptr)
		{
			UE_LOG(LogR1, Warning, TEXT("Attempted sync loading because asset hadn't loaded yet [%s]."), *AssetPath.ToString());
			LoadedAsset = Cast<AssetType>(AssetPath.TryLoad());
		}
	}
	return LoadedAsset;
}
