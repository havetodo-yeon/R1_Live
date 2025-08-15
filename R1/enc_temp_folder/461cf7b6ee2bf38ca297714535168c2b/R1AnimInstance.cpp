


#include "Animation/R1AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/R1Player.h"

UR1AnimInstance::UR1AnimInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UR1AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AR1Player>(TryGetPawnOwner());

	if (Character)
		MovementComponent = Character->GetCharacterMovement();

}

void UR1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;
	if (MovementComponent == nullptr)
		return;

	//Velocity = MovementComponent->Velocity;
	//Groundspeed = Velocity.Size2D();

}
