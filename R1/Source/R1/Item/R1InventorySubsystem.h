

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "R1InventorySubsystem.generated.h"

class UR1ItemInstance;

/**
 * Inventory Manager
 */
UCLASS()
class R1_API UR1InventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

	// TEMP: 임시로 기본 아이템 몇 종만 추가
	void AddDefaultItems();

	const TArray<TObjectPtr<UR1ItemInstance>>& GetItems() { return Items; }

protected:
	UPROPERTY()
	TArray<TObjectPtr<UR1ItemInstance>> Items;

	
};
