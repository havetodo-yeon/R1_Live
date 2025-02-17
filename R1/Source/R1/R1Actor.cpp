// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Actor.h"
#include "R1Object.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AR1Actor::AR1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>FindMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Dobe/SM_ChamferCube.SM_ChamferCube'"));
	if(FindMesh.Succeeded())
	{
		Box->SetStaticMesh(FindMesh.Object);
	}*/

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;
	Body->SetRelativeScale3D(FVector(2, 3, 0.5f));

	Wings = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wings"));
	Wings->SetupAttachment(Body);
	Wings->SetRelativeLocationAndRotation(FVector(55, -72, 80), FRotator(0, 90, 0));
	Wings->SetRelativeScale3D(FVector(3.75f, 0.25f, 0.5f));

	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Body);
	Head->SetRelativeLocationAndRotation(FVector(105, 36, 40), FRotator(0, 0, 0));
	Head->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	Wings->SetRelativeLocation(FVector(0, 0, 0));
	Head->SetRelativeLocation(FVector(0, 0, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>FindMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Dobe/SM_ChamferCube.SM_ChamferCube'"));
	if (FindMesh.Succeeded())
	{
		Body->SetStaticMesh(FindMesh.Object);
		Wings->SetStaticMesh(FindMesh.Object);
		Head->SetStaticMesh(FindMesh.Object);
	}

}

// Called when the game starts or when spawned
void AR1Actor::BeginPlay()
{
	Super::BeginPlay();

	// Target = UGameplayStatics::GetActorOfClass(GetWorld(), AR1Actor::StaticClass());
	
	//std::vector
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Dobe"), Actors);

	if (Actors.Num() > 0)
	{
		Target = Actors[0];
	}

}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Target != nullptr)
	{
		float Speed = 50.0f;
		float Distance = DeltaTime * Speed;

		FVector Location = GetActorLocation();	// 현재 위치 가져오기

		FVector DirectionVector = Target->GetActorLocation() - GetActorLocation();
		DirectionVector.Normalize();

		//FVector NewLocation = Location + FVector::ForwardVector * Distance;	// 방향벡터를 더하여 위치 갱신
		//SetActorLocation(NewLocation);
		// 
		//AddActorWorldOffset(FVector::ForwardVector * Distance);

		AddActorWorldOffset(DirectionVector * Distance);

	}
}
