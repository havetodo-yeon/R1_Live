#include "Character/R1Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/R1PlayerController.h"

AR1Player::AR1Player()
{	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;	// Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);


	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;	// Camera does not totate relative to arm

	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//GetCapsuleComponent()->SetCollisionResponseToChannels(ECC_Pawn, ECC_Ignore);

}

void AR1Player::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

}

void AR1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AR1Player::HandleGameplayEvent(FGameplayTag EventTag)
{
	// TODO: PlayerController에 있는 상태나 HP 등의 수치가 Player쪽에 있는 것이 장기적으로는 더 좋음
	AR1PlayerController* PC = Cast<AR1PlayerController>(GetController());
	if (PC) 
	{
		PC->HandleGameplayEvent(EventTag);
	}
}

void AR1Player::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

}