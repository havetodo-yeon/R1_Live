


#include "MainActor.h"
#include "R1Actor.h"

// Sets default values
AMainActor::AMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AR1Actor>FindClass(TEXT("/Script/Engine.Blueprint'/Game/_Dobe/BP_R1Actor.BP_R1Actor_C'"));	// 블루프린트 가져올때 맨 마지막에 _C
	if(FindClass.Succeeded())
	{
		ActorClass = FindClass.Class;
	}
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0, 0, 0);
	FRotator Rocation(0, 0, 0);
	
	//AR1Actor* Actor = GetWorld()->SpawnActor<AR1Actor>(Location, Rocation);
	//Actor = GetWorld()->SpawnActor<AR1Actor>(Location, Rocation);

	// dynamic_cast
	Actor = Cast<AR1Actor>( GetWorld()->SpawnActor(ActorClass));

	//Actor->SetLifeSpan(5.0f);
	//GetWorld()->DestroyActor(Actor);

}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

