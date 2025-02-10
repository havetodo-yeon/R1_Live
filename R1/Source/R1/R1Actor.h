// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "R1Actor.generated.h"

class UR1Object;

UCLASS()
class R1_API AR1Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AR1Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UR1Object* Obj1;	// 명시 안함

	// 메모리 확보를 위해 이것은 멤버변수입니다를 명시
	// 우리가 일일이 지정해줘야함 언리얼이 얘를 봐주기를(탐색해주기를) 바라는거임
	// UClass, UFunction 등 마찬가지
	UPROPERTY()
	UR1Object* Obj2;
};
