#include "Data/R1InputData.h"
#include "R1LogChannels.h"

const UInputAction* UR1InputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	// 태그에 해당하는 인풋 액션 실행
	for (const FR1InputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogR1, Error, TEXT("Can't find InputAction for InputTag [%s]"), *InputTag.ToString());

	return nullptr;
}
