

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActor.generated.h"

UCLASS()
class R1_API AMainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TObjectPtr<class AR1Actor>Actor;
	UPROPERTY()
	TSubclassOf<AR1Actor> ActorClass;	// 캐스팅이 되는 애들만 받아옴 클래스 타입을 넣어줄 수 있다.

};
