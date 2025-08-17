#pragma once

UENUM(BlueprintType)
enum class ECreatureState: uint8
{
	None,
	Moving,
	Skill,
	Dead,
};