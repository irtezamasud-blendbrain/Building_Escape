// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

#include "Engine/TriggerVolume.h"

#define OUT
// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle = InitialYaw + OpenAngle;

	FindDoorTrigger();
	FindAudioComponent();
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > DoorTriggerWeight)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

const float UWorldPosition::TotalMassOfActors()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	if (!DoorTrigger) { return TotalMass; }

	DoorTrigger->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

void UWorldPosition::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("Door rotation is %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CurrentRotation);
	if (!AudioComponent) { return; }
	if (!DoorSoundPlayed)
	{
		AudioComponent->Play();
		DoorSoundPlayed = true;
	}
}

void UWorldPosition::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CurrentRotation);
	if (!AudioComponent) { return; }
	if (DoorSoundPlayed)
	{
		AudioComponent->Play();
		DoorSoundPlayed = false;
	}
}

const void UWorldPosition::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Audio Component is missing"));
	}
}

void UWorldPosition::FindDoorTrigger()
{
	if (!DoorTrigger)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has no door trigger set"), *GetOwner()->GetActorLabel())
	}
}
