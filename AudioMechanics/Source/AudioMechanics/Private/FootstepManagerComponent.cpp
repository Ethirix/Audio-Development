// Copyright Jack Wright. All Rights Reserved.


#include "FootstepManagerComponent.h"

UFootstepManagerComponent::UFootstepManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFootstepManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	
	LeftFootCollider = Cast<UPrimitiveComponent>(LeftFootColliderReference.GetComponent(Owner));
	RightFootCollider = Cast<UPrimitiveComponent>(RightFootColliderReference.GetComponent(Owner));

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
}

void UFootstepManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFootstepManagerComponent::OnLeftFootBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, signed int OtherBodyIndex,
                                                       bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner || bLeftFootCollided)
	{
		return;
	}
	bLeftFootCollided = true;
	
	DebugCollidedObject(OtherActor, FColor::Cyan);
}

void UFootstepManagerComponent::OnLeftFootEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, signed int OtherBodyIndex)
{
	bLeftFootCollided = false;
}

void UFootstepManagerComponent::OnRightFootBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, signed int OtherBodyIndex,
                                                        bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner || bRightFootCollided)
	{
		return;
	}
	bRightFootCollided = true;
	
	DebugCollidedObject(OtherActor, FColor::Magenta);
}

void UFootstepManagerComponent::OnRightFootEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, signed int OtherBodyIndex)
{
	bRightFootCollided = false;
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

