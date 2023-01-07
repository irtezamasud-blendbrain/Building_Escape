// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "WorldPosition.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UWorldPosition : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWorldPosition();
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	const float TotalMassOfActors();
	const void FindAudioComponent();
	void FindDoorTrigger();
	bool DoorSoundPlayed = false;

private:
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 75;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = .5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.0f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float DoorTriggerWeight = 50.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
