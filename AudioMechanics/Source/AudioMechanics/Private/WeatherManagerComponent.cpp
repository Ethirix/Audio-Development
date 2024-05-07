// Copyright Jack Wright. All Rights Reserved.


#include "WeatherManagerComponent.h"
#include "WeatherState.h"

UWeatherManagerComponent::UWeatherManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeatherManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeatherManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UWeatherState* State : WeatherStates)
	{
		if (const bool bChangeThisFrame = FMath::RandBool(); !bChangeThisFrame)
		{
			continue;
		}

		const bool bIncreaseState = FMath::RandBool();
		State->IncrementState(bIncreaseState ? DeltaTime : -DeltaTime);
	}

#if UE_BUILD_DEBUG | UE_BUILD_DEVELOPMENT
	for (UWeatherState* State : WeatherStates)
	{
		if (GEngine)
		{
			const int32 Id = State->GetUniqueID();
			GEngine->AddOnScreenDebugMessage(Id,1.0f, FColor::White,
				FString::Printf(TEXT("%s: %f"), *State->GetName(), State->GetState()));
		}
	}
#endif
}

TArray<UWeatherState*>& UWeatherManagerComponent::GetStates()
{
	return WeatherStates;
}

void UWeatherManagerComponent::AddState(UWeatherState* State)
{
	WeatherStates.Add(State);
}
