#include "System/R1AssetManager.h"
#include "R1LogCHannels.h"

UR1AssetManager::UR1AssetManager() : Super()
{
}

UR1AssetManager& UR1AssetManager::Get()
{
	if (UR1AssetManager* Singleton = Cast<UR1AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	return *NewObject<UR1AssetManager>();

}
