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

	for (UWeatherState* State : Weathers)
	{
		State->SetState(0);
	}
	
	if (WeatherStates.Num() - 1 >= BaseWeatherState)
	{
		WeatherStates[Weathers[BaseWeatherState]] = MaximumWeatherBudget;
		WeatherBudgetUsed = MaximumWeatherBudget;
	}
}

void UWeatherManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WeatherBudgetUsed > MaximumWeatherBudget)
	{
		WeatherBudgetUsed = MaximumWeatherBudget;
	}
	
	for (TTuple<UWeatherState*, float>& State : WeatherStates)
	{
		if (const bool bChangeThisFrame = FMath::RandBool(); !bChangeThisFrame)
		{
			continue;
		}

		const bool bIncreaseThisFrame =
			WeatherBudgetUsed < MaximumWeatherBudget && FMath::RandBool();
		const float DeltaState = bIncreaseThisFrame ? DeltaTime : -DeltaTime;
		WeatherBudgetUsed += DeltaState;
		State.Value += DeltaState;
	}

#if UE_BUILD_DEBUG | UE_BUILD_DEVELOPMENT
	for (const TTuple<UWeatherState*, float>& State : WeatherStates)
	{
		if (GEngine)
		{
			const int32 Id = State.Key->GetUniqueID();
			GEngine->AddOnScreenDebugMessage(Id,1.0f, FColor::White,
				FString::Printf(TEXT("%s: %f"), *State.Key->GetName(), State.Value));
		}
	}
#endif
}

TMap<UWeatherState*, float>& UWeatherManagerComponent::GetStates()
{
	return WeatherStates;
}

void UWeatherManagerComponent::AddState(UWeatherState* State)
{
	WeatherStates.Add(State);
}
