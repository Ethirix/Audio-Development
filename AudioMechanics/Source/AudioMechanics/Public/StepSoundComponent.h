// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StepSoundComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOMECHANICS_API UStepSoundComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Sound;
	
public:
	UStepSoundComponent();

	USoundBase* GetSound();

protected:
	virtual void BeginPlay() override;
};
