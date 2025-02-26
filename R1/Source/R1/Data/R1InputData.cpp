#include "Data/R1InputData.h"
#include "R1LogChannels.h"

const UInputAction* UR1InputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FR1InputAction& Action : InputActions)
	{	// 원하는 태그가 있는지 찾기
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogR1, Error, TEXT("Can't find InputAction for InputTag [%s]"), *InputTag.ToString());

	return nullptr;
}
