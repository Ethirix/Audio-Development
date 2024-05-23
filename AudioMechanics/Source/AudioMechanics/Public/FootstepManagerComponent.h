// Copyright Jack Wright. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootstepManagerComponent.generated.h"

class UStepSoundComponent;
class UWeatherManagerComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOMECHANICS_API UFootstepManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Footstep Manager|Colliders")
	FComponentReference LeftFootColliderReference;
	UPROPERTY(EditDefaultsOnly, Category = "Footstep Manager|Colliders")
	FComponentReference RightFootColliderReference;
	UPROPERTY(EditDefaultsOnly, Category = "Footstep Manager|Audio")
	FComponentReference LeftFootAudioReference;
	UPROPERTY(EditDefaultsOnly, Category = "Footstep Manager|Audio")
	FComponentReference RightFootAudioReference;

	UPROPERTY(EditAnywhere, Category = "Footstep Manager")
	float AudioComponentTimeout = 5.0f;
	
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> LeftFootCollider;
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> RightFootCollider;
	UPROPERTY()
	TObjectPtr<UAudioComponent> LeftFootAudioComponent;
	UPROPERTY()
	TObjectPtr<UAudioComponent> RightFootAudioComponent;

	UPROPERTY(VisibleInstanceOnly)
	bool bLeftFootCollided = false;
	UPROPERTY(VisibleInstanceOnly)
	bool bRightFootCollided = false;

	UPROPERTY()
	TObjectPtr<UWeatherManagerComponent> WeatherManagerComponent;
	
	UPROPERTY()
	TObjectPtr<AActor> Owner;

	void RunFootstep(UPrimitiveComponent* FootColliderComponent, UStepSoundComponent* StepSoundComponent);
	
	void DebugNoPrimitiveComponent(const FString& Name);
	void DebugNoAudioComponent(const FString& Name);
	void DebugCollidedObject(const AActor* Actor, const FColor Color);

	UFUNCTION()
	void OnLeftFootBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, signed int OtherBodyIndex, bool FromSweep,
	                            const FHitResult& SweepResult);
	UFUNCTION()
	void OnLeftFootEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, signed int OtherBodyIndex);
	UFUNCTION()
	void OnRightFootBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, signed int OtherBodyIndex, bool FromSweep,
								const FHitResult& SweepResult);
	UFUNCTION()
	void OnRightFootEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, signed int OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;

public:	
	UFootstepManagerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Footstep Manager")
	bool bPrintDebug = true;
};
