// Copyright Jack Wright. All Rights Reserved.


#include "StepSoundComponent.h"

UStepSoundComponent::UStepSoundComponent()
{
}

void UStepSoundComponent::BeginPlay()
{
	Super::BeginPlay();
}

USoundBase* UStepSoundComponent::GetSound()
{
	return Sound;
}