// Copyright Jack Wright. All Rights Reserved.


#include "FootstepManagerComponent.h"

#include "ActiveSoundStruct.h"
#include "StepSoundComponent.h"
#include "WeatherManager.h"
#include "WeatherManagerComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UFootstepManagerComponent::UFootstepManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFootstepManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeatherManager::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		WeatherManagerComponent = Cast<UWeatherManagerComponent>(
			FoundActors[0]->GetComponentByClass(UWeatherManagerComponent::StaticClass()));
	}
		
	LeftFootCollider = Cast<UPrimitiveComponent>(LeftFootColliderReference.GetComponent(Owner));
	RightFootCollider = Cast<UPrimitiveComponent>(RightFootColliderReference.GetComponent(Owner));
	LeftFootAudioComponent = Cast<UAudioComponent>(LeftFootAudioReference.GetComponent(Owner));
	RightFootAudioComponent = Cast<UAudioComponent>(RightFootAudioReference.GetComponent(Owner));

	if (!LeftFootCollider)
	{	
		DebugNoPrimitiveComponent("Left Foot Collider");
	}
	else
	{
		LeftFootCollider->OnComponentBeginOverlap.AddDynamic(this, &UFootstepManagerComponent::OnLeftFootBeginOverlap);
		LeftFootCollider->OnComponentEndOverlap.AddDynamic(this, &UFootstepManagerComponent::OnLeftFootEndOverlap);
	}
	
	if (!RightFootCollider)
	{
		DebugNoPrimitiveComponent("Right Foot Collider");
	}
	else
	{
		RightFootCollider->OnComponentBeginOverlap.AddDynamic(this, &UFootstepManagerComponent::OnRightFootBeginOverlap);
		RightFootCollider->OnComponentEndOverlap.AddDynamic(this, &UFootstepManagerComponent::OnRightFootEndOverlap);
	}

	if (!LeftFootAudioComponent)
	{
		DebugNoAudioComponent("Left Foot Audio Component");
	}

	if (!RightFootAudioComponent)
	{
		DebugNoAudioComponent("Right Foot Audio Component");
	}
}

void UFootstepManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFootstepManagerComponent::OnLeftFootBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, signed int OtherBodyIndex,
                                                       bool FromSweep, const FHitResult& SweepResult)
{
	UStepSoundComponent* SoundComponent = Cast<UStepSoundComponent>(
		OtherActor->GetComponentByClass(UStepSoundComponent::StaticClass()));
	if (OtherActor == Owner || !SoundComponent || LeftFootCollidingWith.Num() > 0)
	{
		return;
	}
	LeftFootCollidingWith.Add(OtherActor);
	
	RunFootstep(LeftFootCollider, SoundComponent);
	
	DebugCollidedObject(OtherActor, FColor::Cyan);
}

void UFootstepManagerComponent::OnLeftFootEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, signed int OtherBodyIndex)
{
	LeftFootCollidingWith.Remove(OtherActor);
}

void UFootstepManagerComponent::OnRightFootBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, signed int OtherBodyIndex,
                                                        bool FromSweep, const FHitResult& SweepResult)
{
	UStepSoundComponent* SoundComponent = Cast<UStepSoundComponent>(
		OtherActor->GetComponentByClass(UStepSoundComponent::StaticClass()));
	if (OtherActor == Owner || !SoundComponent || RightFootCollidingWith.Num() > 0)
	{
		return;
	}
	RightFootCollidingWith.Add(OtherActor);
	

	RunFootstep(RightFootCollider, SoundComponent);
	
	DebugCollidedObject(OtherActor, FColor::Magenta);
}

void UFootstepManagerComponent::OnRightFootEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, signed int OtherBodyIndex)
{
	RightFootCollidingWith.Remove(OtherActor);
}

void UFootstepManagerComponent::RunFootstep(UPrimitiveComponent* FootColliderComponent,
                                            UStepSoundComponent* StepSoundComponent)
{
	TArray<FActiveSoundStruct> ActiveSounds = WeatherManagerComponent->GetActiveSounds();
	float TotalVolume = 0.0f;
	for (FActiveSoundStruct ActiveSound : ActiveSounds)
	{
		TotalVolume += ActiveSound.LinearVolume;
	}
	
	ActiveSounds.Emplace(StepSoundComponent->GetSound(), 1 - TotalVolume);
	for (FActiveSoundStruct Sound : ActiveSounds)
	{
		LeftFootAudioComponent->Sound = Sound.Sound;
		LeftFootAudioComponent->VolumeMultiplier = Sound.LinearVolume;
		LeftFootAudioComponent->Play();
	}
}

void UFootstepManagerComponent::DebugNoPrimitiveComponent(const FString& Name)
{
#ifdef WITH_EDITORONLY_DATA
	if (GEngine && bPrintDebug)
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			10.0f,
			FColor::Red,
			FString::Printf(
				TEXT("Did not find a valid Primative Component for %s!"),
				*Name));
	}
#endif
}

void UFootstepManagerComponent::DebugNoAudioComponent(const FString& Name)
{
#ifdef WITH_EDITORONLY_DATA
	if (GEngine && bPrintDebug)
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			10.0f,
			FColor::Red,
			FString::Printf(
				TEXT("Did not find a valid Audio Component for %s!"),
				*Name));
	}
#endif
}

void UFootstepManagerComponent::DebugCollidedObject(const AActor* Actor, const FColor Color)
{
#ifdef WITH_EDITORONLY_DATA
	if (GEngine && bPrintDebug)
	{
		int32 Id = Actor->GetUniqueID() + Color.ToPackedARGB();
		GEngine->AddOnScreenDebugMessage(
			Id,
			0.25f,
			Color,
			FString::Printf(
				TEXT("%s"),
				*Actor->GetActorLabel()));
	}
#endif
}

