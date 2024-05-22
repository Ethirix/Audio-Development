// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "ActiveSoundStruct.generated.h"

USTRUCT(BlueprintType)
struct AUDIOMECHANICS_API FActiveSoundStruct
{
	GENERATED_BODY()

	FActiveSoundStruct() : Sound(nullptr), LinearVolume(0.0f) {}
	FActiveSoundStruct(USoundBase* Sound, float LinearVolume) : Sound(Sound), LinearVolume(LinearVolume) {}
	
	UPROPERTY(BlueprintReadOnly)
	USoundBase* Sound;
	UPROPERTY(BlueprintReadOnly)
	float LinearVolume;
};
