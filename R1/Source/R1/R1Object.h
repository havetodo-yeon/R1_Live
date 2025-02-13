// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "R1Object.generated.h"

/**
 * 
 */
UCLASS()
class R1_API UR1Object : public UObject
{
	GENERATED_BODY()
	
public:
	int32 Hp = 100;
	float Speed = 3.3f;
};
