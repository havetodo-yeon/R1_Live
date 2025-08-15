

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1PlayerController.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class R1_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AR1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackMontage;

};
