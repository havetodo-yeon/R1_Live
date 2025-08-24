

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindPatrolPos.generated.h"

/**
 *
 */
UCLASS()
class R1_API UBTTaskNode_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector PatrolPosKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float SearchRadius = 1000.f;
};
